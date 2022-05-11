#include <stdio.h>
#include <time.h>

#include <bcm2835.h>

#include "hal/spi.h"
#include "radio/rfm69/rfm69.h"
#include "rts_frame_builder.h"

#define DATA_PIN 24

rfm69_t radio;
rts_frame_builder_t frame_builder;
bool last_state = false;
uint64_t last_updated = 0;

void hal_spi_init(struct spi_module_t *spi) {
    bcm2835_init();
    bcm2835_spi_begin();

    // TODO: Use values from spi object instead of hardcoding
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
}

void hal_spi_transfer(struct spi_module_t *spi, uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t length) {
    uint8_t tmp[2];
    if(rx_buffer == NULL) {
        rx_buffer = tmp;
    }

    bcm2835_spi_transfernb(tx_buffer, rx_buffer, length);
}

void init_radio() {
    spi_module_t spi = {};
    spi_init(&spi);

    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);
    rfm69_set_mode(&radio, RFM69_MODE_RX);
}

void print_frame(rts_frame_t *frame, uint8_t repeat_count, uint32_t repeat_duration, void *user_data) {
    printf("Detected an RTS Frame!\n");
    printf("Command: %X\n", frame->command);
    printf("Remote: 0x%06X\n", frame->remote_address);
    printf("Rolling Code: 0x%04X (%d)\n\n", frame->rolling_code, repeat_count);
}

void check_for_pulses() {
    bool state = !bcm2835_gpio_lev(DATA_PIN);
    if(state != last_state) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        uint64_t now = 1000000 * ts.tv_sec + ts.tv_nsec/1000;

        uint32_t time_in_state = now - last_updated;

        rts_frame_builder_handle_pulse(&frame_builder, state, time_in_state);

        last_state = state;
        last_updated = now;
    }
}

int main(int argc, char **argv) {
    // Initialize the radio
    init_radio();

    // Set up the radio data pin for reading
    bcm2835_gpio_fsel(DATA_PIN, BCM2835_GPIO_FSEL_INPT);

    // Set up a framebuilder
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder, print_frame, NULL);

    // Check for new pulses
    while(1) {
        check_for_pulses();
    }

    return 0;
}
