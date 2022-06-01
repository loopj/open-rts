#include <stdio.h>

#include "driver/spi_master.h"

// Uncomment one of these or define your own RADIO_* defines (see boards.h)
// #define OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
// #define OPENRTS_BOARD_TTGO_LORA32_V21
// #define OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2

#include "open_rts.h"

#if defined(RADIO_TYPE_RFM69)
struct rfm69 radio;
#elif defined(RADIO_TYPE_SX1278)
struct sx1278 radio;
#else
#error "Must defined a supported radio type"
#endif

struct rts_frame_builder frame_builder;
struct rts_pulse_source pulse_source;

void init_radio()
{
    // Initialize SPI host bus
    spi_bus_config_t buscfg = {
        .miso_io_num   = RADIO_MISO,
        .mosi_io_num   = RADIO_MOSI,
        .sclk_io_num   = RADIO_SCK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    spi_bus_initialize(HSPI_HOST, &buscfg, 1);

    // Initialize SPI module
    struct spi_module spi = {
        .cs_pin = RADIO_CS,
        .clock  = 1000000,
        .mode   = 0,
    };
    spi_module_init_espidf(&spi, HSPI_HOST);

    // Initialize radio
    #if defined(RADIO_TYPE_RFM69)
    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);
    rfm69_set_mode(&radio, RFM69_MODE_RX);
    #elif defined(RADIO_TYPE_SX1278)
    sx1278_init(&radio, &spi, true);
    sx1278_configure_for_rts(&radio);
    sx1278_set_mode(&radio, SX1278_MODE_RX);
    #endif
}

void print_frame(struct rts_frame *frame, uint8_t count, uint32_t duration,
                 void *user_data)
{
    printf("Detected an RTS Frame!\n");
    printf("Command: %X\n", frame->command);
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
    rts_pulse_source_init_espidf_gpio(&pulse_source, RADIO_DATA);
    rts_pulse_source_attach(&pulse_source, &frame_builder);
    rts_pulse_source_enable(&pulse_source);
}
