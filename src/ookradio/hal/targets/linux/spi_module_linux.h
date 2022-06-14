#ifndef SPI_MODULE_LINUX_H
#define SPI_MODULE_LINUX_H

#include "ookradio/hal/spi_module.h"

#ifdef __cplusplus
extern "C" {
#endif

int spi_module_init_linux(struct spi_module *spi_module, const char *device);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SPI_MODULE_LINUX_H