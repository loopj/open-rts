/*
 * Simple RTS Remote Example
 *
 * This example implements a 4-button, single-address RTS remote control.
 * It takes button inputs, assembles them into RTS frames, then outputs them
 * to the attached radio module.
 *
 * Rolling codes are persisted to a file "remotes.dat"
 *
 * Pressing and holding a button will send "repeat" frames, which won't
 * increase the rolling code.
 */

//
// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
//

// #define OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
// #define OPENRTS_BOARD_RASPBERRY_PI_RFM96_BONNET

//
// Uncomment all of the following and configure which GPIOs to use for input
//

// #define OPENRTS_BUTTON_1 0   // My button
// #define OPENRTS_BUTTON_2 23  // Up button
// #define OPENRTS_BUTTON_3 19  // Down button
// #define OPENRTS_BUTTON_4 18  // Prog button

#include <gpiod.h>
#include <stdio.h>

#include <openrts.h>

struct rts_radio radio;
struct rts_pulse_output pulse_output;
struct rts_remote_store remote_store;
struct rts_remote remote;

void init_radio()
{
    // Initialize SPI module
    struct spi_module spi = {
        .clock = 1000000,
    };
    spi_module_init_linux(&spi, OPENRTS_SPI_DEVICE);

    // Initialize radio
    #if defined(OPENRTS_RADIO_TYPE_RFM69)
    rts_radio_init_rfm69(&radio, &spi, true);
    #elif defined(OPENRTS_RADIO_TYPE_SX1278)
    rts_radio_init_sx1278(&radio, &spi, true);
    #endif

    // Switch to transmit mode
    rts_radio_set_mode(&radio, RTS_RADIO_MODE_TRANSMIT);
}

int main(int argc, char **argv)
{
    // Initialize the radio
    init_radio();

    // Set up the buttons
    struct gpiod_chip *gpio_chip = gpiod_chip_open(OPENRTS_GPIOD_DEVICE);
    struct gpiod_line *buttons[4];
    buttons[0] = gpiod_chip_get_line(gpio_chip, OPENRTS_BUTTON_1);
    buttons[1] = gpiod_chip_get_line(gpio_chip, OPENRTS_BUTTON_2);
    buttons[2] = gpiod_chip_get_line(gpio_chip, OPENRTS_BUTTON_3);
    buttons[3] = gpiod_chip_get_line(gpio_chip, OPENRTS_BUTTON_4);

    // Set up the remote button GPIOs as inputs, enable internal pull-ups
    for (int i = 0; i < 4; i++) {
        gpiod_line_request_input_flags(buttons[i], "remote",
                                       GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    }

    // Set up pulse output to send pulses to a linux gpiod pin
    rts_pulse_output_init_gpiod(&pulse_output, OPENRTS_GPIOD_DEVICE,
                                OPENRTS_RADIO_DATA);

    // Store remote rolling codes in a memory-mapped file
    rts_remote_store_init_mmap(&remote_store, "remotes.dat");

    // Set up the remote
    rts_remote_init(&remote, &pulse_output, &remote_store, RTS_TIMINGS_DEFAULT);

    // Check for button presses periodically, and send commands
    uint8_t last_command = 0;
    while (1) {
        uint8_t command = 0;
        command |= !gpiod_line_get_value(buttons[0]);      // My
        command |= !gpiod_line_get_value(buttons[1]) << 1; // Up
        command |= !gpiod_line_get_value(buttons[2]) << 2; // Down
        command |= !gpiod_line_get_value(buttons[3]) << 3; // Prog

        if (command) {
            printf("Sending command: %s\n", rts_command_to_string(command));
            rts_remote_send_command(&remote, 0xC0FFEE, command,
                                    last_command == command);
        }

        last_command = command;
    }

    return 0;
}
