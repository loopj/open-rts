#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

#include "open_rts.h"

// Feather ESP32 + RFM69
// #define SPI_SS      33
// #define SPI_SCLK    5
// #define SPI_MOSI    18
// #define SPI_MISO    19
// #define DATA_PIN    25

// Sparkfun ESP32 LoRa 1-CH Gateway
#define SPI_SS   16
#define SPI_MOSI 13
#define SPI_MISO 12
#define SPI_SCLK 14
#define DATA_PIN 32

struct rfm69 radio;
struct rts_frame_builder frame_builder;
TaskHandle_t check_for_pulses_task;
bool last_state       = false;
uint64_t last_updated = 0;

void init_spi()
{
    spi_bus_config_t buscfg = {
        .miso_io_num   = SPI_MISO,
        .mosi_io_num   = SPI_MOSI,
        .sclk_io_num   = SPI_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    spi_bus_initialize(HSPI_HOST, &buscfg, 1);
}

void init_radio()
{
    struct spi_module spi = {
        .cs_pin = SPI_SS,
        .clock  = 1000000,
        .mode   = 0,
    };
    spi_module_init_espidf(&spi, HSPI_HOST);

    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);
    rfm69_set_mode(&radio, RFM69_MODE_RX);
}

void print_frame(struct rts_frame *frame, uint8_t count, uint32_t duration,
                 void *user_data)
{
    printf("Detected an RTS Frame!\n");
    printf("Command: %X\n", frame->command);
    printf("Remote: 0x%06X\n", frame->remote_address);
    printf("Rolling Code: 0x%04X (%d)\n\n", frame->rolling_code, count);
}

void IRAM_ATTR isr0()
{
    vTaskNotifyGiveFromISR(check_for_pulses_task, NULL);
    portYIELD_FROM_ISR();
}

void check_for_pulses(void *params)
{
    while (1) {
        // Block indefinitely until interrupt recieved
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Get state and time since last state change
        bool state = !gpio_get_level(DATA_PIN);
        if (state != last_state) {
            int64_t now            = esp_timer_get_time();
            uint32_t time_in_state = now - last_updated;

            rts_frame_builder_handle_pulse(&frame_builder, state,
                                           time_in_state);

            last_state   = state;
            last_updated = now;
        }
    }
}

void app_main()
{
    // Initialize the SPI bus
    init_spi();

    // Initialize the radio
    init_radio();

    // Set up the radio data pin for reading and attach interrupt
    gpio_install_isr_service(0);
    gpio_set_direction(DATA_PIN, GPIO_MODE_INPUT);
    gpio_set_intr_type(DATA_PIN, GPIO_INTR_ANYEDGE);
    gpio_isr_handler_add(DATA_PIN, isr0, NULL);

    // Set up a framebuilder
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder, print_frame, NULL);

    // Check for new pulses
    xTaskCreate(check_for_pulses, "check_for_pulses", 2048, NULL, 5,
                &check_for_pulses_task);
}
