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
    return UknownNS::NOTSUPPORTED;
}
