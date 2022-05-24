#ifndef SPI_MODULE_H
#define SPI_MODULE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct spi_module {
    void (*transfer)(struct spi_module *spi, uint8_t *tx_buffer,
                     uint8_t *rx_buffer, uint8_t length);
    uint8_t cs_pin;
    uint32_t clock;
    uint8_t mode;
    uint8_t read_mask;
    uint8_t write_mask;

    union {
        void *user_data_ptr;
        int user_data_int;
    };
};

uint8_t spi_read(struct spi_module *spi, uint8_t reg);

void spi_write(struct spi_module *spi, uint8_t reg, uint8_t val);

void spi_write_masked(struct spi_module *spi, uint8_t reg, uint8_t mask,
                      uint8_t val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SPI_MODULE_H