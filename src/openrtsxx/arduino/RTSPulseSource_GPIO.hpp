#ifndef RTS_PULSE_SOURCE_ARDUINO_GPIO_HPP
#define RTS_PULSE_SOURCE_ARDUINO_GPIO_HPP

#include "../RTSPulseSource.hpp"

class RTSPulseSource_GPIO : public RTSPulseSource
{
  public:
    RTSPulseSource_GPIO(uint8_t dataPin);

  private:
    uint8_t dataPin;

    bool interruptReady  = false;
    uint32_t lastUpdated = 0;

    static void isr0();
    static void enableFn(struct rts_pulse_source *pulse_source);
    static void disableFn(struct rts_pulse_source *pulse_source);
    static void updateFn(struct rts_pulse_source *pulse_source);

    static RTSPulseSource_GPIO *interruptInstance;
};

#endif // RTS_PULSE_SOURCE_ARDUINO_GPIO_HPP