// Uncomment one of these or define your own OPENRTS_* defines (see boards.h)
// #define OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
// #define OPENRTS_BOARD_TTGO_LORA32_V21
// #define OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2

#include "open_rts.h"

// Pulse source and frame builder
RTSPulseSource_ArduinoGPIO pulseSource(OPENRTS_RADIO_DATA);
RTSFrameBuilder frameBuilder;

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
    rts_radio_set_mode(&radio, RTS_RADIO_MODE_RECEIVE);
}

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
    init_radio();

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