#pragma once

#include "VideoFrameInterface.h"

class VideoFrameComponent : public virtual VideoFrame, public virtual VideoFrame2 {
public:
    VideoFrameComponent() = default;
    VideoFrameComponent(int w, int h);
    VideoFrameComponent(int w, int h, int linesize);
    ~VideoFrameComponent();

    virtual uint32_t MYCALLTYPE GetWidth() override;
    virtual uint32_t MYCALLTYPE GetHeight() override;
    virtual void* MYCALLTYPE GetData() override;
    virtual float MYCALLTYPE GetOpacity() override;
    virtual uint32_t MYCALLTYPE GetLinesize() override;

    virtual void MYCALLTYPE AddRef() override;
    virtual void MYCALLTYPE Release()  override;
    virtual MYRESULT MYCALLTYPE QueryInterface(MYID riid, void** ppvObject) override;

private:
    uint32_t mWidth = 0;
    uint32_t mHeight = 0;
    uint32_t mLinesize = 0;
    float mOpacity = 1.0f;
    void* mData = nullptr;
};
