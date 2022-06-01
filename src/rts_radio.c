#include "rts_radio.h"

#define RTS_FREQUENCY 433420000

void rts_radio_init_rfm69(struct rts_radio *radio, struct spi_module *spi, bool use_pa_boost)
{
	rfm69_init(&radio->rfm69, spi, use_pa_boost);

	// Configure radio for RTS
	rfm69_set_data_mode(&radio->rfm69, RFM69_DATA_MODE_CONTINUOUS);
    rfm69_set_modulation_type(&radio->rfm69, RFM69_MODULATION_TYPE_OOK);
    rfm69_set_frequency(&radio->rfm69, RTS_FREQUENCY);
    rfm69_set_bitrate(&radio->rfm69, 1200);
    rfm69_set_rx_bandwidth(&radio->rfm69, 83300);
    rfm69_set_transmit_power(&radio->rfm69, 20);

	radio->type = RTS_RADIO_MODULE_RFM69;
}

void rts_radio_init_sx1278(struct rts_radio *radio, struct spi_module *spi, bool use_pa_boost)
{
	sx1278_init(&radio->sx1278, spi, use_pa_boost);

	// Configure radio for RTS
	sx1278_set_long_range_mode(&radio->sx1278, SX1278_LONG_RANGE_MODE_OFF);
    sx1278_set_data_mode(&radio->sx1278, SX1278_DATA_MODE_CONTINUOUS);
    sx1278_set_modulation_type(&radio->sx1278, SX1278_MODULATION_TYPE_OOK);
    sx1278_set_bit_sync_on(&radio->sx1278, false);
    sx1278_set_frequency(&radio->sx1278, RTS_FREQUENCY);
    sx1278_set_bitrate(&radio->sx1278, 1200);
    sx1278_set_rx_bandwidth(&radio->sx1278, 62500);
    sx1278_set_transmit_power(&radio->sx1278, 20);

	radio->type = RTS_RADIO_MODULE_SX1278;
}

void rts_radio_set_mode(struct rts_radio *radio, enum rts_radio_mode mode)
{
	switch(mode) {
		case RTS_RADIO_MODE_STANDBY:
			if(radio->type == RTS_RADIO_MODULE_RFM69) {
				rfm69_set_mode(&radio->rfm69, RFM69_MODE_STDBY);
			} else if(radio->type == RTS_RADIO_MODULE_SX1278) {
				sx1278_set_mode(&radio->sx1278, SX1278_MODE_STDBY);
			}
			break;
		case RTS_RADIO_MODE_RECEIVE:
			if(radio->type == RTS_RADIO_MODULE_RFM69) {
				rfm69_set_mode(&radio->rfm69, RFM69_MODE_RX);
			} else if(radio->type == RTS_RADIO_MODULE_SX1278) {
				sx1278_set_mode(&radio->sx1278, SX1278_MODE_RX);
			}
			break;
		case RTS_RADIO_MODE_TRANSMIT:
			if(radio->type == RTS_RADIO_MODULE_RFM69) {
				rfm69_set_mode(&radio->rfm69, RFM69_MODE_TX);
			} else if(radio->type == RTS_RADIO_MODULE_SX1278) {
				sx1278_set_mode(&radio->sx1278, SX1278_MODE_TX);
			}
			break;
		default:
			// TODO: Log warning
			break;
	}
}