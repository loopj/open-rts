#include <stdio.h>

#include "driver/spi_master.h"

#include "open_rts.h"

// Feather ESP32 + RFM69
// #define SPI_SS      33
// #define SPI_SCLK    5
// #define SPI_MOSI    18
// #define SPI_MISO    19
// #define DATA_PIN    25

// Sparkfun ESP32 LoRa 1-CH Gateway
#define SPI_SS   16
#define SPI_MOSI 13
#define SPI_MISO 12
#define SPI_SCLK 14
#define DATA_PIN 32

struct rfm69 radio;
struct rts_frame_builder frame_builder;
struct rts_pulse_source pulse_source;

void init_radio()
{
    // Initialize SPI host bus
    spi_bus_config_t buscfg = {
        .miso_io_num   = SPI_MISO,
        .mosi_io_num   = SPI_MOSI,
        .sclk_io_num   = SPI_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    spi_bus_initialize(HSPI_HOST, &buscfg, 1);

    // Initialize SPI module
    struct spi_module spi = {
        .cs_pin = SPI_SS,
        .clock  = 1000000,
        .mode   = 0,
    };
    spi_module_init_espidf(&spi, HSPI_HOST);

    // Initialize radio
    rfm69_init(&radio, &spi, true);
    rfm69_configure_for_rts(&radio);
    rfm69_set_mode(&radio, RFM69_MODE_RX);
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
    rts_pulse_source_init_espidf_gpio(&pulse_source, DATA_PIN);
    rts_pulse_source_attach(&pulse_source, &frame_builder);
    rts_pulse_source_enable(&pulse_source);
}
