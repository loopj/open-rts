#pragma once

#include <stdbool.h>

#include "hal/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sx1278_t {
    spi_module_t *spi_module;
    bool use_pa_boost;
    int power;
    int mode;
} sx1278_t;

void sx1278_init(sx1278_t *radio, spi_module_t *spi, bool use_pa_boost);
void sx1278_set_long_range_mode(sx1278_t *radio, bool long_range_mode);
void sx1278_set_data_mode(sx1278_t *radio, int mode);
void sx1278_set_modulation_type(sx1278_t *radio, int modulation);
void sx1278_set_bit_sync_on(sx1278_t *radio, bool bit_sync_on);
void sx1278_set_frequency(sx1278_t *radio, int freq);
void sx1278_set_bitrate(sx1278_t *radio, int bitrate);
void sx1278_set_rx_bandwidth(sx1278_t *radio, int bw);
void sx1278_set_transmit_power(sx1278_t *radio, int power);
void sx1278_set_mode(sx1278_t *radio, int mode);


// Oscillator
#define RFM95_FXOSC 32000000.0
#define RFM95_FSTEP (RFM95_FXOSC / 524288)

// Registers
#define RFM95_REG_OP_MODE               0x01
#define RFM95_REG_BITRATE_MSB           0x02
#define RFM95_REG_BITRATE_LSB           0x03
#define RFM95_REG_FRF_MSB               0x06
#define RFM95_REG_FRF_MID               0x07
#define RFM95_REG_FRF_LSB               0x08
#define RFM95_REG_PA_CONFIG             0x09
#define RFM95_REG_PA_RAMP               0x0A
#define RFM95_REG_OCP                   0x0B
#define RFM95_REG_RX_BW                 0x12
#define RFM95_REG_OOK_PEAK              0x14
#define RFM95_REG_OOK_FIX               0x15
#define RFM95_REG_PACKET_CONFIG_2       0x31
#define RFM95_REG_IRQ_FLAGS_1           0x3E
#define RFM95_REG_DIO_MAPPING_1         0x40
#define RFM95_REG_PA_DAC                0x4D

// RegOpMode                            0x01
#define RFM95_LONG_RANGE_MODE           0x80
#define RFM95_LONG_RANGE_MODE_OFF       0x00
#define RFM95_LONG_RANGE_MODE_ON        0x80

#define RFM95_MODULATION_TYPE           0x60
#define RFM95_MODULATION_TYPE_FSK       0x00
#define RFM95_MODULATION_TYPE_OOK       0x20

#define RFM95_LOW_FREQUENCY_MODE        0x08
#define RFM95_LOW_FREQUENCY_MODE_OFF    0x00
#define RFM95_LOW_FREQUENCY_MODE_ON     0x08

#define RFM95_MODE                      0x07
#define RFM95_MODE_SLEEP                0x00
#define RFM95_MODE_STDBY                0x01
#define RFM95_MODE_FSTX                 0x02
#define RFM95_MODE_TX                   0x03
#define RFM95_MODE_FSRX                 0x04
#define RFM95_MODE_RX                   0x05

// RegPaConfig                          0x09
#define RFM95_PA_SELECT                 0x80
#define RFM95_PA_SELECT_RFO             0x00
#define RFM95_PA_SELECT_PA_BOOST        0x80
#define RFM95_MAX_POWER                 0x70
#define RFM95_MAX_POWER_MAX             0x70
#define RFM95_MAX_POWER_LOW             0x20
#define RFM95_OUTPUT_POWER              0x0F

// RegPaRamp                            0x0A



// RegRxBw                              0x12
#define RFM95_RX_BW_MANT                0x18
#define RFM95_RX_BW_MANT_16             0x00
#define RFM95_RX_BW_MANT_20             0x08
#define RFM95_RX_BW_MANT_24             0x10
#define RFM95_RX_BW_EXP                 0x07

// RegOokPeak                           0x14
#define RFM95_BIT_SYNC                  0x20
#define RFM95_BIT_SYNC_ON               0x20
#define RFM95_BIT_SYNC_OFF              0x00
#define RFM95_OOK_THRESH_TYPE           0x18
#define RFM95_OOK_THRESH_TYPE_FIXED     0x00
#define RFM95_OOK_THRESH_TYPE_PEAK      0x08
#define RFM95_OOK_THRESH_TYPE_AVERAGE   0x10

// RegPacketConfig2                     0x31
#define RFM95_DATA_MODE                 0x40
#define RFM95_DATA_MODE_CONTINUOUS      0x00
#define RFM95_DATA_MODE_PACKET          0x40

// RegIrqFlags1                         0x3E
#define RFM95_MODE_READY                0x80

// RegPaDac                             0x4D
#define RFM95_PA_DAC                    0x07
#define RFM95_PA_DAC_ENABLED            0x07
#define RFM95_PA_DAC_DISABLED           0x04

#ifdef __cplusplus
} // extern "C"
#endif