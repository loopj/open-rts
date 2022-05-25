#include <gpiod.h>
#include <stdio.h>
#include <time.h>

#include "open_rts.h"

#define DATA_PIN     24
#define BUTTON_PIN_1 5
#define SPI_DEVICE   "/dev/spidev0.1"
#define GPIOD_DEVICE "/dev/gpiochip0"

struct rfm69 radio;
struct rts_pulse_source pulse_source;
struct rts_remote_store remote_store;
struct rts_receiver receiver;

void init_radio()
{
    // Initialize the SPI module
    struct spi_module spi = {};
    spi_module_init_linux(&spi, SPI_DEVICE);

    // Initialize the radio
    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);

    // Switch to receive mode
    rfm69_set_mode(&radio, RFM69_MODE_RX);
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
        printf("[Mode Changed] Receiver Off\n");
        break;
    case RTS_RECEIVER_MODE_PROGRAMMING:
        printf("[Mode Changed] Programming Mode\n");
        break;
    case RTS_RECEIVER_MODE_COMMAND:
        printf("[Mode Changed] Command Mode\n");
        break;
    }
}

uint32_t millis()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + ts.tv_nsec / 1000000;
}

void poll_button(struct gpiod_line *button)
{
    static uint8_t event_fired   = 0;
    static bool last_state       = false;
    static uint32_t pressed_time = 0;

    // Check if button is pressed
    bool state   = !gpiod_line_get_value(button);
    uint32_t now = millis();
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

int main(int argc, char **argv)
{
    // Initialize the radio
    init_radio();

    // Set up the receiver "mode" button
    struct gpiod_chip *gpio_chip = gpiod_chip_open(GPIOD_DEVICE);
    struct gpiod_line *button    = gpiod_chip_get_line(gpio_chip, BUTTON_PIN_1);
    gpiod_line_request_input_flags(button, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);

    // Set up a GPIO pulse source
    rts_pulse_source_init_gpiod(&pulse_source, GPIOD_DEVICE, DATA_PIN);
    rts_pulse_source_enable(&pulse_source);

    // Set up remote store for remote pairing
    rts_remote_store_init_memory(&remote_store, 1);

    // Create a receiver
    rts_receiver_init(&receiver, &pulse_source, &remote_store);
    rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_COMMAND);
    rts_receiver_set_event_callback(&receiver, event_callback, NULL);
    rts_receiver_set_mode_callback(&receiver, mode_callback, NULL);

    while (1) {
        // Update receiver with new pulses
        rts_receiver_update(&receiver);

        // Check for button presses
        poll_button(button);
    }

    return 0;
}
