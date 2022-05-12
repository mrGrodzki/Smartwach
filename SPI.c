

#include "sdk_common.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_drv_spi.h"
#include "st7789.h"

#include "SPI.h"

 void ST7789_WriteCommand(uint8_t cmd)
{
	
	ST7789_DC_Clr();
        spi_xfer_done = false;
         APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, &cmd, sizeof(cmd), m_rx_buf, 0));

        while (!spi_xfer_done)
        {
            __WFE();
        }
        //nrf_delay_ms(2);
	
}



/**
 * @brief Write data to ST7789 controller
 * @param buff -> pointer of data buffer
 * @param buff_size -> size of the data buffer
 * @return none
 */
 void ST7789_WriteData(uint8_t *buff, size_t buff_size)
{
	ST7789_DC_Set();

	// split data in small chunks because HAL can't send more than 64K at once

	while (buff_size > 0) {
		uint8_t chunk_size = buff_size > 255 ? 255 : buff_size;
                  spi_xfer_done = false;
                 APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buff, chunk_size, m_rx_buf, 0));

        while (!spi_xfer_done)
        {
            __WFE();
        }

		buff += chunk_size;
		buff_size -= chunk_size;
               // nrf_delay_us(2);
	}

}

 void ST7789_WriteSmallData(uint8_t data)
{
	
	ST7789_DC_Set();
            spi_xfer_done = false;
           APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi,  &data, sizeof(data), m_rx_buf, 0));

        while (!spi_xfer_done)
        {
            __WFE();
        }
//nrf_delay_ms(2);
}

void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{
    spi_xfer_done = true;
    NRF_LOG_INFO("Transfer completed.");
    if (m_rx_buf[0] != 0)
    {
        NRF_LOG_INFO(" Received:");
        NRF_LOG_HEXDUMP_INFO(m_rx_buf, strlen((const char *)m_rx_buf));
    }
}

void SPI_init()
{
 nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin   =  NRF_DRV_SPI_PIN_NOT_USED;
    spi_config.miso_pin =  NRF_DRV_SPI_PIN_NOT_USED;
    spi_config.mosi_pin = ST7789_MOSI;
    spi_config.sck_pin  = ST7789_SCL;
    spi_config.bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST;
    spi_config.frequency = NRF_SPI_FREQ_8M;
    spi_config.mode= NRF_SPI_MODE_3;
    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));

}