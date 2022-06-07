#ifndef OPEN_RTS_CONFIG_H
#define OPEN_RTS_CONFIG_H

//
// Include ESP-IDF non-volatile storage rts_remote_store by default when
// we detect you are building on the ESP platform.
//
// Uncomment the following line to disable:
// #define OPENRTS_HAS_NVS 0
#if defined(ESP_PLATFORM) && !defined(OPENRTS_HAS_NVS)
#define OPENRTS_HAS_NVS 1
#endif

//
// Include ESP-IDF GPIO rts_pulse_source and rts_pulse_output by default when
// we detect you are building on the ESP platform.
//
// Uncomment the following line to disable:
// #define OPENRTS_HAS_ESPIDF_GPIO 0
#if defined(ESP_PLATFORM) && !defined(OPENRTS_HAS_ESPIDF_GPIO)
#define OPENRTS_HAS_ESPIDF_GPIO 1
#endif

//
// Include Linux libgpiod rts_pulse_source and rts_pulse_output.
// We can't automatically detect this, so you'll need to set this flag manually
//
// Uncomment the following line to enable:
// #define OPENRTS_HAS_GPIOD 1
#if !defined(OPENRTS_HAS_GPIOD)
#define OPENRTS_HAS_GPIOD 0
#endif

//
// Include POSIX-specific code if we are on a POSIX platform
// Currently just the memory-mapped rts_remote_store
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#define OPENRTS_HAS_POSIX 1
#endif

//
// Include Arduino-specific code if we are on Arduino
//
// Uncomment the following line to disable:
// #define OPENRTS_HAS_ARDUINO 0
#if defined(ARDUINO) && !defined(OPENRTS_HAS_ARDUINO)
#define OPENRTS_HAS_ARDUINO 1
#endif

//
// Include Arduino EEPROM rts_remote_store by default when we detect you are
// building on a supported platform.
//
// Uncomment the following line to disable:
// #define OPENRTS_HAS_EEPROM 0
#if (defined(ARDUINO) && (defined(__AVR__) || defined(ESP_PLATFORM))) &&       \
    !defined(OPENRTS_HAS_EEPROM)
#define OPENRTS_HAS_EEPROM 1
#endif

//
// Include Linux-specific code if we are on Linux
#if defined(__linux__) && !defined(OPENRTS_HAS_LINUX)
#define OPENRTS_HAS_LINUX 1
#endif

//
// Include C++ bindings by default if we're being built by a C++ compiler
//
// Uncomment the following line to disable:
// #define OPENRTS_INCLUDE_CPP_BINDINGS 0
#if defined(__cplusplus) && !defined(OPENRTS_INCLUDE_CPP_BINDINGS)
#define OPENRTS_INCLUDE_CPP_BINDINGS 1
#endif

//
// Include the radio library by default
//
// Uncomment the following line to disable:
// #define OPENRTS_INCLUDE_RADIO 0
#if !defined(OPENRTS_INCLUDE_RADIO)
#define OPENRTS_INCLUDE_RADIO 1
#endif

#endif // OPEN_RTS_CONFIG_H