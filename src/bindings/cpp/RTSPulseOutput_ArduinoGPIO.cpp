#include "config.h"

#if OPENRTS_HAS_ARDUINO && OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSPulseOutput_ArduinoGPIO.h"

#include <Arduino.h>

static void rts_pulse_output_enable_gpio(struct rts_pulse_output *pulse_output) {
    pinMode(pulse_output->user_data_int, OUTPUT);
}

static void rts_pulse_output_send_pulse_gpio(struct rts_pulse_output *pulse_output, bool state, uint32_t micros) {
    digitalWrite(pulse_output->user_data_int, state);
    micros < 10000 ? delayMicroseconds(micros) : delay(micros/10000);
}

RTSPulseOutput_ArduinoGPIO::RTSPulseOutput_ArduinoGPIO(uint8_t dataPin) {
    this->user_data_int = dataPin;

    rts_pulse_output::enable = &rts_pulse_output_enable_gpio;
    rts_pulse_output::send_pulse = &rts_pulse_output_send_pulse_gpio;
}

#endif // OPENRTS_HAS_ARDUINO && OPENRTS_INCLUDE_CPP_BINDINGS