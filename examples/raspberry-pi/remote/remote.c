#include <gpiod.h>
#include <stdio.h>

#include "open_rts.h"

#define BUTTON_PIN_1 5
#define BUTTON_PIN_2 6
#define BUTTON_PIN_3 12
#define BUTTON_PIN_4 13
#define DATA_PIN     24
#define SPI_DEVICE   "/dev/spidev0.1"
#define GPIOD_DEVICE "/dev/gpiochip0"

struct rfm69 radio;
struct rts_pulse_output pulse_output;
struct rts_remote_store remote_store;
struct rts_remote remote;

void init_radio()
{
    // Initialize the SPI module
    struct spi_module spi = {};
    spi_module_init_linux(&spi, SPI_DEVICE);

    // Initialize the radio
    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);

    // Switch to transmit mode
    rfm69_set_mode(&radio, RFM69_MODE_TX);
}

int main(int argc, char **argv)
{
    // Initialize the radio
    init_radio();

    // Set up the buttons
    struct gpiod_chip *gpio_chip = gpiod_chip_open(GPIOD_DEVICE);
    struct gpiod_line *btn_up    = gpiod_chip_get_line(gpio_chip, BUTTON_PIN_1);
    struct gpiod_line *btn_down  = gpiod_chip_get_line(gpio_chip, BUTTON_PIN_2);
    struct gpiod_line *btn_my    = gpiod_chip_get_line(gpio_chip, BUTTON_PIN_3);
    struct gpiod_line *btn_prog  = gpiod_chip_get_line(gpio_chip, BUTTON_PIN_4);

    gpiod_line_request_input_flags(btn_up, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    gpiod_line_request_input_flags(btn_down, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    gpiod_line_request_input_flags(btn_my, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    gpiod_line_request_input_flags(btn_prog, "openrts",
                                   GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);

    // Set up pulse output
    rts_pulse_output_init_gpiod(&pulse_output, GPIOD_DEVICE, DATA_PIN);

    // Store remote rolling codes in memory
    rts_remote_store_init_memory(&remote_store, 1);

    // Set up the remote
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
