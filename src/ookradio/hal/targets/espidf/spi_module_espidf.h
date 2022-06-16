#ifndef SPI_MODULE_ESPIDF_H
#define SPI_MODULE_ESPIDF_H

#include <driver/spi_master.h>

#include "../../spi_module.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 */

/**
 * @addtogroup ookradio
 * @{
 */

/**
 * @brief Initialize an spi_module struct using the ESP-IDF SPI interface
 *
 * @note Only available on ESP-IDF (ESP32, etc) builds
 *
 * @relates spi_module
 *
 * @param spi_module the spi_module struct to initialize
 * @param host_device the SPI host device to use, e.g. `HSPI_HOST`
 *
 * @return
 * - OOKRADIO_ERR_NONE if successful
 * - OOKRADIO_ERR_SPI_INIT_FAILED if unsuccessful
 */
int spi_module_init_espidf(struct spi_module *spi_module,
                           spi_host_device_t host_device);

/**
 * @}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SPI_MODULE_ESPIDF_H