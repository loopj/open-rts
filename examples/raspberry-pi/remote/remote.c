#include <gpiod.h>
#include <stdio.h>

#include "open_rts.h"

#define BTN_PIN_MY   5
#define BTN_PIN_UP   6
#define BTN_PIN_DOWN 12
#define BTN_PIN_PROG 13
#define DATA_PIN     24

void init_radio(struct spi_module *spi, struct rfm69 *radio)
{
    spi_module_init_linux(spi, "/dev/spidev0.1");

    rfm69_init(radio, spi, true);
    rfm69_configure_for_rts(radio);

    rfm69_set_mode(radio, RFM69_MODE_TX);
}

int main(int argc, char **argv)
{
    // Initialize the radio
    struct spi_module spi = {};
    struct rfm69 radio;
    init_radio(&spi, &radio);

    // Set up the buttons
    struct gpiod_chip *gpio_chip = gpiod_chip_open("/dev/gpiochip0");
    struct gpiod_line *btn_up    = gpiod_chip_get_line(gpio_chip, BTN_PIN_UP);
    struct gpiod_line *btn_down  = gpiod_chip_get_line(gpio_chip, BTN_PIN_DOWN);
    struct gpiod_line *btn_my    = gpiod_chip_get_line(gpio_chip, BTN_PIN_MY);
    struct gpiod_line *btn_prog  = gpiod_chip_get_line(gpio_chip, BTN_PIN_PROG);

    gpiod_line_request_input_flags(btn_up, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    gpiod_line_request_input_flags(btn_down, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    gpiod_line_request_input_flags(btn_my, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    gpiod_line_request_input_flags(btn_prog, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);

    // Set up pulse output
    struct rts_pulse_output pulse_output;
    rts_pulse_output_init_gpiod(&pulse_output, "/dev/gpiochip0", DATA_PIN);

    // Store remote rolling codes in ESP non-volatile storage
    struct rts_remote_store remote_store;
    rts_remote_store_init_memory(&remote_store, 1);

    // Set up the remote
    struct rts_remote remote;
    rts_remote_init(&remote, &pulse_output, &remote_store, RTS_TIMINGS_DEFAULT);

    // Check for button presses periodically, and send commands
    uint8_t last_command = 0;
    while (1) {
        uint8_t command = 0;
        command |= !gpiod_line_get_value(btn_my);
        command |= !gpiod_line_get_value(btn_up) << 1;
        command |= !gpiod_line_get_value(btn_down) << 2;
        command |= !gpiod_line_get_value(btn_prog) << 3;

        if (command) {
            printf("Sending command: %d\n", command);
            rts_remote_send_command(&remote, 0xC0FFEE, command,
                                    last_command == command);
        }

        last_command = command;
    }

    return 0;
}
