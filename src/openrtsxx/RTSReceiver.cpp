#include "RTSReceiver.hpp"

RTSReceiver::RTSReceiver(RTSPulseSource *pulseSource,
                         RTSRemoteStore *remoteStore)
{
    rts_receiver_init(this, pulseSource, remoteStore);
}

void RTSReceiver::setFrameCallback(FrameCallback callback, void *userData)
{
    this->frameCallback         = callback;
    this->frameCallbackUserData = userData;

    rts_receiver_set_frame_callback(this, frameCallbackWrapper, this);
}

void RTSReceiver::setModeCallback(ModeCallback callback, void *userData)
{
    this->modeCallback         = callback;
    this->modeCallbackUserData = userData;

    rts_receiver_set_mode_callback(this, modeCallbackWrapper, this);
}

void RTSReceiver::setMode(enum rts_receiver_mode mode)
{
    rts_receiver_set_mode(this, mode);
}

void RTSReceiver::forgetAllRemotes()
{
    rts_receiver_forget_all_remotes(this);
}

void RTSReceiver::update()
{
    rts_receiver_update(this);
}

void RTSReceiver::frameCallbackWrapper(enum rts_receiver_event event,
                                       rts_frame *frame, void *userData)
{
    RTSReceiver *inst = (RTSReceiver *)userData;

    RTSFrame convertedFrame(frame);
    inst->frameCallback(event, &convertedFrame, inst->frameCallbackUserData);
}

void RTSReceiver::modeCallbackWrapper(enum rts_receiver_mode mode,
                                      void *userData)
{
    RTSReceiver *inst = (RTSReceiver *)userData;
    inst->modeCallback(mode, inst->modeCallbackUserData);
}