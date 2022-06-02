#include "config.h"

#if HAS_GPIOD

#include <stddef.h>

#include <gpiod.h>
#include <time.h>

#include "rts_pulse_output_gpiod.h"

static void enable(struct rts_pulse_output *pulse_output)
{
    gpiod_line_request_output((struct gpiod_line *)pulse_output->user_data_ptr,
                              "open_rts", false);
}

static void disable(struct rts_pulse_output *pulse_output)
{
    gpiod_line_request_input((struct gpiod_line *)pulse_output->user_data_ptr,
                             "open_rts");
}

static void send_pulse(struct rts_pulse_output *pulse_output, bool state,
                       uint32_t micros)
{
    gpiod_line_set_value((struct gpiod_line *)pulse_output->user_data_ptr,
                         state);

    const struct timespec time = {.tv_nsec = micros * 1000};
    nanosleep(&time, NULL);
}

static void close(struct rts_pulse_output *pulse_output)
{
    gpiod_line_close_chip((struct gpiod_line *)pulse_output->user_data_ptr);
}

void rts_pulse_output_init_gpiod(struct rts_pulse_output *pulse_output,
                                 char *device, uint8_t data_pin)
{
    pulse_output->enable     = enable;
    pulse_output->disable    = disable;
    pulse_output->send_pulse = send_pulse;
    pulse_output->close      = close;

    // TODO: NULL check gpiod_*
    struct gpiod_chip *gpio_chip = gpiod_chip_open(device);
    pulse_output->user_data_ptr  = gpiod_chip_get_line(gpio_chip, data_pin);
}

#endif /* HAS_GPIOD */