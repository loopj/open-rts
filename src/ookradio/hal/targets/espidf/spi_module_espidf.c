#if defined(ESP_PLATFORM)

#include "../../../errors.h"
#include "spi_module_espidf.h"

static int transfer(struct spi_module *spi_module, uint8_t *tx_buffer,
                    uint8_t *rx_buffer, uint8_t length)
{
    spi_transaction_t t = {
        .length    = 8 * length,
        .tx_buffer = tx_buffer,
        .rx_buffer = rx_buffer,
    };

    esp_err_t status = spi_device_transmit(spi_module->user_data_ptr, &t);
    if(status != ESP_OK) {
        return OOKRADIO_ERR_SPI_TRANSFER_FAILED;
    }

    return OOKRADIO_ERR_NONE;
}

int spi_module_init_espidf(struct spi_module *spi_module,
                           spi_host_device_t host_device)
{
    spi_device_interface_config_t devcfg = {
        .mode           = spi_module->mode,
        .clock_speed_hz = spi_module->clock,
        .spics_io_num   = spi_module->cs_pin,
        .queue_size     = 1,
    };

    spi_module->transfer = transfer;

    esp_err_t status = spi_bus_add_device(host_device, &devcfg,
                       (spi_device_handle_t *)(&spi_module->user_data_ptr));

    if(status != ESP_OK) {
        return OOKRADIO_ERR_SPI_INIT_FAILED;
    }

    return OOKRADIO_ERR_NONE;
}

#endif