#ifndef OPENRTS_HPP
#define OPENRTS_HPP

/**
 * @file
 */

/**
 * @defgroup openrtsxx Open RTS C++ Bindings
 * @brief C++ bindings
 */

#include "openrts/boards.h"
#include "openrts/config.h"

#include "openrtsxx/RTSFrame.hpp"
#include "openrtsxx/RTSFrameBuilder.hpp"
#include "openrtsxx/RTSPulseOutput.hpp"
#include "openrtsxx/RTSPulseSource.hpp"
#include "openrtsxx/RTSReceiver.hpp"
#include "openrtsxx/RTSRemote.hpp"
#include "openrtsxx/RTSRemoteStore.hpp"
#include "openrtsxx/RTSRemoteStore_Memory.hpp"

// Radio (ook-radio) features
#if OPENRTS_INCLUDE_RADIO
#include "openrtsxx/RTSRadio.hpp"
#include "openrtsxx/RTSRadio_RFM69.hpp"
#include "openrtsxx/RTSRadio_SX1278.hpp"
#endif

// Arduino
#if OPENRTS_HAS_ARDUINO_GPIO
#include "openrtsxx/arduino/RTSPulseOutput_ArduinoGPIO.hpp"
#include "openrtsxx/arduino/RTSPulseSource_ArduinoGPIO.hpp"
#endif

// ESP-IDF (ESP32)
#if OPENRTS_HAS_EEPROM
#include "openrtsxx/arduino/RTSRemoteStore_EEPROM.hpp"
#endif

#if OPENRTS_HAS_NVS
#include "openrtsxx/espidf/RTSRemoteStore_NVS.hpp"
#endif

// Linux
#if OPENRTS_HAS_MMAP
#include "openrtsxx/linux/RTSRemoteStore_MMap.hpp"
#endif

#endif // OPENRTS_HPP