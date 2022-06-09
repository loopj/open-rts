#ifndef SPI_MODULE_ARDUINO_H
#define SPI_MODULE_ARDUINO_H

#include "ookradio/hal/spi_module.h"

#ifdef __cplusplus
extern "C" {
#endif

int spi_module_init_arduino(struct spi_module *spi_module);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SPI_MODULE_ESPIDF_H