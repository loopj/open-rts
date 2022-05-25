#ifndef OPEN_RTS_H
#define OPEN_RTS_H

#include "config.h"

#include "hal.h"
#include "rts_command.h"
#include "rts_frame.h"
#include "rts_frame_builder.h"
#include "rts_pulse_output.h"
#include "rts_pulse_source.h"
#include "rts_receiver.h"
#include "rts_remote.h"
#include "rts_remote_store.h"
#include "rts_remote_store_memory.h"
#include "rts_timings.h"

#if HAS_RADIO
#include "radio/rfm69.h"
#include "radio/spi_module.h"
#include "radio/sx1278.h"

#if defined(ESP_PLATFORM)
#include "radio/spi_module_espidf.h"
#endif

#if defined(__linux__)
#include "radio/spi_module_linux.h"
#endif
#endif

#if HAS_GPIOD
#include "rts_pulse_output_gpiod.h"
#include "rts_pulse_source_gpiod.h"
#endif

#if HAS_ESPIDF_GPIO
#include "rts_pulse_output_espidf_gpio.h"
#include "rts_pulse_source_espidf_gpio.h"
#endif

#if HAS_NVS
#include "rts_remote_store_nvs.h"
#endif

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include "rts_remote_store_mmap.h"
#endif

#endif // OPEN_RTS_H