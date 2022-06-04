#pragma once

#include "RTSPulseSource.h"

class RTSPulseSource_GPIO : public RTSPulseSource {
  public:
    RTSPulseSource_GPIO(uint8_t dataPin, bool interruptCapable);

    uint8_t dataPin;
    bool interruptCapable;

    bool interruptReady = false;
    uint32_t lastUpdated = 0;
};