#pragma once

#include "com.h"

class VideoFrame : public virtual MyUnknown {
public:
    static constexpr MYID ID = InterfaceIds::VIDEOFRAME_ID;

    virtual uint32_t MYCALLTYPE GetWidth() = 0;
    virtual uint32_t MYCALLTYPE GetHeight() = 0;
    virtual void* MYCALLTYPE GetData() = 0;
    virtual float MYCALLTYPE GetOpacity() = 0;
};

class VideoFrame2 : public virtual MyUnknown {
public:
    static constexpr MYID ID = InterfaceIds::VIDEOFRAME2_ID;

    virtual uint32_t MYCALLTYPE GetWidth() = 0;
    virtual uint32_t MYCALLTYPE GetHeight() = 0;
    virtual void* MYCALLTYPE GetData() = 0;
    virtual uint32_t MYCALLTYPE GetLinesize() = 0;
};

class OGLFrame : public virtual MyUnknown {
public:
    static constexpr MYID ID = InterfaceIds::OGLFRAME;

    virtual int MYCALLTYPE GetOGLId() = 0;
};
