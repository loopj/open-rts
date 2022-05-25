#include <stdio.h>

#include "open_rts.h"

#define DATA_PIN 24
#define SPI_DEVICE "/dev/spidev0.1"
#define GPIOD_DEVICE "/dev/gpiochip0"

struct rfm69 radio;
struct rts_frame_builder frame_builder;
struct rts_pulse_source pulse_source;

void init_radio()
{
    struct spi_module spi = {};
    spi_module_init_linux(&spi, SPI_DEVICE);

    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);

    rfm69_set_mode(&radio, RFM69_MODE_RX);
}

void print_frame(struct rts_frame *frame, uint8_t count, uint32_t duration,
                 void *user_data)
{
    printf("Detected an RTS Frame!\n");
    printf("Command: %X\n", frame->command);
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
    rts_pulse_source_init_gpiod(&pulse_source, GPIOD_DEVICE, DATA_PIN);
    rts_pulse_source_attach(&pulse_source, &frame_builder);
    rts_pulse_source_enable(&pulse_source);

    // Check for new pulses
    while (1) {
        rts_pulse_source_update(&pulse_source);
    }

    return 0;
}
