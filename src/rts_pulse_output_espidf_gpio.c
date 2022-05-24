#if defined(ESP_PLATFORM)

#include "rts_pulse_output_espidf_gpio.h"

#include <stdio.h>

#include "driver/gpio.h"
#include "rom/ets_sys.h"

static void enable(struct rts_pulse_output *pulse_output)
{
    gpio_set_direction(pulse_output->user_data_int, GPIO_MODE_OUTPUT);
}

static void disable(struct rts_pulse_output *pulse_output)
{
}

static void send_pulse(struct rts_pulse_output *pulse_output, bool state,
                       uint32_t micros)
{
    gpio_set_level(pulse_output->user_data_int, state);
    ets_delay_us(micros);
}

void rts_pulse_output_init_espidf_gpio(struct rts_pulse_output *pulse_output,
                                       uint8_t data_pin)
{
    pulse_output->send_pulse    = send_pulse;
    pulse_output->enable        = enable;
    pulse_output->disable       = disable;
    pulse_output->user_data_int = data_pin;
}

#endif