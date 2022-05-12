#include "spi.h"

#include <stdio.h>

void spi_init(spi_module_t *spi) {
    hal_spi_init(spi);
}

void spi_write(spi_module_t *spi, uint8_t reg, uint8_t val) {
    uint8_t buf[2];
    buf[0] = reg | spi->write_mask;
    buf[1] = val;

    uint8_t read_buf[2];
    hal_spi_transfer(spi, buf, read_buf, 2);
}

void spi_write_masked(spi_module_t *spi, uint8_t reg, uint8_t mask, uint8_t val) {
    return spi_write(spi, reg, (spi_read(spi, reg) & ~mask) | val);
}

uint8_t spi_read(spi_module_t *spi, uint8_t reg) {
    uint8_t buf[2];
    buf[0] = reg | spi->read_mask;
    buf[1] = 0;

    uint8_t read_buf[2];
    hal_spi_transfer(spi, buf, read_buf, 2);

    return read_buf[1];
}