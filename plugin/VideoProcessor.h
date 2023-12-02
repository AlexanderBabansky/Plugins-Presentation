#include "VideoProcessorInterface.h"
#include <string>
#include <optional>

class VideoProcessor : public virtual VideoProcessorInterface {
public:
    static VideoProcessor* Create();

    VideoProcessor();
    ~VideoProcessor();

    virtual MYRESULT MYCALLTYPE Process(MyUnknown* frame) override;
    virtual bool MYCALLTYPE DoesSupportFrame(MYID id) override;
    virtual const char* MYCALLTYPE GetName() override;
    virtual MYRESULT MYCALLTYPE Init(MYID frameType) override;

    virtual void MYCALLTYPE AddRef() override;
    virtual void MYCALLTYPE Release()  override;
    virtual MYRESULT MYCALLTYPE QueryInterface(MYID riid, void** ppvObject) override;
private:
    MYRESULT ProcessFrame1(MyUnknown* frame);
    MYRESULT ProcessFrame2(MyUnknown* frame);
    MYRESULT ProcessFrameOGL(MyUnknown* frame);

    uint64_t mCounter = 1;
    std::optional<MYID> mInitedFrameType;
};
