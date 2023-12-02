#include <iostream>
#include "MyTestComponent.h"
#include <Windows.h>
#include "VideoFrameComponent.h"
#include "VideoProcessorHost.h"
#include "c_api.h"

void printWinLastError() {
    auto errorMessageID = GetLastError();
    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    printf("%s\n", messageBuffer);
    LocalFree(messageBuffer);
}

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

void processVideo(PluginPassHostType pluginMethod) {
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
    if (processor->Init(supportedFrames[1]) != UknownNS::MYSUCCESS) {
        printf("Failed to init processor\n");
        return;
    }
    VideoFrameComponent frameComponent(10, 10);
    processor->Process(&frameComponent);
}

int main()
{
    const char* lib_path = "C:\\Babansky\\PluginsPres\\PluginsCmake\\out\\build\\x64-Debug\\plugin\\plugin.dll";
    PluginPassHostType pluginMethod = nullptr;

#ifdef WIN32
    HMODULE lib = NULL;
    lib = LoadLibraryA(lib_path);
#else
    void* lib = nullptr;
    lib = dlopen(lib_path, RTLD_NOW);
#endif
    if (!lib) {
        printWinLastError();
        printf("failed to load plugin\n");
        return 1;
    }

#ifdef WIN32
    pluginMethod = reinterpret_cast<PluginPassHostType>(GetProcAddress(lib, PluginPassHostName));
#else
    pluginMethod = reinterpret_cast<PluginPassHostType>dlsym(lib, PluginPassHostName);
#endif // WIN32

    if (!pluginMethod) {
        printf("failed to load method\n");
        return 1;
    }
    processVideo(pluginMethod);
    FreeLibrary(lib);
    return 0;
}
