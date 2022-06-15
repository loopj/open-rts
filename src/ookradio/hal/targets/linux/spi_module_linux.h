#ifndef SPI_MODULE_LINUX_H
#define SPI_MODULE_LINUX_H

#include "../../spi_module.h"

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
 * @brief Initialize an spi_module struct using Linux spidev
 *
 * @note Only available on Linux builds, spidev must be enabled
 *
 * @relates spi_module
 *
 * @param spi_module the spi_module struct to initialize
 * @param device the spi device to use, e.g. `/dev/spidev0.1`
 *
 * @return
 * - OOKRADIO_ERR_NONE if successful
 * - OOKRADIO_ERR_SPI_INIT_FAILED if unsuccessful
 */
int spi_module_init_linux(struct spi_module *spi_module, const char *device);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // SPI_MODULE_LINUX_H