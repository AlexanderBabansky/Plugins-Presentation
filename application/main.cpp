#include <iostream>
#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include "VideoFrameComponent.h"
#include "VideoProcessorHost.h"
#include "c_api.h"

#ifdef WIN32
void printWinLastError() {
    auto errorMessageID = GetLastError();
    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    printf("%s\n", messageBuffer);
    LocalFree(messageBuffer);
}
#endif

std::vector<MYID> getProcessorSupportedFrames(VideoProcessorInterface* processor) {
    std::vector<MYID> check = { VideoFrame::ID, VideoFrame2::ID, OGLFrame::ID };
    std::vector<MYID> res;
    for (auto& f : check) {
        if (processor->DoesSupportFrame(f)) {
            res.push_back(f);
        }
    }
    return res;
}

const char* frameTypeToStr(const MYID& id) {
    switch (id)
    {
    case VideoFrame::ID:
        return "VideoFrame";
    case VideoFrame2::ID:
        return "VideoFrame2";
    case OGLFrame::ID:
        return "OGLFrame";
    default:
        break;
    }
    return nullptr;
}

void printSupportedFrames(const std::vector<MYID>& types) {
    printf("Frametypes:\n");
    for (auto& f : types) {
        printf("%s\n", frameTypeToStr(f));
    }
    printf("\n");
}

void processVideo(PluginPassHostType pluginMethod, int frameTypeId) {
    VideoProcessorHost host;
    pluginMethod(&host);
    printf("\n");
    host.printRegisteredPlugins();
    if (host.getPluginsCount() == 0) {
        printf("No plugins registered\n");
        return;
    }
    VideoProcessorInterface* processor = host.getProcessor(0);
    auto supportedFrames = getProcessorSupportedFrames(processor);
    if (supportedFrames.empty()) {
        printf("No supported frames\n");
        return;
    }
    printSupportedFrames(supportedFrames);
    if (supportedFrames.size() <= frameTypeId) {
        printf("Out of supported frame\n");
        return;
    }
    if (processor->Init(supportedFrames[frameTypeId]) != UknownNS::MYSUCCESS) {
        printf("Failed to init processor\n");
        return;
    }
    VideoFrameComponent frameCom(10, 10);
    MyUnknown* frameAbstr = nullptr;
    frameCom.QueryInterface(MyUnknown::ID, reinterpret_cast<void**>(&frameAbstr));
    if (processor->Process(frameAbstr) != UknownNS::MYSUCCESS) {
        printf("Failed to process frame\n");
    }
}

int main(int argc, const char** argv)
{
    if (argc < 3) {
        printf("Bad args\n");
        return 1;
    }
    const char* lib_path = argv[1];
    int frameTypeId = atoi(argv[2]);
    PluginPassHostType pluginMethod = nullptr;

#ifdef WIN32
    HMODULE lib = NULL;
    lib = LoadLibraryA(lib_path);
#else
    void* lib = nullptr;
    lib = dlopen(lib_path, RTLD_NOW);
#endif
    if (!lib) {
#ifdef WIN32
        printWinLastError();
#endif // WIN32        
        printf("failed to load plugin\n");
        return 1;
    }

#ifdef WIN32
    pluginMethod = reinterpret_cast<PluginPassHostType>(GetProcAddress(lib, PluginPassHostName));
#else
    pluginMethod = reinterpret_cast<PluginPassHostType>(dlsym(lib, PluginPassHostName));
#endif // WIN32

    if (!pluginMethod) {
        printf("failed to load method\n");
        return 1;
    }
    processVideo(pluginMethod, frameTypeId);

#ifdef WIN32
    FreeLibrary(lib);
#else
    dlclose(lib);
#endif // WIN32

    return 0;
}
