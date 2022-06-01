#include <stdio.h>

// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
// #define OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
// #define OPENRTS_BOARD_RASPBERRY_PI_RFM96_BONNET

#include "open_rts.h"

struct rts_radio radio;
struct rts_frame_builder frame_builder;
struct rts_pulse_source pulse_source;

void init_radio()
{
    // Initialize SPI module
    struct spi_module spi = {};
    spi_module_init_linux(&spi, OPENRTS_SPI_DEVICE);

    // Initialize radio
    #if defined(OPENRTS_RADIO_TYPE_RFM69)
    rts_radio_init_rfm69(&radio, &spi, true);
    #elif defined(OPENRTS_RADIO_TYPE_SX1278)
    rts_radio_init_sx1278(&radio, &spi, true);
    #endif

    // Switch to receive mode
    rts_radio_set_mode(&radio, RTS_RADIO_MODE_RECEIVE);
}

void print_frame(struct rts_frame *frame, uint8_t count, uint32_t duration,
                 void *user_data)
{
    printf("Detected an RTS Frame!\n");
    printf("Command: %s\n", rts_command_to_string(frame->command));
    printf("Remote: 0x%06X\n", frame->remote_address);
    printf("Rolling Code: 0x%04X (%d)\n\n", frame->rolling_code, count);
}

int main(int argc, char **argv)
{
    // Initialize the radio
    init_radio();

    // Set up a framebuilder and subscribe to new frames
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder, print_frame, NULL);

    // Set up a GPIO pulse source, send pulses to the framebuilder
    rts_pulse_source_init_gpiod(&pulse_source, OPENRTS_GPIOD_DEVICE, OPENRTS_RADIO_DATA);
    rts_pulse_source_attach(&pulse_source, &frame_builder);
    rts_pulse_source_enable(&pulse_source);

    // Check for new pulses
    while (1) {
        rts_pulse_source_update(&pulse_source);
    }

    return 0;
}
