#include <gpiod.h>
#include <stdio.h>
#include <time.h>

#include "open_rts.h"

#define BTN_MODE     5
#define DATA_PIN     24
#define SPI_DEVICE   "/dev/spidev0.1"
#define GPIOD_DEVICE "/dev/gpiochip0"

struct rfm69 radio;
struct rts_pulse_source pulse_source;
struct rts_remote_store remote_store;
struct rts_receiver receiver;

void init_radio()
{
    struct spi_module spi = {};
    spi_module_init_linux(&spi, SPI_DEVICE);

    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);

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

int main(int argc, char **argv)
{
    // Initialize the radio
    init_radio();

    // Set up the mode button
    struct gpiod_chip *gpio_chip = gpiod_chip_open(GPIOD_DEVICE);
    struct gpiod_line *btn_mode  = gpiod_chip_get_line(gpio_chip, BTN_MODE);
    gpiod_line_request_input_flags(btn_mode, "openrts",
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

    // Check for new pulses
    bool button_state     = false;
    uint32_t last_updated = millis();
    while (1) {
        rts_receiver_update(&receiver);

        bool new_state = !gpiod_line_get_value(btn_mode);
        if (new_state != button_state) {
            uint32_t now = millis();
            if (!new_state) {
                if (now - last_updated > 2000) {
                    // Press button for > 2 seconds to clear paired remotes
                    rts_receiver_forget_all_remotes(&receiver);
                    rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_COMMAND);
                } else {
                    // Short button press enters programming mode
                    rts_receiver_set_mode(&receiver,
                                          RTS_RECEIVER_MODE_PROGRAMMING);
                }
            }

            button_state = new_state;
            last_updated = now;
        }
    }

    return 0;
}
