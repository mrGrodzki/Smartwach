
#include "sdk_common.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_drv_twi.h"
#include "I2C.h"
#include "nrf_delay.h"



void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            m_xfer_done = true;
            break;
        default:
            break;
    }
}

/**
 * @brief UART initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_lm75b_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_lm75b_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

/**
 * @brief Function for reading data from temperature sensor.
 */
bool twi_register_write(uint8_t dev_address, uint8_t register_address, uint8_t value)
{
    ret_code_t err_code;
    uint8_t tx_buf[2];
    tx_buf[0]=register_address;
    tx_buf[1]=value;

    m_xfer_done=false;

    err_code=nrf_drv_twi_tx(&m_twi, dev_address, tx_buf, 2, false);
    while(m_xfer_done==false);
    if (NRF_SUCCESS!=err_code) return false;
    return true;
}


bool twi_register_read(uint8_t dev_address, uint8_t register_address, uint8_t * destination, uint8_t number_of_bytes)
{
  ret_code_t err_code;
  m_xfer_done=false;
  err_code=nrf_drv_twi_tx(&m_twi, dev_address, &register_address, 1, true);
  while(m_xfer_done==false);
  if(NRF_SUCCESS!=err_code) return false;

  m_xfer_done=false;
  err_code=nrf_drv_twi_rx(&m_twi, dev_address, destination, number_of_bytes);
  while(m_xfer_done==false);
  if(NRF_SUCCESS!=err_code) return false;
  return true;
}