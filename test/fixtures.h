#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct recorded_pulse_t {
    bool state;
    uint32_t micros;
} recorded_pulse_t;

extern recorded_pulse_t RECORDED_PULSES_UP[];
extern recorded_pulse_t RECORDED_PULSES_MY[];
extern recorded_pulse_t RECORDED_PULSES_DOWN[];
extern recorded_pulse_t RECORDED_PULSES_PROG[];
extern recorded_pulse_t RECORDED_PULSES_BAD_ENCODING[];
extern recorded_pulse_t RECORDED_PULSES_UP_REPEAT[];
extern recorded_pulse_t GENERATED_PULSES_UP[];
extern recorded_pulse_t GENERATED_PULSES_UP_REPEAT[];