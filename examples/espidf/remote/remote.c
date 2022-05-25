#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

#include "open_rts.h"

// Sparkfun ESP32 LoRa 1-CH Gateway
#define SPI_SS   16
#define SPI_MOSI 13
#define SPI_MISO 12
#define SPI_SCLK 14
#define DATA_PIN 32

#define BUTTON_PIN_MY   23
#define BUTTON_PIN_UP   19
#define BUTTON_PIN_DOWN 18
#define BUTTON_PIN_PROG 5
#define LED_PIN         17

#define POLL_TIMEOUT_US 10000

struct rfm69 radio;
struct rts_remote remote;
struct rts_pulse_output pulse_output;
struct rts_remote_store remote_store;
uint8_t last_command = 0;

// SPI bus configuration
spi_bus_config_t spi_bus_config = {
    .miso_io_num   = SPI_MISO,
    .mosi_io_num   = SPI_MOSI,
    .sclk_io_num   = SPI_SCLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
};

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
    rfm69_set_mode(&radio, RFM69_MODE_TX);
}

void poll_buttons()
{
    uint8_t command = 0;
    command |= !gpio_get_level(BUTTON_PIN_MY);
    command |= !gpio_get_level(BUTTON_PIN_UP) << 1;
    command |= !gpio_get_level(BUTTON_PIN_DOWN) << 2;
    command |= !gpio_get_level(BUTTON_PIN_PROG) << 3;

    if (command) {
        gpio_set_level(LED_PIN, 1);
        rts_remote_send_command(&remote, 0xC0FFEE, command,
                                last_command == command);
    } else {
        gpio_set_level(LED_PIN, 0);
    }

    last_command = command;
}

void app_main()
{
    // Initialize the ESP32 SPI bus
    spi_bus_initialize(HSPI_HOST, &spi_bus_config, SPI_DMA_DISABLED);

    // Configure radio
    init_radio();

    // Set up the remote button GPIOs as inputs
    gpio_set_direction(BUTTON_PIN_UP, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_PIN_DOWN, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_PIN_MY, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_PIN_PROG, GPIO_MODE_INPUT);

    // Enable internal pullup resistors on remote button GPIOS
    gpio_set_pull_mode(BUTTON_PIN_UP, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(BUTTON_PIN_DOWN, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(BUTTON_PIN_MY, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(BUTTON_PIN_PROG, GPIO_PULLUP_ONLY);

    // Set up the LED
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // Set up pulse output
    rts_pulse_output_init_espidf_gpio(&pulse_output, DATA_PIN);

    // Store remote rolling codes in ESP non-volatile storage
    rts_remote_store_init_nvs(&remote_store);

    // Set up the remote
    rts_remote_init(&remote, &pulse_output, &remote_store, RTS_TIMINGS_DEFAULT);

    // Check for button presses periodically
    esp_timer_handle_t timer           = NULL;
    esp_timer_create_args_t timer_args = {
        .arg             = NULL,
        .name            = "poll_buttons",
        .dispatch_method = ESP_TIMER_TASK,
        .callback        = poll_buttons,
    };

    esp_timer_create(&timer_args, &timer);
    esp_timer_start_periodic(timer, POLL_TIMEOUT_US);
}