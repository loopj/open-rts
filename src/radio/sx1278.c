#include "sx1278.h"
#include <stdio.h>

// TODO: Return error code if sensible init fails
// E.g. check SPI is not NULL, and check "version" register
void sx1278_init(struct sx1278 *radio, struct spi_module *spi,
                 bool use_pa_boost)
{
    radio->spi_module   = spi;
    radio->use_pa_boost = use_pa_boost;
    radio->power        = 0;
    radio->mode         = -1;

    spi->write_mask = 0x80;
    spi->read_mask  = 0x00;
}

void sx1278_configure_for_rts(struct sx1278 *radio)
{
    sx1278_set_long_range_mode(radio, SX1278_LONG_RANGE_MODE_OFF);
    sx1278_set_data_mode(radio, SX1278_DATA_MODE_CONTINUOUS);
    sx1278_set_modulation_type(radio, SX1278_MODULATION_TYPE_OOK);
    sx1278_set_bit_sync_on(radio, false);
    sx1278_set_frequency(radio, 433420000);
    sx1278_set_bitrate(radio, 1200);
    sx1278_set_rx_bandwidth(radio, 62500);
    sx1278_set_transmit_power(radio, 20);
}

void sx1278_set_long_range_mode(struct sx1278 *radio, bool long_range_mode)
{
    spi_write_masked(radio->spi_module, SX1278_REG_OP_MODE,
                     SX1278_LONG_RANGE_MODE,
                     long_range_mode ? SX1278_LONG_RANGE_MODE_ON
                                     : SX1278_LONG_RANGE_MODE_OFF);
}

void sx1278_set_data_mode(struct sx1278 *radio, int data_mode)
{
    spi_write_masked(radio->spi_module, SX1278_REG_PACKET_CONFIG_2,
                     SX1278_DATA_MODE, data_mode);
}

void sx1278_set_modulation_type(struct sx1278 *radio, int modulation_type)
{
    spi_write_masked(radio->spi_module, SX1278_REG_OP_MODE,
                     SX1278_MODULATION_TYPE, modulation_type);
}

void sx1278_set_bit_sync_on(struct sx1278 *radio, bool bit_sync_on)
{
    spi_write_masked(radio->spi_module, SX1278_REG_OOK_PEAK, SX1278_BIT_SYNC,
                     bit_sync_on ? SX1278_BIT_SYNC_ON : SX1278_BIT_SYNC_OFF);
}

void sx1278_set_frequency(struct sx1278 *radio, int freq)
{
    freq /= SX1278_FSTEP;
    spi_write(radio->spi_module, SX1278_REG_FRF_MSB, freq >> 16);
    spi_write(radio->spi_module, SX1278_REG_FRF_MID, freq >> 8);
    spi_write(radio->spi_module, SX1278_REG_FRF_LSB, freq);
}

void sx1278_set_bitrate(struct sx1278 *radio, int bitrate)
{
    bitrate = SX1278_FXOSC / bitrate;
    spi_write(radio->spi_module, SX1278_REG_BITRATE_MSB, bitrate >> 8);
    spi_write(radio->spi_module, SX1278_REG_BITRATE_LSB, bitrate);
}

void sx1278_set_rx_bandwidth(struct sx1278 *radio, int rxBw)
{
    uint8_t bwMant = SX1278_RX_BW_MANT_24;
    uint8_t bwExp  = 5;

    if (rxBw == 2600) {
        bwMant = SX1278_RX_BW_MANT_24;
        bwExp  = 7;
    } else if (rxBw == 3100) {
        bwMant = SX1278_RX_BW_MANT_20;
        bwExp  = 7;
    } else if (rxBw == 3900) {
        bwMant = SX1278_RX_BW_MANT_16;
        bwExp  = 7;
    } else if (rxBw == 5200) {
        bwMant = SX1278_RX_BW_MANT_24;
        bwExp  = 6;
    } else if (rxBw == 6300) {
        bwMant = SX1278_RX_BW_MANT_20;
        bwExp  = 6;
    } else if (rxBw == 7800) {
        bwMant = SX1278_RX_BW_MANT_16;
        bwExp  = 6;
    } else if (rxBw == 10400) {
        bwMant = SX1278_RX_BW_MANT_24;
        bwExp  = 5;
    } else if (rxBw == 12500) {
        bwMant = SX1278_RX_BW_MANT_20;
        bwExp  = 5;
    } else if (rxBw == 15600) {
        bwMant = SX1278_RX_BW_MANT_16;
        bwExp  = 5;
    } else if (rxBw == 20800) {
        bwMant = SX1278_RX_BW_MANT_24;
        bwExp  = 4;
    } else if (rxBw == 25000) {
        bwMant = SX1278_RX_BW_MANT_20;
        bwExp  = 4;
    } else if (rxBw == 31300) {
        bwMant = SX1278_RX_BW_MANT_16;
        bwExp  = 4;
    } else if (rxBw == 41700) {
        bwMant = SX1278_RX_BW_MANT_24;
        bwExp  = 3;
    } else if (rxBw == 50000) {
        bwMant = SX1278_RX_BW_MANT_20;
        bwExp  = 3;
    } else if (rxBw == 62500) {
        bwMant = SX1278_RX_BW_MANT_16;
        bwExp  = 3;
    } else if (rxBw == 83300) {
        bwMant = SX1278_RX_BW_MANT_24;
        bwExp  = 2;
    } else if (rxBw == 100000) {
        bwMant = SX1278_RX_BW_MANT_20;
        bwExp  = 2;
    } else if (rxBw == 125000) {
        bwMant = SX1278_RX_BW_MANT_16;
        bwExp  = 2;
    } else if (rxBw == 166700) {
        bwMant = SX1278_RX_BW_MANT_24;
        bwExp  = 1;
    } else if (rxBw == 200000) {
        bwMant = SX1278_RX_BW_MANT_20;
        bwExp  = 1;
    } else if (rxBw == 250000) {
        bwMant = SX1278_RX_BW_MANT_16;
        bwExp  = 1;
    } else {
        // TODO: ERROR
    }

    spi_write_masked(radio->spi_module, SX1278_REG_RX_BW,
                     SX1278_RX_BW_MANT | SX1278_RX_BW_EXP, bwMant | bwExp);
}

void sx1278_set_transmit_power(struct sx1278 *radio, int power)
{
    if (radio->use_pa_boost) {
        // Transmit using the PA_BOOST pin
        spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                         SX1278_PA_SELECT, SX1278_PA_SELECT_PA_BOOST);

        if (power == 20) {
            // Enable +20dBm option
            spi_write_masked(radio->spi_module, SX1278_REG_PA_DAC,
                             SX1278_PA_DAC, SX1278_PA_DAC_ENABLED);

            // Set output power
            spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                             SX1278_OUTPUT_POWER, 15);
        } else {
            // Disable the +20dBm option
            spi_write_masked(radio->spi_module, SX1278_REG_PA_DAC,
                             SX1278_PA_DAC, SX1278_PA_DAC_DISABLED);

            // Set output power
            spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                             SX1278_OUTPUT_POWER, power - 2);
        }
    } else {
        // Transmit using RFO pins
        spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                         SX1278_PA_SELECT, SX1278_PA_SELECT_RFO);

        // Disable the +20dBm option
        spi_write_masked(radio->spi_module, SX1278_REG_PA_DAC, SX1278_PA_DAC,
                         SX1278_PA_DAC_DISABLED);

        if (power < 0) {
            // Set output power
            spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                             SX1278_MAX_POWER, SX1278_MAX_POWER_LOW);
            spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                             SX1278_OUTPUT_POWER, power + 3);
        } else {
            // Set output power
            spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                             SX1278_MAX_POWER, SX1278_MAX_POWER_MAX);
            spi_write_masked(radio->spi_module, SX1278_REG_PA_CONFIG,
                             SX1278_OUTPUT_POWER, power);
        }
    }
}

void sx1278_set_mode(struct sx1278 *radio, int mode)
{
    if (mode == radio->mode)
        return;

    // Set the new mode
    spi_write_masked(radio->spi_module, SX1278_REG_OP_MODE, SX1278_MODE, mode);

    // Wait for mode to become ready
    while (!(spi_read(radio->spi_module, SX1278_REG_IRQ_FLAGS_1) &
             SX1278_MODE_READY))
        ;

    radio->mode = mode;
}