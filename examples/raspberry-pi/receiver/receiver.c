#include <gpiod.h>
#include <stdio.h>

#include "open_rts.h"

#define BTN_MODE 5
#define DATA_PIN 24

void init_radio(struct spi_module *spi, struct rfm69 *radio)
{
    spi_module_init_linux(spi, "/dev/spidev0.1");

    rfm69_init(radio, spi, true);
    rfm69_configure_for_rts(radio);

    rfm69_set_mode(radio, RFM69_MODE_RX);
}

void event_callback(enum rts_receiver_event event, struct rts_frame *frame,
                    void *user_data)
{
    printf("Got an RTS event!\n");
    printf("Command: %X\n", frame->command);
    printf("Remote: 0x%06X\n", frame->remote_address);
    printf("Rolling Code: 0x%04X\n\n", frame->rolling_code);
}

void mode_callback(enum rts_receiver_mode mode, void *user_data)
{
    printf("Receiver mode changed\n");
}

int main(int argc, char **argv)
{
    // Initialize the radio
    struct spi_module spi = {};
    struct rfm69 radio;
    init_radio(&spi, &radio);

    // Set up the mode button
    struct gpiod_chip *gpio_chip = gpiod_chip_open("/dev/gpiochip0");
    struct gpiod_line *btn_mode  = gpiod_chip_get_line(gpio_chip, BTN_MODE);
    gpiod_line_request_input_flags(btn_mode, "openrts",
                                GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);

    // Set up a GPIO pulse source, send pulses to the framebuilder
    struct rts_pulse_source pulse_source;
    rts_pulse_source_init_gpiod(&pulse_source, "/dev/gpiochip0", DATA_PIN);
    rts_pulse_source_enable(&pulse_source);

    // Set up remote store for remote pairing
    struct rts_remote_store remote_store;
    rts_remote_store_init_memory(&remote_store, 1);

    // Create a receiver
    struct rts_receiver receiver;
    rts_receiver_init(&receiver, &pulse_source, &remote_store);
    rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_COMMAND);
    rts_receiver_set_event_callback(&receiver, event_callback, NULL);
    rts_receiver_set_mode_callback(&receiver, mode_callback, NULL);

    // Check for new pulses
    while (1) {
        rts_receiver_update(&receiver);

        // TODO: Single button press enters programming mode
        // TODO: Long button press clears all paired remotes from memory

        if(!gpiod_line_get_value(btn_mode)) {
            printf("Mode button pressed\n");
        }
    }

    return 0;
}
