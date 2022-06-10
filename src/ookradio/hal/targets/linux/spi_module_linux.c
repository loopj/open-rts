#if defined(__linux__)

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "spi_module_linux.h"

static int transfer(struct spi_module *spi_module, uint8_t *tx_buffer,
                     uint8_t *rx_buffer, uint8_t length)
{
    if(spi_module->user_data_int == -1) {
        printf("SPI transfer failed\n");
        return -1;
    }

    struct spi_ioc_transfer transfer = {
        .tx_buf   = (unsigned long)tx_buffer,
        .rx_buf   = (unsigned long)rx_buffer,
        .speed_hz = spi_module->clock,
        .len      = length,
    };

    if(ioctl(spi_module->user_data_int, SPI_IOC_MESSAGE(1), &transfer) == -1) {
        perror("SPI transfer failed");
        return -1;
    }

    return 0;
}

int spi_module_init_linux(struct spi_module *spi_module, const char *device)
{
    spi_module->transfer      = transfer;
    spi_module->user_data_int = open(device, O_RDWR);

    if(spi_module->user_data_int == -1) {
        perror("SPI init failed");
        return -1;
    }
}

#endif