#if defined(ESP_PLATFORM)

#include "rts_pulse_source_espidf_gpio.h"

#include "driver/gpio.h"
#include "esp_timer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>

static void IRAM_ATTR gpio_isr_handler(void *task_handle)
{
    vTaskNotifyGiveFromISR(task_handle, NULL);
    portYIELD_FROM_ISR();
}

static void check_for_pulses_task(void *params)
{
    while (1) {
        // Block indefinitely until interrupt recieved
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Let pulse source know when state changes
        rts_pulse_source_update((struct rts_pulse_source *)params);
    }
}

static void enable(struct rts_pulse_source *pulse_source)
{
    gpio_intr_enable(pulse_source->user_data_int);
}

static void disable(struct rts_pulse_source *pulse_source)
{
    gpio_intr_disable(pulse_source->user_data_int);
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

    // Check for new pulses
    TaskHandle_t check_for_pulses_handle;
    xTaskCreate(check_for_pulses_task, "check_for_pulses", 2048, pulse_source,
                5, &check_for_pulses_handle);

    // Set up the radio data pin for reading and attach interrupt
    gpio_install_isr_service(0);
    gpio_set_direction(data_pin, GPIO_MODE_INPUT);
    gpio_set_intr_type(data_pin, GPIO_INTR_ANYEDGE);
    gpio_isr_handler_add(data_pin, gpio_isr_handler, check_for_pulses_handle);
    gpio_intr_disable(data_pin);
}

#endif // defined(ESP_PLATFORM)