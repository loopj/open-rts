#if defined(ESP_PLATFORM)

#include <esp_timer.h>

#include "hal/timing.h"

uint32_t hal_millis() {
    return (uint32_t)(esp_timer_get_time() / 1000);
}

#endif