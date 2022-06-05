#pragma once

#include "RTSPulseOutput.h"

class RTSPulseOutput_ArduinoGPIO : public RTSPulseOutput {
  public:
    RTSPulseOutput_ArduinoGPIO(uint8_t dataPin);
    uint8_t dataPin;
};