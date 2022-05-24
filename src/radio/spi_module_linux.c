#if defined(__linux__)

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

#include "spi_module_linux.h"

static void transfer(struct spi_module *spi_module, uint8_t *tx_buffer,
                     uint8_t *rx_buffer, uint8_t length)
{
    // TODO Make speed configurable from spi->clock
    struct spi_ioc_transfer transfer = {
        .tx_buf   = (unsigned long)tx_buffer,
        .rx_buf   = (unsigned long)rx_buffer,
        .speed_hz = 1000000,
        .len      = length,
    };

    ioctl(spi_module->user_data_int, SPI_IOC_MESSAGE(1), &transfer);

    // TODO: Handle errors
}

void spi_module_init_linux(struct spi_module *spi_module, const char *device)
{
    spi_module->transfer      = transfer;
    spi_module->user_data_int = open(device, O_RDWR);
}

#endif