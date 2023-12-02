#include "MyTestInterface.h"
#include "VideoProcessor.h"
#include <cstdio>
#include "c_api.h"


extern "C" {
    EXPORT_DLL void MYCALLTYPE PluginPassHostMethod(MyUnknown* unk) {
        if (!unk) {
            printf("Bad args\n");
            return;
        }
        VideoProcessorHostInterface* host = nullptr;
        if (unk->QueryInterface(VideoProcessorHostInterface::ID, reinterpret_cast<void**>(&host)) != UknownNS::MYSUCCESS || !host) {
            printf("No supported host\n");
            return;
        }
        auto plug = VideoProcessor::Create();
        host->AddPlugin(plug);
        plug->Release();
        host->Release();
    }
}

