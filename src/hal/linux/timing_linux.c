#if defined (__unix__)

#include <time.h>

#include "hal/timing.h"

uint32_t hal_millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + ts.tv_nsec / 1000000;
}

uint64_t hal_micros() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000000)  + ts.tv_nsec / 1000;
}

#endif