#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <bcm2835.h>

#include "hal/spi.h"
#include "radio/rfm69/rfm69.h"
#include "rts_remote.h"
#include "rts_remote_store_memory.h"

#define BUTTON_PIN_MY   5
#define BUTTON_PIN_UP   6
#define BUTTON_PIN_DOWN 12
#define BUTTON_PIN_PROG 13

#define DATA_PIN 24

rfm69_t radio;
rts_remote_t remote;
rts_pulse_output_t pulse_output;
rts_remote_store_t remote_store;
uint8_t last_command = 0;

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
    rfm69_set_mode(&radio, RFM69_MODE_TX);
}

void rts_pulse_output_enable_gpio(rts_pulse_output_t *pulse_output) {
    bcm2835_gpio_fsel(pulse_output->user_data_int, BCM2835_GPIO_FSEL_OUTP);
}

void rts_pulse_output_send_pulse_gpio(rts_pulse_output_t *pulse_output, bool state, uint32_t micros) {
    if(state) {
        bcm2835_gpio_set(pulse_output->user_data_int);
    } else {
        bcm2835_gpio_clr(pulse_output->user_data_int);
    }

    usleep(micros);
}

void rts_pulse_output_init_gpio(rts_pulse_output_t *pulse_output, uint8_t data_pin) {
    pulse_output->send_pulse_fn = rts_pulse_output_send_pulse_gpio;
    pulse_output->enable_fn = rts_pulse_output_enable_gpio;
    pulse_output->disable_fn = NULL;
    pulse_output->user_data_int = data_pin;
}

int main(int argc, char **argv) {
    // Initialize the radio
    init_radio();

    // Set up the buttons
    bcm2835_gpio_fsel(BUTTON_PIN_UP, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(BUTTON_PIN_DOWN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(BUTTON_PIN_MY, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(BUTTON_PIN_PROG, BCM2835_GPIO_FSEL_INPT);

    bcm2835_gpio_set_pud(BUTTON_PIN_UP, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(BUTTON_PIN_DOWN, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(BUTTON_PIN_MY, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(BUTTON_PIN_PROG, BCM2835_GPIO_PUD_UP);

    // Set up pulse output
    rts_pulse_output_init_gpio(&pulse_output, DATA_PIN);

    // Store remote rolling codes in ESP non-volatile storage
    rts_remote_store_init_memory(&remote_store);

    // Set up the remote
    rts_remote_init(&remote, &pulse_output, &remote_store, RTS_TIMINGS_DEFAULT);

    // Check for button presses periodically, and send commands
    while(1) {
        uint8_t command = 0;
        command |= !bcm2835_gpio_lev(BUTTON_PIN_MY);
        command |= !bcm2835_gpio_lev(BUTTON_PIN_UP) << 1;
        command |= !bcm2835_gpio_lev(BUTTON_PIN_DOWN) << 2;
        command |= !bcm2835_gpio_lev(BUTTON_PIN_PROG) << 3;

        if(command) {
            rts_remote_send_command(&remote, 0xC0FFEE, command, last_command == command);
        }

        last_command = command;
    }

    return 0;
}
