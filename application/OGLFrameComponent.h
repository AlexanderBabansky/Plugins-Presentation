#include "VideoFrameInterface.h"

class OGLFrameComponent : public virtual OGLFrame {
public:
    OGLFrameComponent() = default;
    ~OGLFrameComponent() = default;
    OGLFrameComponent(int id);

    virtual int MYCALLTYPE GetOGLId() override;

    virtual void MYCALLTYPE AddRef() override;
    virtual void MYCALLTYPE Release()  override;
    virtual MYRESULT MYCALLTYPE QueryInterface(MYID riid, void** ppvObject) override;
private:
    int mTexId = 0;
};
