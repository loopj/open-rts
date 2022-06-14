#ifndef RTS_PULSE_OUTPUT_ARDUINO_GPIO_HPP
#define RTS_PULSE_OUTPUT_ARDUINO_GPIO_HPP

#include "bindings/cpp/RTSPulseOutput.hpp"

class RTSPulseOutput_ArduinoGPIO : public RTSPulseOutput
{
  public:
    RTSPulseOutput_ArduinoGPIO(uint8_t dataPin);
    uint8_t dataPin;
};

#endif // RTS_PULSE_OUTPUT_ARDUINO_GPIO_HPP