#ifndef RTS_RECEIVER_CPP_H
#define RTS_RECEIVER_CPP_H

#include "rts_receiver.h"

#include "RTSFrame.h"
#include "RTSPulseSource.h"
#include "RTSRemoteStore.h"

class RTSReceiver : protected rts_receiver
{
  public:
    typedef void (*FrameCallback)(enum rts_receiver_event event,
                                  RTSFrame *frame, void *userData);
    typedef void (*ModeCallback)(enum rts_receiver_mode mode, void *userData);

    RTSReceiver(RTSPulseSource *pulseSource, RTSRemoteStore *remoteStore);

    void setFrameCallback(FrameCallback callback, void *userData = nullptr);
    void setModeCallback(ModeCallback callback, void *userData = nullptr);
    void setMode(enum rts_receiver_mode mode);
    void forgetAllRemotes();
    void update();

  private:
    static void frameCallbackWrapper(enum rts_receiver_event event,
                                     rts_frame *frame, void *userData);

    static void modeCallbackWrapper(enum rts_receiver_mode mode,
                                    void *userData);

    FrameCallback frameCallback = nullptr;
    void *frameCallbackUserData = nullptr;

    ModeCallback modeCallback  = nullptr;
    void *modeCallbackUserData = nullptr;
};

#endif // RTS_RECEIVER_CPP_H