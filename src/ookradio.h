#ifndef OOKRADIO_H
#define OOKRADIO_H


/**
 * @file
 */

/**
 * @defgroup ookradio OOK Radio Library
 * @brief A collection of userland SPI drivers for "OOK" radio modules.
 */

// SPI hardware abstraction layer
#include "ookradio/hal/spi_module.h"

#if defined(ARDUINO)
#include "ookradio/hal/targets/arduino/spi_module_arduino.h"
#endif

#if defined(ESP_PLATFORM)
#include "ookradio/hal/targets/espidf/spi_module_espidf.h"
#endif

#if defined(__linux__)
#include "ookradio/hal/targets/linux/spi_module_linux.h"
#endif

// Userland SPI drivers for radio modules
#include "ookradio/drivers/rfm69/rfm69.h"
#include "ookradio/drivers/sx1278/sx1278.h"

#endif // OOKRADIO_H