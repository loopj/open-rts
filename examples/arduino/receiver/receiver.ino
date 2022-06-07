// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
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

// Paired remote persistence
#if OPENRTS_HAS_NVS
RTSRemoteStore_NVS remoteStore;
#elif OPENRTS_HAS_EEPROM
RTSRemoteStore_EEPROM remoteStore;
#else
RTSRemoteStore_Memory remoteStore;
#endif

RTSReceiver receiver(new RTSPulseSource_ArduinoGPIO(OPENRTS_RADIO_DATA), &remoteStore);

void frameCallback(enum rts_receiver_event event, RTSFrame *frame, void *userData) {
    Serial.println("Got an RTS event!");

    switch (event) {
    case RTS_RECEIVER_EVENT_PRESS:
        Serial.println("Button Pressed");
        break;
    case RTS_RECEIVER_EVENT_HOLD:
        Serial.println("Button Held");
        break;
    case RTS_RECEIVER_EVENT_HOLD_2:
        Serial.println("Button Held (Double)");
        break;
    case RTS_RECEIVER_EVENT_HOLD_3:
        Serial.println("Button Held (Triple)");
        break;
    default:
        break;
    }

    Serial.print("Command: ");
	Serial.println(rts_command_to_string(frame->command));
    Serial.print("Remote: 0x");
	Serial.println(frame->remote_address, HEX);
    Serial.print("Rolling Code: 0x");
	Serial.println(frame->rolling_code, HEX);
}

void modeCallback(enum rts_receiver_mode mode, void *userData) {
    switch (mode) {
    case RTS_RECEIVER_MODE_OFF:
        digitalWrite(OPENRTS_LED, 0);
        Serial.println("[Mode Changed] Receiver Off");
        break;
    case RTS_RECEIVER_MODE_PROGRAMMING:
        digitalWrite(OPENRTS_LED, 1);
        Serial.println("[Mode Changed] Programming Mode");
        break;
    case RTS_RECEIVER_MODE_COMMAND:
        digitalWrite(OPENRTS_LED, 0);
        Serial.println("[Mode Changed] Command Mode");
        break;
    }
}

void pollModeButton() {
    static int eventFired = 0;
    static bool lastState = false;
    static unsigned long pressedTime = 0;

    // Check if button is pressed
    bool state = !digitalRead(OPENRTS_BUTTON_1);
    unsigned long now = millis();
    if (state == true && lastState == false) {
        pressedTime = now;
        eventFired  = 0;
    }

    // Handle button press/held events
    if (state == true && lastState == true) {
        if (now - pressedTime > 2000 && eventFired == 0) {
            // Button pressed and held for > 2s, enter programming mode
			receiver.setMode(RTS_RECEIVER_MODE_PROGRAMMING);
            eventFired++;
        } else if (now - pressedTime > 4000 && eventFired == 1) {
            // Button pressed and held for > 4s, forget all paired remotes
            // and go back into command mode
			receiver.forgetAllRemotes();
			receiver.setMode(RTS_RECEIVER_MODE_COMMAND);
            eventFired++;
        }
    }

    lastState = state;
}

void setup() {
    // Enable serial debugging
    Serial.begin(115200);

    // Set up the onboard button and LED
    pinMode(OPENRTS_BUTTON_1, INPUT_PULLUP);
    pinMode(OPENRTS_LED, OUTPUT);

    // Configure radio
    radio.setMode(RTS_RADIO_MODE_RECEIVE);

    // Set callbacks for new frames and mode change events
	receiver.setFrameCallback(frameCallback);
	receiver.setModeCallback(modeCallback);

	// Enable the receiver
	receiver.setMode(RTS_RECEIVER_MODE_COMMAND);
}

void loop() {
    // Check for new RTS pulses
    receiver.update();

	// Check for receiver "mode" button presses
	pollModeButton();
}