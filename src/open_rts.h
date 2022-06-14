/// @file

/// @defgroup c C Library
/// @defgroup cpp C++ Bindings

#ifndef OPEN_RTS_H
#define OPEN_RTS_H

//
// Core library
//

#include "boards.h"
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

#if OPENRTS_INCLUDE_CPP_BINDINGS
#include "bindings/cpp/RTSFrame.hpp"
#include "bindings/cpp/RTSFrameBuilder.hpp"
#include "bindings/cpp/RTSPulseOutput.hpp"
#include "bindings/cpp/RTSPulseSource.hpp"
#include "bindings/cpp/RTSReceiver.hpp"
#include "bindings/cpp/RTSRemote.hpp"
#include "bindings/cpp/RTSRemoteStore.hpp"
#include "bindings/cpp/RTSRemoteStore_Memory.hpp"
#endif // OPENRTS_INCLUDE_CPP_BINDINGS

//
// Platform-specific includes
//

// Arduino
#if OPENRTS_HAS_ARDUINO_GPIO && OPENRTS_INCLUDE_CPP_BINDINGS
#include "bindings/cpp/arduino/RTSPulseOutput_ArduinoGPIO.hpp"
#include "bindings/cpp/arduino/RTSPulseSource_ArduinoGPIO.hpp"
#endif

#if OPENRTS_HAS_EEPROM && OPENRTS_INCLUDE_CPP_BINDINGS
#include "bindings/cpp/arduino/RTSRemoteStore_EEPROM.hpp"
#endif

// ESP-IDF (ESP32)
#if OPENRTS_HAS_ESPIDF_GPIO
#include "espidf/rts_pulse_output_espidf_gpio.h"
#include "espidf/rts_pulse_source_espidf_gpio.h"
#endif

#if OPENRTS_HAS_NVS
#include "espidf/rts_remote_store_nvs.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS
#include "bindings/cpp/espidf/RTSRemoteStore_NVS.hpp"
#endif
#endif

// Linux
#if OPENRTS_HAS_GPIOD
#include "linux/rts_pulse_output_gpiod.h"
#include "linux/rts_pulse_source_gpiod.h"
#endif

#if OPENRTS_HAS_MMAP
#include "linux/rts_remote_store_mmap.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS
#include "bindings/cpp/linux/RTSRemoteStore_MMap.hpp"
#endif
#endif

//
// Radio (ook-radio) features
//
#if OPENRTS_INCLUDE_RADIO
#include "rts_radio.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS
#include "bindings/cpp/RTSRadio.hpp"
#include "bindings/cpp/radio/RTSRadio_RFM69.hpp"
#include "bindings/cpp/radio/RTSRadio_SX1278.hpp"
#endif
#endif // OPENRTS_INCLUDE_RADIO

#endif // OPEN_RTS_H