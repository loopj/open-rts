#if defined(ARDUINO)

#include "../../../errors.h"

#include "spi_module_arduino.hpp"

#include <Arduino.h>

static int spi_module_transfer_arduino(struct spi_module *spi_module,
                                       uint8_t *tx_buffer, uint8_t *rx_buffer,
                                       uint8_t length)
{
    SPIClass *spi = (SPIClass *)spi_module->user_data_ptr;

    // Pull chip select pin low
    digitalWrite(spi_module->cs_pin, LOW);

    // Do the transfer
    spi->beginTransaction(SPISettings(spi_module->clock, MSBFIRST, spi_module->mode));
    for (int i = 0; i < length; i++) {
        uint8_t ret = spi->transfer(tx_buffer[i]);
        if (rx_buffer) {
            rx_buffer[i] = ret;
        }
    }
    spi->endTransaction();

    // Pull chip select high again
    digitalWrite(spi_module->cs_pin, HIGH);

    return OOKRADIO_ERR_NONE;
}

int spi_module_init_arduino(struct spi_module *spi_module, SPIClass *spi)
{
    // TODO: Do we need this? SPI.begin says it does this
    pinMode(spi_module->cs_pin, OUTPUT);

    // Initialize the SPI bus
    spi->begin();

    spi_module->transfer = spi_module_transfer_arduino;
    spi_module->user_data_ptr = spi;

    return OOKRADIO_ERR_NONE;
}

#endif // defined(ARDUINO)