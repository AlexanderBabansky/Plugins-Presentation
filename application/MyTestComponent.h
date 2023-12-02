#pragma once

#include "MyTestInterface.h"

class MyTestComponent : public MyInterface, public MyInterface2{
public:
    virtual void MYCALLTYPE AddRef() override;
    virtual void MYCALLTYPE Release() override;
    virtual MYRESULT MYCALLTYPE QueryInterface(uint64_t riid, void** ppvObject)  override;

    virtual void MYCALLTYPE Hello3() override;
    virtual void MYCALLTYPE Hello1() override;
    virtual void MYCALLTYPE Hello2() override;
};
