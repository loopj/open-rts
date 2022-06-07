#ifndef RTS_PULSE_OUTPUT_ARDUINO_GPIO_CPP_H
#define RTS_PULSE_OUTPUT_ARDUINO_GPIO_CPP_H

#include "bindings/cpp/RTSPulseOutput.h"

class RTSPulseOutput_ArduinoGPIO : public RTSPulseOutput
{
  public:
    RTSPulseOutput_ArduinoGPIO(uint8_t dataPin);
    uint8_t dataPin;
};

#endif // RTS_PULSE_OUTPUT_ARDUINO_GPIO_CPP_H