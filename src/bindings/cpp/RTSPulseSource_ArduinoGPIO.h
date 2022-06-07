#ifndef RTS_PULSE_SOURCE_ARDUINO_GPIO_CPP_H
#define RTS_PULSE_SOURCE_ARDUINO_GPIO_CPP_H

#include "RTSPulseSource.h"

class RTSPulseSource_ArduinoGPIO : public RTSPulseSource
{
  public:
    RTSPulseSource_ArduinoGPIO(uint8_t dataPin, bool interruptCapable = true);

    uint8_t dataPin;
    bool interruptCapable;

    bool interruptReady  = false;
    uint32_t lastUpdated = 0;
};

#endif // RTS_PULSE_SOURCE_ARDUINO_GPIO_CPP_H