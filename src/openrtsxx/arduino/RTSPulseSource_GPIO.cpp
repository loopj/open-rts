#include <openrts/config.h>

#if OPENRTS_HAS_ARDUINO_GPIO

#include <Arduino.h>

#include "RTSPulseSource_GPIO.hpp"

#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266)
#define INTERRUPT_ATTR IRAM_ATTR
#else
#define INTERRUPT_ATTR
#endif

RTSPulseSource_GPIO *RTSPulseSource_GPIO::interruptInstance =
    NULL;

void INTERRUPT_ATTR RTSPulseSource_GPIO::isr0()
{
    if (interruptInstance) {
        interruptInstance->interruptReady = true;
    }
}

void RTSPulseSource_GPIO::enableFn(struct rts_pulse_source *pulse_source)
{
    RTSPulseSource_GPIO *inst =
        (RTSPulseSource_GPIO *)pulse_source->user_data_ptr;

    pinMode(inst->dataPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(inst->dataPin), isr0, CHANGE);
}

void RTSPulseSource_GPIO::disableFn(
    struct rts_pulse_source *pulse_source)
{
    RTSPulseSource_GPIO *inst =
        (RTSPulseSource_GPIO *)pulse_source->user_data_ptr;

    detachInterrupt(digitalPinToInterrupt(inst->dataPin));
}

void RTSPulseSource_GPIO::updateFn(struct rts_pulse_source *pulse_source)
{
    RTSPulseSource_GPIO *inst =
        (RTSPulseSource_GPIO *)pulse_source->user_data_ptr;

    if (inst->interruptReady) {
        bool state                  = !digitalRead(inst->dataPin);
        unsigned long now           = micros();
        unsigned long time_in_state = now - inst->lastUpdated;

        if (pulse_source->frame_builder) {
            rts_frame_builder_handle_pulse(pulse_source->frame_builder, state,
                                           time_in_state);
        }

        inst->interruptReady = false;
        inst->lastUpdated    = now;
    }
}

RTSPulseSource_GPIO::RTSPulseSource_GPIO(uint8_t dataPin)
{
    this->dataPin = dataPin;

    rts_pulse_source::enable        = enableFn;
    rts_pulse_source::disable       = disableFn;
    rts_pulse_source::update        = updateFn;
    rts_pulse_source::user_data_ptr = this;

    if (interruptInstance) {
        // TODO: Log an error
    }

    interruptInstance = this;
}

#endif // OPENRTS_HAS_ARDUINO_GPIO