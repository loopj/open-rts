#ifndef RTS_PULSE_OUTPUT_ARDUINO_GPIO_HPP
#define RTS_PULSE_OUTPUT_ARDUINO_GPIO_HPP

#include "../RTSPulseOutput.hpp"

class RTSPulseOutput_GPIO : public RTSPulseOutput
{
  public:
    RTSPulseOutput_GPIO(uint8_t dataPin);
    uint8_t dataPin;
};

#endif // RTS_PULSE_OUTPUT_ARDUINO_GPIO_HPP