#pragma once

#include "RTSPulseOutput.h"

class RTSPulseOutput_GPIO : public RTSPulseOutput {
  public:
    RTSPulseOutput_GPIO(uint8_t dataPin);
    uint8_t dataPin;
};