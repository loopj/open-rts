/**
 * @file boards.h
 *
 * Common board definitions for microcontrollers and radio modules.
 *
 * Each board config should define the following:
 *
 * - `OPENRTS_RADIO_TYPE_*` - The type of radio module connected to the MCU
 * - `OPENRTS_RADIO_CS` 	- The SPI chip select pin for the radio module
 * - `OPENRTS_RADIO_DATA` 	- The data pin for OOK control on the radio module
 * - `OPENRTS_RADIO_RST` 	- The reset GPIO for the radio module (if present)
 *
 *
 * Although Arduino typically defines MISO/MOSI/SCLK for us, on other platforms
 * it is useful to know these:
 *
 * - `OPENRTS_RADIO_MISO` 	- The SPI MISO pin
 * - `OPENRTS_RADIO_MOSI` 	- The SPI MOSI pin
 * - `OPENRTS_RADIO_SCK` 	- The SPI SCLK pin
 *
 *
 * Where the board has onboard buttons/leds it is helpful to define these for
 * use in example applications:
 *
 * - `OPENRTS_LED` 			- Onboard LED
 * - `OPENRTS_BUTTON_1` 	- Onboard button 1
 * - `OPENRTS_BUTTON_2` 	- Onboard button 2
 * - `OPENRTS_BUTTON_3` 	- Onboard button 3
 * - `OPENRTS_BUTTON_4` 	- Onboard button 4
 *
 */

#if defined(OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY)
// SparkFun LoRa Gateway 1-Channel (with modification)
// Assumes the default 915MHz radio module has been removed and replaced with a
// 433MHz module (RFM69HCW)
#define OPENRTS_RADIO_TYPE_RFM69
#define OPENRTS_RADIO_MISO 12
#define OPENRTS_RADIO_MOSI 13
#define OPENRTS_RADIO_SCK  14
#define OPENRTS_RADIO_CS   16
#define OPENRTS_RADIO_RST  27
#define OPENRTS_RADIO_DATA 32
#define OPENRTS_BUTTON_1   0
#define OPENRTS_LED        17
#elif defined(OPENRTS_BOARD_TTGO_LORA32_V21)
// LILYGO TTGO LoRa32 (V2.1) - 433MHz
#define OPENRTS_RADIO_TYPE_SX1278
#define OPENRTS_RADIO_MISO 19
#define OPENRTS_RADIO_MOSI 27
#define OPENRTS_RADIO_SCK  5
#define OPENRTS_RADIO_CS   18
#define OPENRTS_RADIO_RST  23
#define OPENRTS_RADIO_DATA 32
#define OPENRTS_LED        25
#elif defined(OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2)
// Heltec WiFi LoRa 32 (V2) - 433MHz
#define OPENRTS_RADIO_TYPE_SX1278
#define OPENRTS_RADIO_MISO 19
#define OPENRTS_RADIO_MOSI 27
#define OPENRTS_RADIO_SCK  5
#define OPENRTS_RADIO_CS   18
#define OPENRTS_RADIO_RST  14
#define OPENRTS_RADIO_DATA 34
#define OPENRTS_BUTTON_1   0
#define OPENRTS_LED        25
#elif defined(OPENRTS_BOARD_ADAFRUIT_M0_RFM69)
// Adafruit Feather M0 RFM69HCW Packet Radio - 433MHz
// TODO: Double check these pins
#define OPENRTS_RADIO_TYPE_RFM69
#define OPENRTS_RADIO_CS   8
#define OPENRTS_RADIO_RST  4
#define OPENRTS_RADIO_DATA 0
#define OPENRTS_LED        13
#elif defined(OPENRTS_BOARD_ADAFRUIT_32U4_RFM69)
// Adafruit Feather 32u4 RFM69HCW Packet Radio - 433MHz
#define OPENRTS_RADIO_TYPE_RFM69
#define OPENRTS_RADIO_CS   8
#define OPENRTS_RADIO_RST  4
#define OPENRTS_RADIO_DATA 0
#define OPENRTS_LED        13
#elif defined(OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET)
// Raspberry Pi with Adafruit RFM69HCW Transceiver Radio Bonnet - 433 MHz
#define OPENRTS_RADIO_TYPE_RFM69
#define OPENRTS_BUTTON_1     5
#define OPENRTS_BUTTON_2     6
#define OPENRTS_BUTTON_3     12
#define OPENRTS_BUTTON_4     13
#define OPENRTS_RADIO_DATA   24
#define OPENRTS_SPI_DEVICE   "/dev/spidev0.1"
#define OPENRTS_GPIOD_DEVICE "/dev/gpiochip0"
#elif defined(OPENRTS_BOARD_RASPBERRY_PI_RFM96_BONNET)
// Raspberry Pi with Adafruit LoRa Radio Bonnet RFM96W - 433 MHz
#define OPENRTS_RADIO_TYPE_SX1278
#define OPENRTS_BUTTON_1     5
#define OPENRTS_BUTTON_2     6
#define OPENRTS_BUTTON_3     12
#define OPENRTS_BUTTON_4     13
#define OPENRTS_RADIO_DATA   24
#define OPENRTS_SPI_DEVICE   "/dev/spidev0.1"
#define OPENRTS_GPIOD_DEVICE "/dev/gpiochip0"
#endif