#include "config.h"

#if HAS_GPIOD

#include <time.h>

#include <gpiod.h>

#include "rts_pulse_output_gpiod.h"

static void enable(struct rts_pulse_output *pulse_output)
{
    struct gpiod_line *line = (struct gpiod_line *)pulse_output->user_data_ptr;
    gpiod_line_request_output(line, "openrts", false);
}

static void disable(struct rts_pulse_output *pulse_output)
{
}

static void send_pulse(struct rts_pulse_output *pulse_output, bool state,
                       uint32_t micros)
{
    struct gpiod_line *line = (struct gpiod_line *)pulse_output->user_data_ptr;
    gpiod_line_set_value(line, state);

    const struct timespec t = {
        .tv_nsec = micros * 1000,
    };
    nanosleep(&t, NULL);
}

void rts_pulse_output_init_gpiod(struct rts_pulse_output *pulse_output,
                                 char *device, uint8_t data_pin)
{
    pulse_output->enable     = enable;
    pulse_output->disable    = disable;
    pulse_output->send_pulse = send_pulse;

    // TODO: NULL check gpiod_*
    struct gpiod_chip *gpio_chip = gpiod_chip_open(device);
    pulse_output->user_data_ptr  = gpiod_chip_get_line(gpio_chip, data_pin);
}

#endif /* HAS_GPIOD */