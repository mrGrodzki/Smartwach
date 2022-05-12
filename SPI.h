
#include  <stdint.h> 
#include  <stdbool.h> 

#include "nrf_drv_spi.h"
#define SPI_INSTANCE  1 /**< SPI instance index. */

static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */
static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */

static uint8_t       m_tx_buf[12];           /**< TX buffer. */
static uint8_t       m_rx_buf[12];    /**< RX buffer. */
static const uint8_t m_length = sizeof(m_tx_buf);        /**< Transfer length. */

 void ST7789_WriteCommand(uint8_t cmd);

 void ST7789_WriteData(uint8_t *buff, size_t buff_size);

 void ST7789_WriteSmallData(uint8_t data);

void SPI_init();

