#include "VideoProcessor.h"
#include "VideoFrameInterface.h"

#include <cstdio>

VideoProcessor* VideoProcessor::Create()
{
    return new VideoProcessor();
}

VideoProcessor::VideoProcessor()
{
    printf("Constructing video processor\n");
}

VideoProcessor::~VideoProcessor()
{
    printf("Destructing video processor\n");
}

MYRESULT MYCALLTYPE VideoProcessor::Process(MyUnknown* frame_unk)
{
    if (!frame_unk) {
        printf("Bad frame\n");
        return UknownNS::MYERROR;
    }
    if (!mInitedFrameType) {
        printf("Processor not inited\n");
        return UknownNS::MYERROR;
    }

    switch (mInitedFrameType.value())
    {
    case VideoFrame::ID:
        return ProcessFrame1(frame_unk);
    case VideoFrame2::ID:
        return ProcessFrame2(frame_unk);
    case OGLFrame::ID:
        return ProcessFrameOGL(frame_unk);

    default:
        printf("Internal error\n");
        break;
    }
    return UknownNS::MYERROR;
}

bool MYCALLTYPE VideoProcessor::DoesSupportFrame(MYID id)
{
    switch (id)
    {
    case VideoFrame::ID:
        return true;
    case VideoFrame2::ID:
        return true;
    case OGLFrame::ID:
        return true;
    default:
        break;
    }
    return false;
}

const char* MYCALLTYPE VideoProcessor::GetName()
{
    return "MyProcessor";
}

MYRESULT MYCALLTYPE VideoProcessor::Init(MYID frameType)
{
    if (DoesSupportFrame(frameType) == false) {
        return UknownNS::MYERROR;
    }
    mInitedFrameType = frameType;
    return UknownNS::MYSUCCESS;
}

void MYCALLTYPE VideoProcessor::AddRef()
{
    mCounter++;
}

void MYCALLTYPE VideoProcessor::Release()
{
    mCounter--;
    if (mCounter == 0) {
        delete this;
    }
}

MYRESULT MYCALLTYPE VideoProcessor::QueryInterface(MYID riid, void** ppvObject)
{
    if (!ppvObject)
        return UknownNS::MYERROR;
    switch (riid)
    {
    case VideoProcessorInterface::ID:
        (*ppvObject) = static_cast<VideoProcessorInterface*>(this);
        AddRef();
        return UknownNS::MYSUCCESS;
    case MyUnknown::ID:
        (*ppvObject) = static_cast<MyUnknown*>(this);
        AddRef();
        return UknownNS::MYSUCCESS;
    default:
        break;
    }
    return UknownNS::NOTSUPPORTED;
}

MYRESULT VideoProcessor::ProcessFrame1(MyUnknown* frame_unk)
{
    VideoFrame* frame = nullptr;
    if (frame_unk->QueryInterface(VideoFrame::ID, reinterpret_cast<void**>(&frame)) != UknownNS::MYSUCCESS || !frame) {
        printf("Wrong frame passed\n");
        return UknownNS::MYERROR;
    }
    printf("Processing Frame1.\nwidth: %d\nheight: %d\nopacity: %f\n\n", frame->GetWidth(), frame->GetHeight(), frame->GetOpacity());
    frame->Release();
    return UknownNS::MYSUCCESS;
}

MYRESULT VideoProcessor::ProcessFrame2(MyUnknown* frame_unk)
{
    VideoFrame2* frame = nullptr;
    if (frame_unk->QueryInterface(VideoFrame2::ID, reinterpret_cast<void**>(&frame)) != UknownNS::MYSUCCESS || !frame) {
        printf("Wrong frame passed\n");
        return UknownNS::MYERROR;
    }
    printf("Processing Frame2.\nwidth: %d\nheight: %d\nlinesize: %u\n\n", frame->GetWidth(), frame->GetHeight(), frame->GetLinesize());
    frame->Release();
    return UknownNS::MYSUCCESS;
}

MYRESULT VideoProcessor::ProcessFrameOGL(MyUnknown* frame_unk)
{
    OGLFrame* frame = nullptr;
    if (frame_unk->QueryInterface(OGLFrame::ID, reinterpret_cast<void**>(&frame)) != UknownNS::MYSUCCESS || !frame) {
        printf("Wrong frame passed\n");
        return UknownNS::MYERROR;
    }
    printf("Processing OGL frame. id: %d\n\n", frame->GetOGLId());
    frame->Release();
    return UknownNS::MYSUCCESS;
}
