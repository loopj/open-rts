#include "rfm69.h"

void rfm69_init(struct rfm69 *radio, struct spi_module *spi, bool use_pa_boost)
{
    radio->spi_module   = spi;
    radio->use_pa_boost = use_pa_boost;
    radio->power        = 0;
    radio->mode         = -1;

    spi->write_mask = 0x80;
    spi->read_mask  = 0x00;
}

void rfm69_configure_for_rts(struct rfm69 *radio)
{
    rfm69_set_data_mode(radio, RFM69_DATA_MODE_CONTINUOUS);
    rfm69_set_modulation_type(radio, RFM69_MODULATION_TYPE_OOK);
    rfm69_set_frequency(radio, 433420000);
    rfm69_set_bitrate(radio, 1200);
    rfm69_set_rx_bandwidth(radio, 83300);
    rfm69_set_transmit_power(radio, 20);
}

void rfm69_set_data_mode(struct rfm69 *radio, int mode)
{
    spi_write_masked(radio->spi_module, RFM69_REG_DATA_MODUL, RFM69_DATA_MODE,
                     mode);
}

void rfm69_set_modulation_type(struct rfm69 *radio, int modulation)
{
    spi_write_masked(radio->spi_module, RFM69_REG_DATA_MODUL,
                     RFM69_MODULATION_TYPE, modulation);
}

void rfm69_set_frequency(struct rfm69 *radio, int freq)
{
    freq /= RFM69_FSTEP;
    spi_write(radio->spi_module, RFM69_REG_FRF_MSB, freq >> 16);
    spi_write(radio->spi_module, RFM69_REG_FRF_MID, freq >> 8);
    spi_write(radio->spi_module, RFM69_REG_FRF_LSB, freq);
}

void rfm69_set_bitrate(struct rfm69 *radio, int bitrate)
{
    int bitrate_bps = RFM69_FXOSC / bitrate;
    spi_write(radio->spi_module, RFM69_REG_BITRATE_MSB, bitrate_bps >> 8);
    spi_write(radio->spi_module, RFM69_REG_BITRATE_LSB, bitrate_bps);
}

void rfm69_set_rx_bandwidth(struct rfm69 *radio, int rxBw)
{
    uint8_t bwMant = RFM69_RX_BW_MANT_24;
    uint8_t bwExp  = 5;

    if (rxBw == 1300) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 7;
    } else if (rxBw == 1600) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 7;
    } else if (rxBw == 2000) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 7;
    } else if (rxBw == 2600) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 6;
    } else if (rxBw == 3100) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 6;
    } else if (rxBw == 3900) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 6;
    } else if (rxBw == 5200) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 5;
    } else if (rxBw == 6300) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 5;
    } else if (rxBw == 7800) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 5;
    } else if (rxBw == 10400) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 4;
    } else if (rxBw == 12500) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 4;
    } else if (rxBw == 15600) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 4;
    } else if (rxBw == 20800) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 3;
    } else if (rxBw == 25000) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 3;
    } else if (rxBw == 31300) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 3;
    } else if (rxBw == 41700) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 2;
    } else if (rxBw == 50000) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 2;
    } else if (rxBw == 62500) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 2;
    } else if (rxBw == 83300) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 1;
    } else if (rxBw == 100000) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 1;
    } else if (rxBw == 125000) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 1;
    } else if (rxBw == 166700) {
        bwMant = RFM69_RX_BW_MANT_24;
        bwExp  = 0;
    } else if (rxBw == 200000) {
        bwMant = RFM69_RX_BW_MANT_20;
        bwExp  = 0;
    } else if (rxBw == 250000) {
        bwMant = RFM69_RX_BW_MANT_16;
        bwExp  = 0;
    } else {
        // TODO: ERROR
    }

    spi_write_masked(radio->spi_module, RFM69_REG_RX_BW,
                     RFM69_RX_BW_MANT | RFM69_RX_BW_EXP, bwMant | bwExp);
}

void rfm69_set_transmit_power(struct rfm69 *radio, int power)
{
    if (radio->use_pa_boost) {
        if (power <= 10) {
            // -2 to 13 dBm, PA1 is enough
            spi_write(radio->spi_module, RFM69_REG_PA_LEVEL,
                      RFM69_PA1_ON | (power + 18));
        } else if (power <= 17) {
            // 13 to 17 dBm, both PAs required
            spi_write(radio->spi_module, RFM69_REG_PA_LEVEL,
                      RFM69_PA1_ON | RFM69_PA2_ON | (power + 14));
        } else {
            // 18 - 20 dBm, both PAs and high power settings required
            spi_write(radio->spi_module, RFM69_REG_PA_LEVEL,
                      RFM69_PA1_ON | RFM69_PA2_ON | (power + 11));
        }
    } else {
        // low power module, use only PA0
        spi_write(radio->spi_module, RFM69_REG_PA_LEVEL,
                  RFM69_PA0_ON | (power + 18));
    }

    radio->power = power;
}

void rfm69_set_mode(struct rfm69 *radio, int mode)
{
    if (mode == radio->mode)
        return;

    // Set the new mode
    spi_write_masked(radio->spi_module, RFM69_REG_OP_MODE, RFM69_MODE, mode);

    // Wait for mode to become ready
    // while (!(spi_read(radio->spi_module, RFM69_REG_IRQ_FLAGS_1) &
    //          RFM69_MODE_READY))
    //     ;

    radio->mode = mode;
}
