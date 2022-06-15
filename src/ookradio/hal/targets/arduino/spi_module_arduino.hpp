#ifndef SPI_MODULE_ARDUINO_H
#define SPI_MODULE_ARDUINO_H

#include <SPI.h>

#include "../../spi_module.h"

/**
 * @file
 */

/**
 * @addtogroup ookradio
 * @{
 */

/**
 * @brief Initialize an spi_module struct using Arduino's SPI interface
 *
 * @note Only available on Arduino builds
 *
 * @relates spi_module
 *
 * @param spi_module the spi_module struct to initialize
 * @param spi_device a pointer to the Arduino SPI device to use, e.g. `&SPI`
 *
 * @return
 * - OOKRADIO_ERR_NONE if successful
 * - OOKRADIO_ERR_SPI_INIT_FAILED if unsuccessful
 */
int spi_module_init_arduino(struct spi_module *spi_module, SPIClass *spi_device);

/**
 * @}
 */

#endif // SPI_MODULE_ESPIDF_H