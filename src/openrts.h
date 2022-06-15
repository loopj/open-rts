#ifndef OPENRTS_H
#define OPENRTS_H

/**
 * @file
 */

/**
 * @defgroup openrts Open RTS C Library
 * @brief Core C library
 */

#include "openrts/boards.h"
#include "openrts/config.h"

#include "openrts/hal.h"
#include "openrts/rts_command.h"
#include "openrts/rts_frame.h"
#include "openrts/rts_frame_builder.h"
#include "openrts/rts_pulse_output.h"
#include "openrts/rts_pulse_source.h"
#include "openrts/rts_receiver.h"
#include "openrts/rts_remote.h"
#include "openrts/rts_remote_store.h"
#include "openrts/rts_remote_store_memory.h"
#include "openrts/rts_timings.h"

// Radio (ook-radio) features
#if OPENRTS_INCLUDE_RADIO
#include "openrts/rts_radio.h"
#endif

// ESP-IDF (ESP32)
#if OPENRTS_HAS_ESPIDF_GPIO
#include "openrts/espidf/rts_pulse_output_espidf_gpio.h"
#include "openrts/espidf/rts_pulse_source_espidf_gpio.h"
#endif

#if OPENRTS_HAS_NVS
#include "openrts/espidf/rts_remote_store_nvs.h"
#endif

// Linux
#if OPENRTS_HAS_GPIOD
#include "openrts/linux/rts_pulse_output_gpiod.h"
#include "openrts/linux/rts_pulse_source_gpiod.h"
#endif

#if OPENRTS_HAS_MMAP
#include "openrts/linux/rts_remote_store_mmap.h"
#endif

#endif // OPENRTS_H