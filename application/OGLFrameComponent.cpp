#include "OGLFrameComponent.h"

OGLFrameComponent::OGLFrameComponent(int id) : mTexId(id)
{
}

int MYCALLTYPE OGLFrameComponent::GetOGLId()
{
    return mTexId;
}

void MYCALLTYPE OGLFrameComponent::AddRef()
{
    return;
}

void MYCALLTYPE OGLFrameComponent::Release()
{
    return;
}

MYRESULT MYCALLTYPE OGLFrameComponent::QueryInterface(MYID riid, void** ppvObject)
{
    if (!ppvObject) {
        return UknownNS::MYERROR;
    }
    switch (riid)
    {
    case MyUnknown::ID:
        (*ppvObject) = static_cast<MyUnknown*>(this);
        AddRef();
        return UknownNS::MYSUCCESS;
    case OGLFrame::ID:
        (*ppvObject) = static_cast<OGLFrame*>(this);
        AddRef();
        return UknownNS::MYSUCCESS;
    default:
        break;
    }
    return UknownNS::NOTSUPPORTED;
}
