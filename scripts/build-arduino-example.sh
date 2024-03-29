#!/usr/bin/env bash

# This script requires
# - Bash >= 4.0
# - Arduino CLI

# brew install bash arduino-cli

# arduino-cli config init
# arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
# arduino-cli core update-index
# arduino-cli core install
# arduino-cli lib install U8g2

declare -A board_fqbns=()
declare -A board_flags=()

# SparkFun LoRa Gateway (w/RFM69 module)
board_fqbns["sparkfun"]="esp32:esp32:sparkfun_lora_gateway_1-channel"
board_flags["sparkfun"]="
    -DOPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
    -DOPENRTS_BUTTON_2=23
    -DOPENRTS_BUTTON_3=19
    -DOPENRTS_BUTTON_4=18
"

# LILYGO TTGO LoRa32 (V2.1)
board_fqbns["ttgo"]="esp32:esp32:ttgo-lora32:Revision=TTGO_LoRa32_v21new"
board_flags["ttgo"]="
    -DOPENRTS_BOARD_TTGO_LORA32_V21
"

# Heltec WiFi LoRa 32 (V2)
board_fqbns["heltec"]="esp32:esp32:heltec_wifi_lora_32_V2"
board_flags["heltec"]="
    -DOPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2
"

# Adafruit HUZZAH32
# with Adafruit Radio FeatherWing RFM69HCW
# RST=A, CS=B, DIO2=25
board_fqbns["featheresp32"]="esp32:esp32:featheresp32"
board_flags["featheresp32"]="
    -DOPENRTS_RADIO_TYPE_RFM69
    -DOPENRTS_RADIO_CS=33
    -DOPENRTS_RADIO_DATA=25
    -DOPENRTS_LED=13
    -DOPENRTS_BUTTON_1=15
    -DOPENRTS_BUTTON_2=32
    -DOPENRTS_BUTTON_3=14
    -DOPENRTS_BUTTON_4=0
    -DOPENRTS_OLED_TYPE_SH1107
"

# Adafruit Feather 32u4 RFM69HCW
board_fqbns["feather32u4"]="adafruit:avr:feather32u4"
board_flags["feather32u4"]="
    -DOPENRTS_BOARD_ADAFRUIT_32U4_RFM69
    -DOPENRTS_BUTTON_1=9
    -DOPENRTS_BUTTON_2=6
    -DOPENRTS_BUTTON_3=5
    -DOPENRTS_BUTTON_4=10
"

# Adafruit Feather M0 RFM69HCW
board_fqbns["featherm0"]="adafruit:samd:adafruit_feather_m0"
board_flags["featherm0"]="
    -DOPENRTS_BOARD_ADAFRUIT_M0_RFM69
    -DOPENRTS_BUTTON_1=9
    -DOPENRTS_BUTTON_2=6
    -DOPENRTS_BUTTON_3=5
    -DOPENRTS_BUTTON_4=10
"

# Get a list of example names
example_paths=(examples/arduino/*)
example_names=()
for i in ${example_paths[@]}; do
    example_names+=(${i##*/})
done

# Check example, board, and port are passed
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <example> <board> <port>" 1>&2
    exit 1
fi

# Check example exists
if [[ ! " ${example_names[*]} " =~ " $1 " ]]; then
    echo "Unknown example '$1'. Valid examples are:"
    for i in ${example_names[@]}; do
        echo ${i}
    done
    exit 1
fi

# Check board is known
if [[ ! -v "board_fqbns[$2]" ]]; then
    echo "Unknown board '$2'. Valid boards are:"
    for i in ${!board_fqbns[@]}; do
        echo ${i}
    done
    exit 1
fi

# Build the example
arduino-cli compile \
    --clean \
    --warnings all\
    --dump-profile \
    --upload \
    --port $3 \
	--fqbn ${board_fqbns[$2]} \
	--build-property "compiler.cpp.extra_flags=${board_flags[$2]}" \
	--library="$PWD" \
    --build-path="build" \
	examples/arduino/$1