#include <openrts.hpp>
#include <U8g2lib.h>

// Supported OLEDs
#if defined(OPENRTS_OLED_TYPE_SH1107)
U8G2 display = U8G2_SH1107_64X128_1_HW_I2C(U8G2_R1);
#elif defined(OPENRTS_OLED_TYPE_SSD1306) && defined(OPENRTS_OLED_RST)
U8G2 display = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, OPENRTS_OLED_RST, OPENRTS_OLED_SCL, OPENRTS_OLED_SDA);
#elif defined(OPENRTS_OLED_TYPE_SSD1306)
U8G2 display = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0);
#endif

// Supported radio modules
#if defined(OPENRTS_RADIO_TYPE_RFM69)
RTSRadio_RFM69 radio(OPENRTS_RADIO_CS);
#elif defined(OPENRTS_RADIO_TYPE_SX1278)
RTSRadio_SX1278 radio(OPENRTS_RADIO_CS);
#endif

// Pulse source and frame builder
RTSPulseSource_GPIO pulseSource(OPENRTS_RADIO_DATA);
RTSFrameBuilder frameBuilder;

// Drawing status
bool shouldRedraw = true;
RTSFrame *lastFrame = nullptr;
uint8_t lastRepeatCount = 0;

// Draw the last frame we received (if any)
void drawFrame() {
    uint8_t x = 0;
    uint8_t y = 0;

    // Draw a border around the screen
    display.setDrawColor(1);
    display.drawBox(0, 0, display.getWidth(), 16);

    // Draw the title (inverted)
    display.setDrawColor(0);
    display.setCursor((display.getWidth() - display.getStrWidth("RTS Frame Sniffer"))/2, y+3);
    display.print("RTS Frame Sniffer");
    display.setDrawColor(1);
    y+=23;

    // Draw the frame
    if(lastFrame == nullptr) {
        display.setCursor((display.getWidth() - display.getStrWidth("Listening..."))/2, 38);
        display.print("Listening...");
    } else {
        display.setCursor(x, y);
        display.print("Command:");
        display.setCursor(x+60, y);
        display.print(rts_command_to_string(lastFrame->command));
        y += 14;

        display.setCursor(x, y);
        display.print("Remote:");
        display.setCursor(x+60, y);
        display.print(lastFrame->remote_address, HEX);
        y += 14;

        display.setCursor(x, y);
        display.print("Rolling:");
        display.setCursor(x+60, y);
        display.print(lastFrame->rolling_code, HEX);
        display.setCursor(x+100, y);
        display.print(lastRepeatCount);
    }
}

void setup() {
    // Set up display
    display.begin();
    display.setFont(u8g2_font_lucasfont_alternate_tr);
    display.setFontPosTop();
    display.setFontMode(1);

    // Configure radio
    radio.begin();
    radio.setMode(RTS_RADIO_MODE_RECEIVE);

    // Connect pulses to the framebuilder
    pulseSource.attach(&frameBuilder);
    pulseSource.enable();

    // Subscribe to new frames
    frameBuilder.setFrameCallback([](RTSFrame *frame, uint8_t repeatCount, uint32_t repeatDuration, void *userData) {
        if(lastFrame) {
            delete lastFrame;
        }

        lastFrame = new RTSFrame(*frame);
        lastRepeatCount = repeatCount;
        shouldRedraw = true;
    });
}

void loop() {
    // Redraw the screen
    if(shouldRedraw) {
        display.firstPage();
        do {
            drawFrame();
        } while(display.nextPage());

        shouldRedraw = false;
    }

    // Check for new RTS pulses
    pulseSource.update();
}