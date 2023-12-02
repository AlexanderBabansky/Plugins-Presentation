#include "VideoProcessorInterface.h"
#include <vector>

class VideoProcessorHost : public VideoProcessorHostInterface {
public:
    VideoProcessorHost() = default;
    ~VideoProcessorHost();
    void printRegisteredPlugins();

    virtual void MYCALLTYPE AddPlugin(MyUnknown* plugin) override;

    virtual void MYCALLTYPE AddRef() override;
    virtual void MYCALLTYPE Release()  override;
    virtual MYRESULT MYCALLTYPE QueryInterface(MYID riid, void** ppvObject) override;

    int getPluginsCount() const;    
    VideoProcessorInterface* getProcessor(int index);
private:
    std::vector<VideoProcessorInterface*> mPlugins;
};
