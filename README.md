# Open RTS

[![GitHub](https://img.shields.io/github/license/loopj/open-rts)](https://github.com/loopj/open-rts/blob/main/LICENSE)
[![Build Status](https://github.com/loopj/open-rts/actions/workflows/unit_tests.yml/badge.svg)](https://github.com/loopj/open-rts/actions/workflows/unit_tests.yml)

Open RTS is a C library (with optional C++ bindings), which provides a full implementation of the Somfy RTS protocol designed for creating your own remotes, receivers, repeaters, or bridges on embedded hardware, such as Arduino or ESP8266/ESP32 devices.

This open-source, non-commercial library is not affiliated, associated, authorized, endorsed by, or in any way officially connected with Somfy.

## What can I do with this?

- Make your own Somfy RTS remote
- Build a web or mobile interface to open/close your shades
- Build your own Somfy RTS repeater to extend range of your remotes
- Turn on or off your lights using your Somfy RTS remote control
- Connect your shades to home automation systems, like Vantage
- Build an automation that closes your shades at sunset


## What hardware do I need?

1. A device capable of running this code
2. A 433Mhz, [OOK](https://en.wikipedia.org/wiki/On%E2%80%93off_keying)-capable radio

There are some awesome off-the-shelf devices that can do both of these, such as the [Adafruit Feather M0 RFM69HCW](https://www.adafruit.com/product/3177), the [Heltec WiFi LoRa 32](https://heltec.org/project/wifi-lora-32/), or [LILYGO TTGO LoRa32](http://www.lilygo.cn/prod_view.aspx?TypeId=50003&Id=1319&FId=t3:50003:3).

Alternatively you can take a 433Mhz OOK-capable radio module (eg. CC1101, RFM69, RFM96, SX1231, SX1278) and attach to a microcontroller.


## Key components

### rts_remote / RTSRemote

Simulates a physical RTS remote control. It takes RTS commands (button presses), converts them into a series of pulses, then outputs those pulses to a `rts_pulse_output` / `RTSPulseOutput` (eg. a GPIO or radio).

Remote rolling codes can be persisted by providing a `rts_remote_store` backend (eg. ESP32's non-volatile storage, or Arduino's EEPROM).

### rts_frame_builder / RTSFrameBuilder

Receives pulses via `rts_frame_builder_handle_pulse()`, assembles the pulses into complete RTS "frames", and delivers them to the callback you attach with `rts_frame_builder_set_callback()`.

An `rts_frame_builder` can be attached to an `rts_pulse_source` (eg. a GPIO or radio) with `rts_pulse_source_attach()` to observe pulses and build frames automatically.

### rts_receiver / RTSReceiver

Simulates a physical RTS receiver device, such as a shade or drapery motor.

It connects an `rts_pulse_source` (eg. a GPIO or radio) to an internal `rts_frame_builder` and adds common receiver functionality such as frame deduplication, remote pairing, and rolling code validation.

Deduplicated frame "events" such as "remote button pressed" and "remote button held" are sent to the event callback you attach with `rts_receiver_set_frame_callback()`.

Paired remotes and rolling codes can be persisted by providing a `rts_remote_store` backend (eg. ESP32's non-volatile storage, Arduino's EEPROM, or something custom if you'd prefer).
