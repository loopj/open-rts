#include "spi_module.h"

#include <stdio.h>

uint8_t spi_read(struct spi_module *spi, uint8_t reg)
{
    uint8_t buf[2];
    buf[0] = reg | spi->read_mask;
    buf[1] = 0;

    uint8_t read_buf[2];
    if (spi->transfer) {
        spi->transfer(spi, buf, read_buf, 2);
    } else {
        // TODO: Log error
    }

    return read_buf[1];
}

void spi_write(struct spi_module *spi, uint8_t reg, uint8_t val)
{
    uint8_t buf[2];
    buf[0] = reg | spi->write_mask;
    buf[1] = val;

    uint8_t read_buf[2];
    if (spi->transfer) {
        spi->transfer(spi, buf, read_buf, 2);
    } else {
        // TODO: Log error
    }
}

void spi_write_masked(struct spi_module *spi, uint8_t reg, uint8_t mask,
                      uint8_t val)
{
    return spi_write(spi, reg, (spi_read(spi, reg) & ~mask) | val);
}