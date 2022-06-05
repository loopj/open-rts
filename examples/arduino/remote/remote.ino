// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
// #define OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
// #define OPENRTS_BOARD_TTGO_LORA32_V21
// #define OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2

#include "open_rts.h"

// Set up remote
uint32_t remoteAddress = 0xC0FFEE;
RTSPulseOutput_ArduinoGPIO pulseOutput(OPENRTS_RADIO_DATA);
RTSRemoteStore_Memory remoteStore;
RTSRemote remote(&pulseOutput, &remoteStore);
uint8_t lastCommand = 0;

struct rts_radio radio;
void init_radio()
{
    // Initialize SPI module
    struct spi_module spi = {
        .cs_pin = OPENRTS_RADIO_CS,
        .clock = 1000000,
        .mode = 0,
    };
    spi_module_init_arduino(&spi);

    // Initialize radio
    #if defined(OPENRTS_RADIO_TYPE_RFM69)
    rts_radio_init_rfm69(&radio, &spi, true);
    #elif defined(OPENRTS_RADIO_TYPE_SX1278)
    rts_radio_init_sx1278(&radio, &spi, true);
    #endif

    // Switch to receive mode
    rts_radio_set_mode(&radio, RTS_RADIO_MODE_TRANSMIT);
}

void setup() {
    // Enable serial debugging
    Serial.begin(115200);

    // Configure radio
    init_radio();

    // Set up the buttons
    pinMode(OPENRTS_BUTTON_1, INPUT_PULLUP);
    pinMode(OPENRTS_BUTTON_2, INPUT_PULLUP);
    pinMode(OPENRTS_BUTTON_3, INPUT_PULLUP);
    pinMode(OPENRTS_BUTTON_4, INPUT_PULLUP);

    // Set up the LED
    pinMode(OPENRTS_LED, OUTPUT);
}

void loop() {
    // Convert button state to RTS commands
    uint8_t command = 0;
    command |= !digitalRead(OPENRTS_BUTTON_1);
    command |= !digitalRead(OPENRTS_BUTTON_2) << 1;
    command |= !digitalRead(OPENRTS_BUTTON_3) << 2;
    command |= !digitalRead(OPENRTS_BUTTON_4) << 3;

    // Send the command if we have one
    if(command) {
        Serial.print("Sending command: ");
        Serial.println(rts_command_to_string((rts_command)command));
        digitalWrite(OPENRTS_LED, 1);

        remote.sendCommand(remoteAddress, (rts_command)command, lastCommand == command);
    } else {
        digitalWrite(OPENRTS_LED, 0);
    }

    // Store the last command, so we can detect if this is a repeated vs new command
    lastCommand = command;
}