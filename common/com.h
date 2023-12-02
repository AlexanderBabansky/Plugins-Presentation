#pragma once
#include <cstdint>
#include "InterfaceIds.h"

#define MYCALLTYPE __stdcall
#define EXPORT_DLL __declspec(dllexport)

typedef uint8_t MYRESULT;

namespace UknownNS {
    constexpr MYRESULT MYSUCCESS = 0;
    constexpr MYRESULT MYERROR = 1;
    constexpr MYRESULT NOTSUPPORTED = 1;
}

struct MyUnknown {
public:
    static constexpr MYID ID = InterfaceIds::UNKNOWN_ID;
    virtual void MYCALLTYPE AddRef() = 0;
    virtual void MYCALLTYPE Release() = 0;
    virtual MYRESULT MYCALLTYPE QueryInterface(MYID riid, void **ppvObject) = 0;
};
