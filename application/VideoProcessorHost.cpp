#include "VideoProcessorHost.h"
#include <cstdio>

VideoProcessorHost::~VideoProcessorHost()
{
    for (auto& p : mPlugins) {
        p->Release();
    }
}

void VideoProcessorHost::printRegisteredPlugins()
{
    printf("Plugins (%ld):\n", mPlugins.size());
    for (auto& p : mPlugins) {
        printf("%s\n", p->GetName());
    }
    printf("\n");
}

void MYCALLTYPE VideoProcessorHost::AddPlugin(MyUnknown* plugin)
{
    if (!plugin) {
        printf("Bad plugin\n");
        return;
    }
    VideoProcessorInterface* vi = nullptr;
    if (plugin->QueryInterface(VideoProcessorInterface::ID,
        reinterpret_cast<void**>(&vi)) != UknownNS::MYSUCCESS || !vi) {
        printf("Not supported plugins\n");
        return;
    }
    mPlugins.push_back(vi);
}

void MYCALLTYPE VideoProcessorHost::AddRef()
{
    return;
}

void MYCALLTYPE VideoProcessorHost::Release()
{
    return;
}

MYRESULT MYCALLTYPE VideoProcessorHost::QueryInterface(MYID riid, void** ppvObject)
{
    if (!ppvObject)
        return UknownNS::MYERROR;
    switch (riid)
    {
    case VideoProcessorHostInterface::ID:
        (*ppvObject) = static_cast<VideoProcessorHostInterface*>(this);
        AddRef();
        return UknownNS::MYSUCCESS;
    default:
        break;
    }
    return UknownNS::NOTSUPPORTED;
}

int VideoProcessorHost::getPluginsCount() const
{
    return mPlugins.size();
}

VideoProcessorInterface* VideoProcessorHost::getProcessor(int index)
{
    return mPlugins[index];
}
