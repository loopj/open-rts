#pragma once

#include "RTSPulseSource.h"

class RTSPulseSource_ArduinoGPIO : public RTSPulseSource {
  public:
    RTSPulseSource_ArduinoGPIO(uint8_t dataPin, bool interruptCapable=true);

    uint8_t dataPin;
    bool interruptCapable;

    bool interruptReady = false;
    uint32_t lastUpdated = 0;
};