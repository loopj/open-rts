#ifndef SPI_MODULE_ESPIDF_H
#define SPI_MODULE_ESPIDF_H

#include <driver/spi_master.h>

#include "spi_module.h"

#ifdef __cplusplus
extern "C" {
#endif

void spi_module_init_espidf(struct spi_module *spi_module,
                            spi_host_device_t host_device);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SPI_MODULE_ESPIDF_H