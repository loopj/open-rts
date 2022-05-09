# Open RTS

![Build Status](https://github.com/loopj/open-rts/actions/workflows/unit_tests.yml/badge.svg)

This library is a full implementation of the Somfy RTS protocol designed for creating your own remotes, receivers, repeaters, or bridges on embedded hardware, such as Arduino or ESP8266/ESP32 devices.

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

### RTSRemote

The `RTSRemote` class simulates a physical RTS remote control. It takes RTS commands (button presses), converts them into a series of pulses, then outputs those pulses to a `RTSPulseOutput` (eg. a GPIO or radio).

Remote rolling codes can be persisted by providing a `RTSRemoteStore` backend (eg. ESP32's non-volatile storage, or Arduino's EEPROM).

### RTSFrameBuilder

The `RTSFrameBuilder` class receives pulses via `RTSFrameBuilder::sendPulse`, assembles the pulses into complete RTS "frames", and delivers them to the callback you attach with `RTSFrameBuilder::onFrame`.

An `RTSFrameBuilder` can be attached to an `RTSPulseSource` (eg. a GPIO or radio) with `RTSPulseSource::attachObserver` to observe pulses and build frames automatically.

### RTSReceiver

The `RTSReceiver` class simulates a physical RTS receiver device, such as a shade or drapery motor.

It connects an `RTSPulseSource` (eg. a GPIO or radio) to an internal `RTSFrameBuilder` and adds common receiver functionality such as frame deduplication, remote pairing, and rolling code validation.

Deduplicated frame "events" such as "remote button pressed" and "remote button held" are sent to the event callback you attach with `RTSReceiver::onEvent`.

Paired remotes and rolling codes can be persisted by providing a `RTSRemoteStore` backend (eg. ESP32's non-volatile storage, Arduino's EEPROM, or something custom if you'd prefer).
