#if defined(ESP_PLATFORM)

#include "spi_module_espidf.h"

static void transfer(struct spi_module *spi_module, uint8_t *tx_buffer,
                     uint8_t *rx_buffer, uint8_t length)
{
    spi_transaction_t t = {
        .length    = 8 * length,
        .tx_buffer = tx_buffer,
        .rx_buffer = rx_buffer,
    };

    spi_device_transmit(spi_module->user_data_ptr, &t);

    // TODO: Handle errors
}

void spi_module_init_espidf(struct spi_module *spi_module,
                            spi_host_device_t host_device)
{
    spi_device_interface_config_t devcfg = {
        .mode           = spi_module->mode,
        .clock_speed_hz = spi_module->clock,
        .spics_io_num   = spi_module->cs_pin,
        .queue_size     = 1,
    };

    spi_module->transfer = transfer;

    spi_bus_add_device(host_device, &devcfg,
                       (spi_device_handle_t *)(&spi_module->user_data_ptr));

    // TODO: Handle errors
}

#endif