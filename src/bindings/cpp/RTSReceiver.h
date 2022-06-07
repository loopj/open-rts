#ifndef RTS_RECEIVER_CPP_H
#define RTS_RECEIVER_CPP_H

#include "rts_receiver.h"

#include "RTSPulseSource.h"
#include "RTSRemoteStore.h"

class RTSReceiver : protected rts_receiver
{
  public:
    typedef void (*FrameCallback)(enum rts_receiver_event event,
                                  RTSFrame *frame, void *userData);
    typedef void (*ModeCallback)(enum rts_receiver_mode mode, void *userData);

    RTSReceiver(RTSPulseSource *pulseSource, RTSRemoteStore *remoteStore)
    {
        rts_receiver_init(this, pulseSource, remoteStore);
    }

    void setFrameCallback(FrameCallback callback, void *userData = nullptr)
    {
        this->frameCallback         = callback;
        this->frameCallbackUserData = userData;

        rts_receiver_set_frame_callback(
            this,
            [](enum rts_receiver_event event, rts_frame *frame,
               void *userData) {
                RTSReceiver *inst = (RTSReceiver *)userData;

                RTSFrame convertedFrame(frame);
                inst->frameCallback(event, &convertedFrame,
                                    inst->frameCallbackUserData);
            },
            this);
    }

    void setModeCallback(ModeCallback callback, void *userData = nullptr)
    {
        this->modeCallback         = callback;
        this->modeCallbackUserData = userData;

        rts_receiver_set_mode_callback(
            this,
            [](enum rts_receiver_mode mode, void *userData) {
                RTSReceiver *inst = (RTSReceiver *)userData;
                inst->modeCallback(mode, inst->modeCallbackUserData);
            },
            this);
    }

    void setMode(enum rts_receiver_mode mode)
    {
        rts_receiver_set_mode(this, mode);
    }

    void forgetAllRemotes()
    {
        rts_receiver_forget_all_remotes(this);
    }

    void update()
    {
        rts_receiver_update(this);
    }

  private:
    FrameCallback frameCallback = nullptr;
    void *frameCallbackUserData = nullptr;

    ModeCallback modeCallback  = nullptr;
    void *modeCallbackUserData = nullptr;
};

#endif // RTS_RECEIVER_CPP_H