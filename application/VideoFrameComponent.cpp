#include "VideoFrameComponent.h"

VideoFrameComponent::VideoFrameComponent(int w, int h) : VideoFrameComponent(w, h, w * 4) {}

VideoFrameComponent::VideoFrameComponent(int w, int h, int linesize) : mFrame1Comp(this), mFrame2Comp(this), mWidth(w), mHeight(h), mLinesize(linesize)
{
    int size = mLinesize * mHeight;
    mData = new char[size];
}

VideoFrameComponent::~VideoFrameComponent()
{
    delete[] mData;
}

uint32_t MYCALLTYPE VideoFrameComponent::GetWidth()
{
    return mWidth;
}

uint32_t MYCALLTYPE VideoFrameComponent::GetHeight()
{
    return mHeight;
}

void* MYCALLTYPE VideoFrameComponent::GetData()
{
    return mData;
}

float MYCALLTYPE VideoFrameComponent::GetOpacity()
{
    return mOpacity;
}

uint32_t MYCALLTYPE VideoFrameComponent::GetLinesize()
{
    return mLinesize;
}

void MYCALLTYPE VideoFrameComponent::AddRef()
{
    return;
}

void MYCALLTYPE VideoFrameComponent::Release()
{
    return;
}

MYRESULT MYCALLTYPE VideoFrameComponent::QueryInterface(MYID riid, void** ppvObject)
{
    if (!ppvObject) {
        return UknownNS::MYERROR;
    }
    switch (riid)
    {
    case VideoFrame::ID:
        (*ppvObject) = static_cast<VideoFrame*>(&mFrame1Comp);
        AddRef();
        return UknownNS::MYSUCCESS;
    case VideoFrame2::ID:
        (*ppvObject) = static_cast<VideoFrame2*>(&mFrame2Comp);
        AddRef();
        return UknownNS::MYSUCCESS;
    case MyUnknown::ID:
        (*ppvObject) = static_cast<MyUnknown*>(&mFrame1Comp);
        return UknownNS::MYSUCCESS;
    default:
        break;
    }
    return UknownNS::NOTSUPPORTED;
}

VideoFrame1Component::VideoFrame1Component(VideoFrameComponent* impl) :mImpl(impl)
{
}

uint32_t MYCALLTYPE VideoFrame1Component::GetWidth()
{
    return mImpl->GetWidth();
}

uint32_t MYCALLTYPE VideoFrame1Component::GetHeight()
{
    return mImpl->GetHeight();
}

void* MYCALLTYPE VideoFrame1Component::GetData()
{
    return mImpl->GetData();
}

float MYCALLTYPE VideoFrame1Component::GetOpacity()
{
    return mImpl->GetOpacity();
}

void MYCALLTYPE VideoFrame1Component::AddRef()
{
    return mImpl->AddRef();
}

void MYCALLTYPE VideoFrame1Component::Release()
{
    return mImpl->Release();
}

MYRESULT MYCALLTYPE VideoFrame1Component::QueryInterface(MYID riid, void** ppvObject)
{
    return mImpl->QueryInterface(riid, ppvObject);
}

void MYCALLTYPE VideoFrame2Component::AddRef()
{
    return mImpl->AddRef();
}

void MYCALLTYPE VideoFrame2Component::Release()
{
    return mImpl->Release();
}

MYRESULT MYCALLTYPE VideoFrame2Component::QueryInterface(MYID riid, void** ppvObject)
{
    return mImpl->QueryInterface(riid, ppvObject);
}

VideoFrame2Component::VideoFrame2Component(VideoFrameComponent* impl) :mImpl(impl)
{
}

uint32_t MYCALLTYPE VideoFrame2Component::GetWidth()
{
    return mImpl->GetWidth();
}

uint32_t MYCALLTYPE VideoFrame2Component::GetHeight()
{
    return mImpl->GetHeight();
}

void* MYCALLTYPE VideoFrame2Component::GetData()
{
    return mImpl->GetData();
}

uint32_t MYCALLTYPE VideoFrame2Component::GetLinesize()
{
    return mImpl->GetLinesize();
}
