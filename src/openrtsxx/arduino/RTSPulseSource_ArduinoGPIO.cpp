#include <openrts/config.h>

#if OPENRTS_HAS_ARDUINO_GPIO

#include <Arduino.h>

#include "RTSPulseSource_ArduinoGPIO.hpp"

#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266)
#define INTERRUPT_ATTR IRAM_ATTR
#else
#define INTERRUPT_ATTR
#endif

RTSPulseSource_ArduinoGPIO *RTSPulseSource_ArduinoGPIO::interruptInstance =
    NULL;

void INTERRUPT_ATTR RTSPulseSource_ArduinoGPIO::isr0()
{
    if (interruptInstance) {
        interruptInstance->interruptReady = true;
    }
}

void RTSPulseSource_ArduinoGPIO::enableFn(struct rts_pulse_source *pulse_source)
{
    RTSPulseSource_ArduinoGPIO *inst =
        (RTSPulseSource_ArduinoGPIO *)pulse_source->user_data_ptr;

    pinMode(inst->dataPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(inst->dataPin), isr0, CHANGE);
}

void RTSPulseSource_ArduinoGPIO::disableFn(
    struct rts_pulse_source *pulse_source)
{
    RTSPulseSource_ArduinoGPIO *inst =
        (RTSPulseSource_ArduinoGPIO *)pulse_source->user_data_ptr;

    detachInterrupt(digitalPinToInterrupt(inst->dataPin));
}

void RTSPulseSource_ArduinoGPIO::updateFn(struct rts_pulse_source *pulse_source)
{
    RTSPulseSource_ArduinoGPIO *inst =
        (RTSPulseSource_ArduinoGPIO *)pulse_source->user_data_ptr;

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

RTSPulseSource_ArduinoGPIO::RTSPulseSource_ArduinoGPIO(uint8_t dataPin)
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