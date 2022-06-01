#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
// #define OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
// #define OPENRTS_BOARD_TTGO_LORA32_V21
// #define OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2

// Also define which GPIOs to use for the remote's 4 buttons
// #define OPENRTS_BUTTON_1 0
// #define OPENRTS_BUTTON_2 23
// #define OPENRTS_BUTTON_3 19
// #define OPENRTS_BUTTON_4 18

#include "open_rts.h"

struct rts_radio radio;
struct rts_remote remote;
struct rts_pulse_output pulse_output;
struct rts_remote_store remote_store;
uint8_t last_command = 0;

void init_radio()
{
    // Initialize the ESP-IDF SPI host bus
    spi_bus_config_t buscfg = {
        .miso_io_num   = OPENRTS_RADIO_MISO,
        .mosi_io_num   = OPENRTS_RADIO_MOSI,
        .sclk_io_num   = OPENRTS_RADIO_SCK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    spi_bus_initialize(HSPI_HOST, &buscfg, 1);

    // Initialize SPI module for the radio
    struct spi_module spi = {
        .cs_pin = OPENRTS_RADIO_CS,
        .clock  = 1000000,
        .mode   = 0,
    };
    spi_module_init_espidf(&spi, HSPI_HOST);

    // Initialize radio
    #if defined(OPENRTS_RADIO_TYPE_RFM69)
    rts_radio_init_rfm69(&radio, &spi, true);
    #elif defined(OPENRTS_RADIO_TYPE_SX1278)
    rts_radio_init_sx1278(&radio, &spi, true);
    #endif

    rts_radio_set_mode(&radio, RTS_RADIO_MODE_TRANSMIT);
}

void poll_buttons()
{
    uint8_t command = 0;
    command |= !gpio_get_level(OPENRTS_BUTTON_1);
    command |= !gpio_get_level(OPENRTS_BUTTON_2) << 1;
    command |= !gpio_get_level(OPENRTS_BUTTON_3) << 2;
    command |= !gpio_get_level(OPENRTS_BUTTON_4) << 3;

    if (command) {
        gpio_set_level(OPENRTS_LED, 1);
        rts_remote_send_command(&remote, 0xC0FFEE, command,
                                last_command == command);
        printf("Sending command: %s\n", rts_command_to_string(command));
    } else {
        gpio_set_level(OPENRTS_LED, 0);
    }

    last_command = command;
}

void app_main()
{
    // Configure radio
    init_radio();

    // Set up the remote button GPIOs as inputs
    gpio_set_direction(OPENRTS_BUTTON_1, GPIO_MODE_INPUT);
    gpio_set_direction(OPENRTS_BUTTON_2, GPIO_MODE_INPUT);
    gpio_set_direction(OPENRTS_BUTTON_3, GPIO_MODE_INPUT);
    gpio_set_direction(OPENRTS_BUTTON_4, GPIO_MODE_INPUT);

    // Enable internal pullup resistors on remote button GPIOS
    gpio_set_pull_mode(OPENRTS_BUTTON_1, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(OPENRTS_BUTTON_2, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(OPENRTS_BUTTON_3, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(OPENRTS_BUTTON_4, GPIO_PULLUP_ONLY);

    // Set up the LED
    gpio_set_direction(OPENRTS_LED, GPIO_MODE_OUTPUT);

    // Set up pulse output
    rts_pulse_output_init_espidf_gpio(&pulse_output, OPENRTS_RADIO_DATA);

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
    esp_timer_start_periodic(timer, 10000);
}