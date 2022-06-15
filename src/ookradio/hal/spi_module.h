#ifndef SPI_MODULE_H
#define SPI_MODULE_H

#include <stdint.h>

/**
 * @file
 */

/**
 * @addtogroup ookradio
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hardware abstraction layer for userland SPI drivers
 */
struct spi_module {
    /**
     * The chip select pin for the target SPI device
     */
    uint8_t cs_pin;

    /**
     * The SPI clock speed (in Hz) to use for transfers
     */
    uint32_t clock;

    /**
     * The SPI mode to use for transfers
     */
    uint8_t mode;

    /**
     * Bitmask to apply to the register address when we are reading
     */
    uint8_t read_mask;

    /**
     * Bitmask to apply to the register address when we are writing
     */
    uint8_t write_mask;

    // The SPI transfer function to call (set by spi_module_init_*)
    int (*transfer)(struct spi_module *spi, uint8_t *tx_buffer,
                    uint8_t *rx_buffer, uint8_t length);

    // Internal user_data to store device handles, etc
    union {
        void *user_data_ptr;
        int user_data_int;
    };
};

/**
 * @brief Read a byte from the spi device at the specified register address
 *
 * @relates spi_module
 *
 * @param spi the spi_module to read from
 * @param reg the register address to read from
 *
 * @return the value returned from the device
 */
uint8_t spi_read(struct spi_module *spi, uint8_t reg);

/**
 * @brief Write a byte to the spi device at the specified register address
 *
 * @relates spi_module
 *
 * @param spi the spi_module to write to
 * @param reg the register address to write to
 *
 */
void spi_write(struct spi_module *spi, uint8_t reg, uint8_t val);

/**
 * @brief Write some bits of val to the spi device at the specified register
 *        address, using a bitmask
 *
 * @relates spi_module
 *
 * @param spi the spi_module to write to
 * @param reg the register address to write to
 *
 */
void spi_write_masked(struct spi_module *spi, uint8_t reg, uint8_t mask,
                      uint8_t val);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // SPI_MODULE_H