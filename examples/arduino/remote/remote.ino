/*
 * Simple RTS Remote Example
 *
 * This example implements a 4-button, single-address RTS remote control.
 * It takes button inputs, assembles them into RTS frames, then outputs them
 * to the attached radio module.
 *
 * Rolling codes are persisted to EEPROM or NVS if available.
 *
 * Pressing and holding a button will send "repeat" frames, which won't
 * increase the rolling code.
 */

//
// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
//

// #define OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
// #define OPENRTS_BOARD_TTGO_LORA32_V21
// #define OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2
// #define OPENRTS_BOARD_ADAFRUIT_M0_RFM69
// #define OPENRTS_BOARD_ADAFRUIT_32U4_RFM69

//
// Uncomment all of the following and configure which GPIOs to use for input
//

// #define OPENRTS_BUTTON_1 0   // My button
// #define OPENRTS_BUTTON_2 23  // Up button
// #define OPENRTS_BUTTON_3 19  // Down button
// #define OPENRTS_BUTTON_4 18  // Prog button

#include <openrts.hpp>

// Supported radio modules
#if defined(OPENRTS_RADIO_TYPE_RFM69)
RTSRadio_RFM69 radio(OPENRTS_RADIO_CS);
#elif defined(OPENRTS_RADIO_TYPE_SX1278)
RTSRadio_SX1278 radio(OPENRTS_RADIO_CS);
#endif

// Remote and rolling code persistence
#if OPENRTS_HAS_NVS
RTSRemoteStore_NVS remoteStore;
#elif OPENRTS_HAS_EEPROM
RTSRemoteStore_EEPROM remoteStore;
#else
RTSRemoteStore_Memory remoteStore;
#endif

// Set up remote
uint32_t remoteAddress = 0xC0FFEE;
RTSRemote remote(new RTSPulseOutput_GPIO(OPENRTS_RADIO_DATA), &remoteStore);
uint8_t lastCommand = 0;

void setup() {
    // Enable serial debugging
    Serial.begin(115200);

    // Set up the buttons
    pinMode(OPENRTS_BUTTON_1, INPUT_PULLUP);
    pinMode(OPENRTS_BUTTON_2, INPUT_PULLUP);
    pinMode(OPENRTS_BUTTON_3, INPUT_PULLUP);
    pinMode(OPENRTS_BUTTON_4, INPUT_PULLUP);

    // Set up the LED
    pinMode(OPENRTS_LED, OUTPUT);

    // Configure radio
    radio.begin();
    radio.setMode(RTS_RADIO_MODE_TRANSMIT);
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

        // Turn on LED while sending
        digitalWrite(OPENRTS_LED, 1);

        // Send the command
        remote.sendCommand(remoteAddress, (rts_command)command, lastCommand == command);
    } else {
        digitalWrite(OPENRTS_LED, 0);
    }

    // Store the last command, so we can detect if this is a repeated vs new command
    lastCommand = command;
}