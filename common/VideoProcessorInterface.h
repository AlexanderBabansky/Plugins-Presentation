#pragma once

#include "com.h"

class VideoProcessorInterface : public MyUnknown {
public:
    static constexpr MYID ID = InterfaceIds::VIDPROCESSOR_ID;
    virtual MYRESULT MYCALLTYPE Process(MyUnknown* frame) = 0;
    virtual bool MYCALLTYPE DoesSupportFrame(MYID id) = 0;
    virtual const char* MYCALLTYPE GetName() = 0;
    virtual MYRESULT MYCALLTYPE Init(MYID frameType) = 0;
};

class VideoProcessorHostInterface : public MyUnknown {
public:
    static constexpr MYID ID = InterfaceIds::VIDPROCESSORHOST_ID;
    virtual void MYCALLTYPE AddPlugin(MyUnknown* plugin) = 0;
};
