#ifndef OPEN_RTS_H
#define OPEN_RTS_H

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


// Radio (ook-radio) features
#if INCLUDE_RADIO
#include "rts_radio.h"

#if defined(ESP_PLATFORM)
#include "radio/spi_module_espidf.h"
#endif

#if HAS_LINUX
#include "radio/spi_module_linux.h"
#endif

#if HAS_ARDUINO
#include "radio/spi_module_arduino.h"
#endif
#endif // INCLUDE_RADIO


// C++ bindings
#if INCLUDE_CPP_BINDINGS

#include "bindings/cpp/RTSFrame.h"
#include "bindings/cpp/RTSFrameBuilder.h"
#include "bindings/cpp/RTSPulseOutput.h"
#include "bindings/cpp/RTSPulseSource.h"
#include "bindings/cpp/RTSReceiver.h"
#include "bindings/cpp/RTSRemote.h"
#include "bindings/cpp/RTSRemoteStore.h"
#include "bindings/cpp/RTSRemoteStore_Memory.h"

#if HAS_ARDUINO
#include "bindings/cpp/RTSPulseOutput_ArduinoGPIO.h"
#include "bindings/cpp/RTSPulseSource_ArduinoGPIO.h"
#endif

#if HAS_POSIX
#include "bindings/cpp/RTSRemoteStore_MMap.h"
#endif

#if HAS_NVS
#include "bindings/cpp/RTSRemoteStore_NVS.h"
#endif

#if INCLUDE_RADIO
#include "bindings/cpp/RTSRadio.h"
#include "bindings/cpp/RTSRadio_RFM69.h"
#include "bindings/cpp/RTSRadio_SX1278.h"
#endif

#endif // INCLUDE_CPP_BINDINGS

#endif // OPEN_RTS_H