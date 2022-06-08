#ifndef OPENRTS_TEST_FIXTURES_H
#define OPENRTS_TEST_FIXTURES_H

#include <stdbool.h>
#include <stdint.h>

struct recorded_pulse {
    bool state;
    uint32_t micros;
};

extern struct recorded_pulse RECORDED_PULSES_UP[];
extern struct recorded_pulse RECORDED_PULSES_MY[];
extern struct recorded_pulse RECORDED_PULSES_DOWN[];
extern struct recorded_pulse RECORDED_PULSES_PROG[];
extern struct recorded_pulse RECORDED_PULSES_BAD_ENCODING[];
extern struct recorded_pulse RECORDED_PULSES_UP_REPEAT[];
extern struct recorded_pulse GENERATED_PULSES_UP[];
extern struct recorded_pulse GENERATED_PULSES_UP_REPEAT[];

#endif // OPENRTS_TEST_FIXTURES_H