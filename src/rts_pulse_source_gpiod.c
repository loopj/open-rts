#include "config.h"

#if HAS_GPIOD

#include "rts_pulse_source_gpiod.h"

#include <gpiod.h>
#include <stdlib.h>
#include <time.h>

struct gpiod_data {
    struct gpiod_line *gpio_line;
    bool last_state;
    uint64_t last_updated;
};

static uint64_t micros()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000000) + ts.tv_nsec / 1000;
}

static void enable(struct rts_pulse_source *pulse_source)
{
    struct gpiod_data *data = (struct gpiod_data *)pulse_source->user_data_ptr;
    gpiod_line_request_input(data->gpio_line, "openrts");
    // TODO: Check for -1 return code in gpiod_line_request_input
}

static void disable(struct rts_pulse_source *pulse_source)
{
}

static void update(struct rts_pulse_source *pulse_source)
{
    struct gpiod_data *data = (struct gpiod_data *)pulse_source->user_data_ptr;
    bool state              = gpiod_line_get_value(data->gpio_line);
    // TODO: Check for -1 return code in gpiod_line_get_value
    if (state != data->last_state) {
        uint64_t now           = micros();
        uint32_t time_in_state = now - data->last_updated;

        rts_frame_builder_handle_pulse(pulse_source->frame_builder, state,
                                       time_in_state);

        data->last_state   = state;
        data->last_updated = now;
    }
}

void rts_pulse_source_init_gpiod(struct rts_pulse_source *pulse_source,
                                 char *device, uint8_t data_pin)
{
    struct gpiod_data *data      = malloc(sizeof(struct gpiod_data));
    struct gpiod_chip *gpio_chip = gpiod_chip_open(device);
    data->gpio_line              = gpiod_chip_get_line(gpio_chip, data_pin);

    // TODO: NULL check gpiod_*

    pulse_source->enable        = enable;
    pulse_source->disable       = disable;
    pulse_source->update        = update;
    pulse_source->frame_builder = NULL;
    pulse_source->user_data_ptr = data;
}

#endif /* HAS_GPIOD */