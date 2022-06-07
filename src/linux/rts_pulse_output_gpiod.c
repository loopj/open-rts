#include "config.h"

#if OPENRTS_HAS_GPIOD

#include <stddef.h>

#include <gpiod.h>
#include <time.h>

#include "rts_pulse_output_gpiod.h"

static void rts_pulse_output_enable_gpiod(struct rts_pulse_output *pulse_output)
{
    gpiod_line_request_output((struct gpiod_line *)pulse_output->user_data_ptr,
                              "open_rts", false);
}

static void
rts_pulse_output_disable_gpiod(struct rts_pulse_output *pulse_output)
{
    gpiod_line_request_input((struct gpiod_line *)pulse_output->user_data_ptr,
                             "open_rts");
}

static void
rts_pulse_output_send_pulse_gpiod(struct rts_pulse_output *pulse_output,
                                  bool state, uint32_t micros)
{
    gpiod_line_set_value((struct gpiod_line *)pulse_output->user_data_ptr,
                         state);

    const struct timespec time = {.tv_nsec = micros * 1000};
    nanosleep(&time, NULL);
}

static void rts_pulse_output_close_gpiod(struct rts_pulse_output *pulse_output)
{
    gpiod_line_close_chip((struct gpiod_line *)pulse_output->user_data_ptr);
}

void rts_pulse_output_init_gpiod(struct rts_pulse_output *pulse_output,
                                 char *device, uint8_t data_pin)
{
    pulse_output->enable     = rts_pulse_output_enable_gpiod;
    pulse_output->disable    = rts_pulse_output_disable_gpiod;
    pulse_output->send_pulse = rts_pulse_output_send_pulse_gpiod;
    pulse_output->close      = rts_pulse_output_close_gpiod;

    // TODO: NULL check gpiod_*
    struct gpiod_chip *gpio_chip = gpiod_chip_open(device);
    pulse_output->user_data_ptr  = gpiod_chip_get_line(gpio_chip, data_pin);
}

#endif /* OPENRTS_HAS_GPIOD */