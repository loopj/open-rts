#include "config.h"

#if OPENRTS_HAS_ARDUINO && OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSPulseSource_ArduinoGPIO.h"

#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266)
#define INTERRUPT_ATTR IRAM_ATTR
#else
#define INTERRUPT_ATTR
#endif

static RTSPulseSource_ArduinoGPIO* interruptInstance = NULL;

static void INTERRUPT_ATTR isr0() {
    if(interruptInstance) {
        interruptInstance->interruptReady = true;
    }
}

static void rts_pulse_source_enable_gpio(struct rts_pulse_source *pulse_source) {
    RTSPulseSource_ArduinoGPIO *inst = (RTSPulseSource_ArduinoGPIO *)pulse_source->user_data_ptr;

    pinMode(inst->dataPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(inst->dataPin), isr0, CHANGE);
}

static void rts_pulse_source_disable_gpio(struct rts_pulse_source *pulse_source) {
    RTSPulseSource_ArduinoGPIO *inst = (RTSPulseSource_ArduinoGPIO *)pulse_source->user_data_ptr;

    detachInterrupt(digitalPinToInterrupt(inst->dataPin));
}

static void rts_pulse_source_update_gpio(struct rts_pulse_source *pulse_source) {
    RTSPulseSource_ArduinoGPIO *inst = (RTSPulseSource_ArduinoGPIO *)pulse_source->user_data_ptr;

    if(inst->interruptReady) {
        bool state = !digitalRead(inst->dataPin);
        unsigned long now = micros();
        unsigned long time_in_state = now - inst->lastUpdated;

        if(pulse_source->frame_builder) {
            rts_frame_builder_handle_pulse(pulse_source->frame_builder, state, time_in_state);
        }

        inst->interruptReady = false;
        inst->lastUpdated = now;
    }
}

RTSPulseSource_ArduinoGPIO::RTSPulseSource_ArduinoGPIO(uint8_t dataPin, bool interruptCapable) {
    this->dataPin = dataPin;
    this->interruptCapable = interruptCapable;

    rts_pulse_source::enable = rts_pulse_source_enable_gpio;
    rts_pulse_source::disable = rts_pulse_source_disable_gpio;
    rts_pulse_source::update = rts_pulse_source_update_gpio;
    rts_pulse_source::user_data_ptr = this;

    if(interruptCapable) {
        if(interruptInstance) {
            // TODO: Log an error
        }

        interruptInstance = this;
    }
}

#endif // #if OPENRTS_HAS_ARDUINO && OPENRTS_INCLUDE_CPP_BINDINGS