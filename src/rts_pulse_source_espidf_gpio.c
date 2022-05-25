#if defined(ESP_PLATFORM)

#include "rts_pulse_source_espidf_gpio.h"

#include "esp_timer.h"
#include "driver/gpio.h"

#include <stdio.h>

static void enable(struct rts_pulse_source *pulse_source)
{
}

static void disable(struct rts_pulse_source *pulse_source)
{
}

static void update(struct rts_pulse_source *pulse_source)
{
    bool state = !gpio_get_level(pulse_source->user_data_int);
    if (state != pulse_source->last_state) {
        int64_t now            = esp_timer_get_time();
        uint32_t time_in_state = now - pulse_source->last_updated;

        rts_frame_builder_handle_pulse(pulse_source->frame_builder, state,
                                       time_in_state);

        pulse_source->last_state   = state;
        pulse_source->last_updated = now;
    }
}

void rts_pulse_source_init_espidf_gpio(struct rts_pulse_source *pulse_source,
                                       uint8_t data_pin)
{
    pulse_source->enable        = enable;
    pulse_source->disable       = disable;
    pulse_source->update        = update;
    pulse_source->frame_builder = NULL;
    pulse_source->user_data_int = data_pin;
    pulse_source->last_state    = false;
    pulse_source->last_updated  = esp_timer_get_time();
}

#endif // defined(ESP_PLATFORM)