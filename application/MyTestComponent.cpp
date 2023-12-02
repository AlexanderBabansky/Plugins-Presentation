#include <cstring>
#include <cstdio>

#include "MyTestComponent.h"

void __stdcall MyTestComponent::AddRef()
{
}

void __stdcall MyTestComponent::Release()
{
}


MYRESULT __stdcall MyTestComponent::QueryInterface(uint64_t riid, void** ppvObject)
{
    if (!ppvObject) {
        return UknownNS::MYERROR;
    }
    if (riid == MyInterface::ID) {
        *ppvObject = static_cast<MyInterface*>(this);
        return UknownNS::MYSUCCESS;
    }
    if (riid == MyInterface2::ID) {
        *ppvObject = static_cast<MyInterface2*>(this);
        return UknownNS::MYSUCCESS;
    }
    if (riid == MyUnknown::ID) {
        MyInterface* iface = static_cast<MyInterface*>(this);
        *ppvObject = static_cast<MyUnknown*>(iface);
        return UknownNS::MYSUCCESS;
    }
    *ppvObject = nullptr;
    return UknownNS::MYERROR;
}

void MyTestComponent::Hello1()
{
    printf("Hello1\n");
}

void MyTestComponent::Hello2()
{
    printf("Hello2\n");
}

void __stdcall MyTestComponent::Hello3()
{
    printf("Hello3\n");
}
