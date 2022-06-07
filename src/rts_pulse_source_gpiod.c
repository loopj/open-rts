#include "config.h"

#if OPENRTS_HAS_GPIOD

#include "rts_pulse_source_gpiod.h"

#include <gpiod.h>
#include <stdlib.h>
#include <time.h>

// TODO: Check return codes in gpiod_* etc

static uint64_t micros()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000000) + ts.tv_nsec / 1000;
}

static void enable(struct rts_pulse_source *pulse_source)
{
    gpiod_line_request_input(pulse_source->user_data_ptr, "open_rts");
}

static void disable(struct rts_pulse_source *pulse_source)
{
}

static void update(struct rts_pulse_source *pulse_source)
{
    bool state = gpiod_line_get_value(pulse_source->user_data_ptr);
    if (state != pulse_source->last_state) {
        uint64_t now           = micros();
        uint32_t time_in_state = now - pulse_source->last_updated;

        rts_frame_builder_handle_pulse(pulse_source->frame_builder, state,
                                       time_in_state);

        pulse_source->last_state   = state;
        pulse_source->last_updated = now;
    }
}

void rts_pulse_source_init_gpiod(struct rts_pulse_source *pulse_source,
                                 char *device, uint8_t data_pin)
{
    struct gpiod_chip *gpio_chip = gpiod_chip_open(device);
    pulse_source->user_data_ptr  = gpiod_chip_get_line(gpio_chip, data_pin);
    pulse_source->enable         = enable;
    pulse_source->disable        = disable;
    pulse_source->update         = update;
    pulse_source->frame_builder  = NULL;
    pulse_source->last_state     = false;
    pulse_source->last_updated   = micros();
}

#endif /* OPENRTS_HAS_GPIOD */