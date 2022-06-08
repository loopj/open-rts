/*
 * Serial Frame Sniffer Example
 *
 * This example receives pulses from a 433MHz radio module, assembles them
 * into RTS Frames, then outputs them to the Serial console.
 *
 * This example doesn't care about remote addresses, rolling codes, or frame
 * deduplication, just prints every assembled frame.
 */

//
// Uncomment one of these to use a predefined board config
// Alternatively you'll need to define the pins manually
//

// #define OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
// #define OPENRTS_BOARD_TTGO_LORA32_V21
// #define OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2

#include "open_rts.h"

// Supported radio modules
#if defined(OPENRTS_RADIO_TYPE_RFM69)
RTSRadio_RFM69 radio(OPENRTS_RADIO_CS);
#elif defined(OPENRTS_RADIO_TYPE_SX1278)
RTSRadio_SX1278 radio(OPENRTS_RADIO_CS);
#endif

// Pulse source and frame builder
RTSPulseSource_ArduinoGPIO pulseSource(OPENRTS_RADIO_DATA);
RTSFrameBuilder frameBuilder;

// Print frames to Serial when received
void printFrame(RTSFrame *frame, uint8_t repeatCount, uint32_t repeatDuration, void *userData) {
    Serial.println("Detected an RTS Frame!");

    Serial.print("Command: ");
	Serial.print(rts_command_to_string(frame->command));
    Serial.print(" (0x");
    Serial.print((int)frame->command, HEX);
    Serial.println(")");

    Serial.print("Remote: 0x");
    Serial.println(frame->remote_address, HEX);

    Serial.print("Rolling Code: 0x");
    Serial.print(frame->rolling_code, HEX);
    Serial.print(" (");
    Serial.print(repeatCount);
    Serial.println(")");
    Serial.println();
}

void setup() {
    // Enable serial debugging
    Serial.begin(115200);

    // Configure radio
    radio.setMode(RTS_RADIO_MODE_RECEIVE);

    // Connect pulses to the framebuilder
    pulseSource.attach(&frameBuilder);
    pulseSource.enable();

    // Subscribe to new frames
    frameBuilder.setFrameCallback(printFrame);
}

void loop() {
    // Check for new RTS pulses
    pulseSource.update();
}