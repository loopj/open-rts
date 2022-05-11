#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spi_module_t {
    void (*init)(struct spi_module_t *spi);
    void (*transfer)(struct spi_module_t *spi, uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t length);
    uint8_t cs_pin;
    uint32_t clock;
    uint8_t mode;
    uint8_t read_mask;
    uint8_t write_mask;
    void *user_data;
} spi_module_t;

void hal_spi_init(struct spi_module_t *spi);
void hal_spi_transfer(struct spi_module_t *spi, uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t length);

void spi_init(spi_module_t *spi);
void spi_write(spi_module_t *spi, uint8_t reg, uint8_t val);
void spi_write_masked(spi_module_t *spi, uint8_t reg, uint8_t mask, uint8_t val);
uint8_t spi_read(spi_module_t *spi, uint8_t reg);

#ifdef __cplusplus
} // extern "C"
#endif