#include "sx1278.h"

void sx1278_init(sx1278_t *radio, spi_module_t *spi, bool use_pa_boost) {
    radio->spi_module = spi;
    radio->use_pa_boost = use_pa_boost;
    radio->power = 0;
    radio->mode = -1;

    spi->write_mask = 0x80;
    spi->read_mask = 0x00;
}

void sx1278_set_long_range_mode(sx1278_t *radio, bool long_range_mode) {
    spi_write_masked(radio->spi_module, RFM95_REG_OP_MODE, RFM95_LONG_RANGE_MODE, long_range_mode ? RFM95_LONG_RANGE_MODE_ON : RFM95_LONG_RANGE_MODE_OFF);
}

void sx1278_set_data_mode(sx1278_t *radio, int data_mode) {
    spi_write_masked(radio->spi_module, RFM95_REG_PACKET_CONFIG_2, RFM95_DATA_MODE, data_mode);
}

void sx1278_set_modulation_type(sx1278_t *radio, int modulation_type) {
    spi_write_masked(radio->spi_module, RFM95_REG_OP_MODE, RFM95_MODULATION_TYPE, modulation_type);
}

void sx1278_set_bit_sync_on(sx1278_t *radio, bool bit_sync_on) {
    spi_write_masked(radio->spi_module, RFM95_REG_OOK_PEAK, RFM95_BIT_SYNC, bit_sync_on ? RFM95_BIT_SYNC_ON : RFM95_BIT_SYNC_OFF);
}

void sx1278_set_frequency(sx1278_t *radio, int freq) {
    freq /= RFM95_FSTEP;
    spi_write(radio->spi_module, RFM95_REG_FRF_MSB, freq >> 16);
    spi_write(radio->spi_module, RFM95_REG_FRF_MID, freq >> 8);
    spi_write(radio->spi_module, RFM95_REG_FRF_LSB, freq);
}

void sx1278_set_bitrate(sx1278_t *radio, int bitrate) {
    bitrate = RFM95_FXOSC / bitrate;
    spi_write(radio->spi_module, RFM95_REG_BITRATE_MSB, bitrate >> 8);
    spi_write(radio->spi_module, RFM95_REG_BITRATE_LSB, bitrate);
}

void sx1278_set_rx_bandwidth(sx1278_t *radio, int rxBw) {
    uint8_t bwMant = RFM95_RX_BW_MANT_24;
    uint8_t bwExp = 5;

    if(rxBw == 2600) {
        bwMant = RFM95_RX_BW_MANT_24;
        bwExp = 7;
    } else if(rxBw == 3100) {
        bwMant = RFM95_RX_BW_MANT_20;
        bwExp = 7;
    } else if(rxBw == 3900) {
        bwMant = RFM95_RX_BW_MANT_16;
        bwExp = 7;
    } else if(rxBw == 5200) {
        bwMant = RFM95_RX_BW_MANT_24;
        bwExp = 6;
    } else if(rxBw == 6300) {
        bwMant = RFM95_RX_BW_MANT_20;
        bwExp = 6;
    } else if(rxBw == 7800) {
        bwMant = RFM95_RX_BW_MANT_16;
        bwExp = 6;
    } else if(rxBw == 10400) {
        bwMant = RFM95_RX_BW_MANT_24;
        bwExp = 5;
    } else if(rxBw == 12500) {
        bwMant = RFM95_RX_BW_MANT_20;
        bwExp = 5;
    } else if(rxBw == 15600) {
        bwMant = RFM95_RX_BW_MANT_16;
        bwExp = 5;
    } else if(rxBw == 20800) {
        bwMant = RFM95_RX_BW_MANT_24;
        bwExp = 4;
    } else if(rxBw == 25000) {
        bwMant = RFM95_RX_BW_MANT_20;
        bwExp = 4;
    } else if(rxBw == 31300) {
        bwMant = RFM95_RX_BW_MANT_16;
        bwExp = 4;
    } else if(rxBw == 41700) {
        bwMant = RFM95_RX_BW_MANT_24;
        bwExp = 3;
    } else if(rxBw == 50000) {
        bwMant = RFM95_RX_BW_MANT_20;
        bwExp = 3;
    } else if(rxBw == 62500) {
        bwMant = RFM95_RX_BW_MANT_16;
        bwExp = 3;
    } else if(rxBw == 83300) {
        bwMant = RFM95_RX_BW_MANT_24;
        bwExp = 2;
    } else if(rxBw == 100000) {
        bwMant = RFM95_RX_BW_MANT_20;
        bwExp = 2;
    } else if(rxBw == 125000) {
        bwMant = RFM95_RX_BW_MANT_16;
        bwExp = 2;
    } else if(rxBw == 166700) {
        bwMant = RFM95_RX_BW_MANT_24;
        bwExp = 1;
    } else if(rxBw == 200000) {
        bwMant = RFM95_RX_BW_MANT_20;
        bwExp = 1;
    } else if(rxBw == 250000) {
        bwMant = RFM95_RX_BW_MANT_16;
        bwExp = 1;
    } else {
        // TODO: ERROR
    }

    spi_write_masked(radio->spi_module, RFM95_REG_RX_BW, RFM95_RX_BW_MANT | RFM95_RX_BW_EXP, bwMant | bwExp);
}

void sx1278_set_transmit_power(sx1278_t *radio, int power) {
    if(radio->use_pa_boost) {
        // Transmit using the PA_BOOST pin
        spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_PA_SELECT, RFM95_PA_SELECT_PA_BOOST);

        if(power == 20) {
            // Enable +20dBm option
            spi_write_masked(radio->spi_module, RFM95_REG_PA_DAC, RFM95_PA_DAC, RFM95_PA_DAC_ENABLED);

            // Set output power
            spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_OUTPUT_POWER, 15);
        } else {
            // Disable the +20dBm option
            spi_write_masked(radio->spi_module, RFM95_REG_PA_DAC, RFM95_PA_DAC, RFM95_PA_DAC_DISABLED);

            // Set output power
            spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_OUTPUT_POWER, power - 2);
        }
    } else {
        // Transmit using RFO pins
        spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_PA_SELECT, RFM95_PA_SELECT_RFO);

        // Disable the +20dBm option
        spi_write_masked(radio->spi_module, RFM95_REG_PA_DAC, RFM95_PA_DAC, RFM95_PA_DAC_DISABLED);

        if(power < 0) {
            // Set output power
            spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_MAX_POWER, RFM95_MAX_POWER_LOW);
            spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_OUTPUT_POWER, power + 3);
        } else {
            // Set output power
            spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_MAX_POWER, RFM95_MAX_POWER_MAX);
            spi_write_masked(radio->spi_module, RFM95_REG_PA_CONFIG, RFM95_OUTPUT_POWER, power);
        }
    }
}

void sx1278_set_mode(sx1278_t *radio, int mode) {
    if(mode == radio->mode) return;

    // Set the new mode
    spi_write_masked(radio->spi_module, RFM95_REG_OP_MODE, RFM95_MODE, mode);

    // Wait for mode to become ready
    while(!(spi_read(radio->spi_module, RFM95_REG_IRQ_FLAGS_1) & RFM95_MODE_READY));

    radio->mode = mode;
}