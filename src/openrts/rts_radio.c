#include "rts_radio.h"

#define RTS_FREQUENCY 433420000

static void rts_radio_set_mode_rfm69(struct rts_radio *radio, enum rts_radio_mode mode)
{
    struct rfm69 *module = radio->module;
    switch (mode) {
    case RTS_RADIO_MODE_STANDBY:
        rfm69_set_mode(module, RFM69_MODE_STDBY);
        break;
    case RTS_RADIO_MODE_RECEIVE:
        rfm69_set_mode(module, RFM69_MODE_RX);
        break;
    case RTS_RADIO_MODE_TRANSMIT:
        rfm69_set_mode(module, RFM69_MODE_TX);
        break;
    default:
        break;
    }
}

void rts_radio_init_rfm69(struct rts_radio *radio, struct spi_module *spi, struct rfm69 *rfm69)
{
    // Initialize radio on the SPI bus
    rfm69_init(rfm69, spi);

    // Configure radio for RTS
    rfm69_set_data_mode(rfm69, RFM69_DATA_MODE_CONTINUOUS);
    rfm69_set_modulation_type(rfm69, RFM69_MODULATION_TYPE_OOK);
    rfm69_set_frequency(rfm69, RTS_FREQUENCY);
    rfm69_set_bitrate(rfm69, 1200);
    rfm69_set_rx_bandwidth(rfm69, 83300);
    rfm69_set_transmit_power(rfm69, 20, true);

    // Set up function hooks
    radio->set_mode = rts_radio_set_mode_rfm69;
    radio->module = rfm69;
}

static void rts_radio_set_mode_sx1278(struct rts_radio *radio, enum rts_radio_mode mode)
{
    struct sx1278 *module = radio->module;
    switch (mode) {
    case RTS_RADIO_MODE_STANDBY:
        sx1278_set_mode(module, SX1278_MODE_STDBY);
        break;
    case RTS_RADIO_MODE_RECEIVE:
        sx1278_set_mode(module, SX1278_MODE_RX);
        break;
    case RTS_RADIO_MODE_TRANSMIT:
        sx1278_set_mode(module, SX1278_MODE_TX);
        break;
    default:
        break;
    }
}

void rts_radio_init_sx1278(struct rts_radio *radio, struct spi_module *spi, struct sx1278 *sx1278)
{
    // Initialize radio on the SPI bus
    sx1278_init(sx1278, spi);

    // Configure radio for RTS
    sx1278_set_long_range_mode(sx1278, SX1278_LONG_RANGE_MODE_OFF);
    sx1278_set_data_mode(sx1278, SX1278_DATA_MODE_CONTINUOUS);
    sx1278_set_modulation_type(sx1278, SX1278_MODULATION_TYPE_OOK);
    sx1278_set_bit_sync_on(sx1278, false);
    sx1278_set_frequency(sx1278, RTS_FREQUENCY);
    sx1278_set_bitrate(sx1278, 1200);
    sx1278_set_rx_bandwidth(sx1278, 62500);
    sx1278_set_transmit_power(sx1278, 20, true);

    // Set up function hooks
    radio->set_mode = rts_radio_set_mode_sx1278;
    radio->module = sx1278;
}

void rts_radio_set_mode(struct rts_radio *radio, enum rts_radio_mode mode)
{
    if (!radio->set_mode) {
        // TODO: Log an error
        return;
    }

    radio->set_mode(radio, mode);
}