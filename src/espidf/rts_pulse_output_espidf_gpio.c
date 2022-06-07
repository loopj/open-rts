#include "config.h"

#if OPENRTS_HAS_ESPIDF_GPIO

#include "rts_pulse_output_espidf_gpio.h"

#include "driver/gpio.h"
#include "rom/ets_sys.h"

#include <stdio.h>

static void
rts_pulse_output_enable_espidf_gpio(struct rts_pulse_output *pulse_output)
{
    gpio_set_direction(pulse_output->user_data_int, GPIO_MODE_OUTPUT);
}

static void
rts_pulse_output_disable_espidf_gpio(struct rts_pulse_output *pulse_output)
{
    gpio_set_direction(pulse_output->user_data_int, GPIO_MODE_INPUT);
}

static void
rts_pulse_output_send_pulse_espidf_gpio(struct rts_pulse_output *pulse_output,
                                        bool state, uint32_t micros)
{
    gpio_set_level(pulse_output->user_data_int, state);
    ets_delay_us(micros);
}

void rts_pulse_output_init_espidf_gpio(struct rts_pulse_output *pulse_output,
                                       uint8_t data_pin)
{
    pulse_output->send_pulse    = rts_pulse_output_send_pulse_espidf_gpio;
    pulse_output->enable        = rts_pulse_output_enable_espidf_gpio;
    pulse_output->disable       = rts_pulse_output_disable_espidf_gpio;
    pulse_output->user_data_int = data_pin;
    pulse_output->close         = NULL;
}

#endif // OPENRTS_HAS_ESPIDF_GPIO