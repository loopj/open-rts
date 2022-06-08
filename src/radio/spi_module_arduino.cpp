#if defined(ARDUINO)

#include "spi_module_arduino.h"

#include <Arduino.h>
#include <SPI.h>

static void spi_module_transfer_arduino(struct spi_module *spi_module,
                                        uint8_t *tx_buffer, uint8_t *rx_buffer,
                                        uint8_t length)
{
    digitalWrite(spi_module->cs_pin, LOW);
    SPI.beginTransaction(*((SPISettings *)spi_module->user_data_ptr));
    for (int i = 0; i < length; i++) {
        uint8_t ret = SPI.transfer(tx_buffer[i]);
        if (rx_buffer) {
            rx_buffer[i] = ret;
        }
    }
    SPI.endTransaction();
    digitalWrite(spi_module->cs_pin, HIGH);
}

void spi_module_init_arduino(struct spi_module *spi_module)
{
    SPI.begin();
    pinMode(spi_module->cs_pin, OUTPUT);

    spi_module->transfer = spi_module_transfer_arduino;
    spi_module->user_data_ptr =
        new SPISettings(spi_module->clock, MSBFIRST, spi_module->mode);
}

#endif // defined(ARDUINO)