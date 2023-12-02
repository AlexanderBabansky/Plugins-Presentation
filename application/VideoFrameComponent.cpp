#include "VideoFrameComponent.h"

VideoFrameComponent::VideoFrameComponent(int w, int h) : VideoFrameComponent(w, h, w * 4) {}

VideoFrameComponent::VideoFrameComponent(int w, int h, int linesize) :mWidth(w), mHeight(h), mLinesize(linesize)
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
        (*ppvObject) = static_cast<VideoFrame*>(this);
        AddRef();
        return UknownNS::MYSUCCESS;
    case VideoFrame2::ID:
        (*ppvObject) = static_cast<VideoFrame2*>(this);
        AddRef();
        return UknownNS::MYSUCCESS;
    default:
        break;
    }
    return UknownNS::NOTSUPPORTED;
}
