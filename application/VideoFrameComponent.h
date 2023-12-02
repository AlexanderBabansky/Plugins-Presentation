#pragma once

#include "VideoFrameInterface.h"
#include <memory>

class VideoFrameComponent;

class VideoFrame1Component : public VideoFrame {
public:
    VideoFrame1Component(VideoFrameComponent* impl);
    virtual uint32_t MYCALLTYPE GetWidth() override;
    virtual uint32_t MYCALLTYPE GetHeight() override;
    virtual void* MYCALLTYPE GetData() override;
    virtual float MYCALLTYPE GetOpacity() override;

    virtual void MYCALLTYPE AddRef() override;
    virtual void MYCALLTYPE Release()  override;
    virtual MYRESULT MYCALLTYPE QueryInterface(MYID riid, void** ppvObject) override;
private:
    VideoFrameComponent* mImpl = nullptr;
};

class VideoFrame2Component : public VideoFrame2 {
public:
    VideoFrame2Component(VideoFrameComponent* impl);
    virtual uint32_t MYCALLTYPE GetWidth() override;
    virtual uint32_t MYCALLTYPE GetHeight() override;
    virtual void* MYCALLTYPE GetData() override;
    virtual uint32_t MYCALLTYPE GetLinesize() override;

    virtual void MYCALLTYPE AddRef() override;
    virtual void MYCALLTYPE Release()  override;
    virtual MYRESULT MYCALLTYPE QueryInterface(MYID riid, void** ppvObject) override;
private:
    VideoFrameComponent* mImpl = nullptr;
};

class VideoFrameComponent {
public:
    VideoFrameComponent(int w, int h);
    VideoFrameComponent(int w, int h, int linesize);
    ~VideoFrameComponent();

    uint32_t GetWidth();
    uint32_t GetHeight();
    void* GetData();
    float GetOpacity();
    uint32_t GetLinesize();

    void AddRef();
    void Release();
    MYRESULT QueryInterface(MYID riid, void** ppvObject);

private:
    VideoFrame1Component mFrame1Comp;
    VideoFrame2Component mFrame2Comp;

    uint32_t mWidth = 0;
    uint32_t mHeight = 0;
    uint32_t mLinesize = 0;
    float mOpacity = 1.0f;
    char* mData = nullptr;
};


