#pragma once

#include "com.h"

class MyInterface : public MyUnknown {
public:
    static const MYID ID = 1;
    virtual void MYCALLTYPE Hello1() = 0;
    virtual void MYCALLTYPE Hello2() = 0;
};

class MyInterface2 : public MyUnknown {
public:
    static const MYID ID = 2;
    virtual void MYCALLTYPE Hello3() = 0;
};

class SupportedInterface : public MyUnknown {
public:
    static const MYID ID = 3;
    virtual uint8_t MYCALLTYPE GetCount() = 0;
    virtual uint8_t MYCALLTYPE GetID(MYID i) = 0;
};
