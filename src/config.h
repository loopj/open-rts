#ifndef OPEN_RTS_CONFIG_H
#define OPEN_RTS_CONFIG_H

#pragma once

#if defined(ESP_PLATFORM) && !defined(HAS_NVS)
#define HAS_NVS 1
#endif

#if defined(ESP_PLATFORM) && !defined(HAS_ESPIDF_GPIO)
#define HAS_ESPIDF_GPIO 1
#endif

#if !defined(HAS_GPIOD)
#define HAS_GPIOD 0
#endif

#if !defined(HAS_RADIO)
#define HAS_RADIO 1
#endif

#endif // OPEN_RTS_CONFIG_H