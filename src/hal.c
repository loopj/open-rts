#include "hal.h"

#if defined(ARDUINO)
#include <Arduino.h>
uint32_t hal_millis() {
    return millis();
}
#elif defined(__XTENSA__)
#include <esp_timer.h>
uint32_t hal_millis() {
    return (uint32_t)(esp_timer_get_time() / 1000);
}
#elif defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <time.h>
uint32_t hal_millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + ts.tv_nsec / 1000000;
}
#elif defined(_WIN32)
#include <sysinfoapi.h>
uint32_t hal_millis() {
    return GetTickCount();
}
#endif