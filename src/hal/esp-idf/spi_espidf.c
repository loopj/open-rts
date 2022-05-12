#if defined(ESP_PLATFORM)

#include <string.h>

#include <driver/spi_master.h>

#include "hal/spi.h"

void hal_spi_init(struct spi_module_t *spi) {
    spi_device_interface_config_t devcfg = {
        .mode = spi->mode,
        .clock_speed_hz = spi->clock,
        .spics_io_num = spi->cs_pin,
        .queue_size = 1,
    };

    spi_bus_add_device(HSPI_HOST, &devcfg, (spi_device_handle_t *)(&spi->user_data));
}

void hal_spi_transfer(struct spi_module_t *spi, uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t length) {
    spi_transaction_t t = {
        .length = 8*length,
        .tx_buffer = tx_buffer,
        .rx_buffer = rx_buffer,
    };

    spi_device_transmit(spi->user_data, &t);
}

#endif