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

#include <stdio.h>

#include <driver/spi_master.h>

#include <openrts.h>

struct rts_radio radio;
struct rts_frame_builder frame_builder;
struct rts_pulse_source pulse_source;

void init_radio()
{
    // Initialize the ESP-IDF SPI host bus
    spi_bus_config_t buscfg = {
        .miso_io_num   = OPENRTS_RADIO_MISO,
        .mosi_io_num   = OPENRTS_RADIO_MOSI,
        .sclk_io_num   = OPENRTS_RADIO_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    spi_bus_initialize(HSPI_HOST, &buscfg, 1);

    // Initialize SPI module for the radio
    struct spi_module spi = {
        .cs_pin = OPENRTS_RADIO_CS,
        .clock  = 1000000,
        .mode   = 0,
    };
    spi_module_init_espidf(&spi, HSPI_HOST);

    // Initialize radio
    #if defined(OPENRTS_RADIO_TYPE_RFM69)
    rts_radio_init_rfm69(&radio, &spi);
    #elif defined(OPENRTS_RADIO_TYPE_SX1278)
    rts_radio_init_sx1278(&radio, &spi);
    #endif

    rts_radio_set_mode(&radio, RTS_RADIO_MODE_RECEIVE);
}

void print_frame(struct rts_frame *frame, uint8_t count, uint32_t duration,
                 void *user_data)
{
    printf("Detected an RTS Frame!\n");
    printf("Command: %s\n", rts_command_to_string(frame->command));
    printf("Remote: 0x%06X\n", frame->remote_address);
    printf("Rolling Code: 0x%04X (%d)\n\n", frame->rolling_code, count);
}

void app_main()
{
    // Initialize the radio
    init_radio();

    // Set up a framebuilder and subscribe to new frames
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder, print_frame, NULL);

    // Set up a GPIO pulse source, send pulses to the framebuilder
    rts_pulse_source_init_espidf_gpio(&pulse_source, OPENRTS_RADIO_DATA);
    rts_pulse_source_attach(&pulse_source, &frame_builder);
    rts_pulse_source_enable(&pulse_source);
}
