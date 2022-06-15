#ifndef OOKRADIO_ERRORS_H
#define OOKRADIO_ERRORS_H

/**
 * @file
 */

/**
 * @addtogroup ookradio
 * @{
 */

enum {
    /// All good
    OOKRADIO_ERR_NONE = 0,

    /// The radio pointer is NULL
    OOKRADIO_ERR_INVALID_HANDLE = -1,

    /// The spi_module pointer is NULL
    OOKRADIO_ERR_INVALID_SPI = -2,

    /// The attached SPI module could not be identified
    OOKRADIO_ERR_INVALID_MODULE = -3,

    /// SPI init failed
    OOKRADIO_ERR_SPI_INIT_FAILED = -4,

    /// SPI transfer failed
    OOKRADIO_ERR_SPI_TRANSFER_FAILED = -5,
};

/**
 * @}
 */

#endif // OOKRADIO_ERRORS_H