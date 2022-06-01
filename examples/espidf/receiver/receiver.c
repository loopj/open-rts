#include <stdio.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"

// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
// #define OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
// #define OPENRTS_BOARD_TTGO_LORA32_V21
// #define OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2

// Also define which GPIO to use for the "programming mode" button
// #define OPENRTS_BUTTON_1 0

#include "open_rts.h"

struct rts_radio radio;
struct rts_pulse_source pulse_source;
struct rts_remote_store remote_store;
struct rts_receiver receiver;

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

    rts_radio_set_mode(&radio, RTS_RADIO_MODE_RECEIVE);
}

void event_callback(enum rts_receiver_event event, struct rts_frame *frame,
                    void *user_data)
{
    printf("Got an RTS event!\n");

    switch (event) {
    case RTS_RECEIVER_EVENT_PRESS:
        printf("Button Pressed\n");
        break;
    case RTS_RECEIVER_EVENT_HOLD:
        printf("Button Held\n");
        break;
    case RTS_RECEIVER_EVENT_HOLD_2:
        printf("Button Held (Double)\n");
        break;
    case RTS_RECEIVER_EVENT_HOLD_3:
        printf("Button Held (Triple)\n");
        break;
    default:
        break;
    }

    printf("Command: %X\n", frame->command);
    printf("Remote: 0x%06X\n", frame->remote_address);
    printf("Rolling Code: 0x%04X\n\n", frame->rolling_code);
}

void mode_callback(enum rts_receiver_mode mode, void *user_data)
{
    switch (mode) {
    case RTS_RECEIVER_MODE_OFF:
        gpio_set_level(OPENRTS_LED, 0);
        printf("[Mode Changed] Receiver Off\n");
        break;
    case RTS_RECEIVER_MODE_PROGRAMMING:
        gpio_set_level(OPENRTS_LED, 1);
        printf("[Mode Changed] Programming Mode\n");
        break;
    case RTS_RECEIVER_MODE_COMMAND:
        gpio_set_level(OPENRTS_LED, 0);
        printf("[Mode Changed] Command Mode\n");
        break;
    }
}

void poll_buttons()
{
    static uint8_t event_fired   = 0;
    static bool last_state       = false;
    static uint32_t pressed_time = 0;

    // Check if button is pressed
    bool state   = !gpio_get_level(OPENRTS_BUTTON_1);
    uint32_t now = (uint32_t)(esp_timer_get_time() / 1000);
    if (state == true && last_state == false) {
        pressed_time = now;
        event_fired  = 0;
    }

    // Handle button press/held events
    if (state == true && last_state == true) {
        if (now - pressed_time > 2000 && event_fired == 0) {
            // Button pressed and held for > 2s, enter programming mode
            rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_PROGRAMMING);
            event_fired++;
        } else if (now - pressed_time > 4000 && event_fired == 1) {
            // Button pressed and held for > 4s, forget all paired remotes
            // and go back into command mode
            rts_receiver_forget_all_remotes(&receiver);
            rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_COMMAND);
            event_fired++;
        }
    }

    last_state = state;
}

void app_main()
{
    // Initialize the radio
    init_radio();

    // Set up a ESP-IDF GPIO pulse source
    // This sets up an interrupt-driven FreeRTOS task under the hood
    rts_pulse_source_init_espidf_gpio(&pulse_source, OPENRTS_RADIO_DATA);
    rts_pulse_source_enable(&pulse_source);

    // Set up remote store for remote pairing
    // Store remotes in ESP-IDF's non-volatile storage
    rts_remote_store_init_nvs(&remote_store);

    // Create a receiver, configure callbacks, and enable
    rts_receiver_init(&receiver, &pulse_source, &remote_store);
    rts_receiver_set_event_callback(&receiver, event_callback, NULL);
    rts_receiver_set_mode_callback(&receiver, mode_callback, NULL);
    rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_COMMAND);

    // Initialize the receiver button
    gpio_set_direction(OPENRTS_BUTTON_1, GPIO_MODE_INPUT);
    gpio_set_pull_mode(OPENRTS_BUTTON_1, GPIO_PULLUP_ONLY);

    // Set up the LED
    gpio_set_direction(OPENRTS_LED, GPIO_MODE_OUTPUT);

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
