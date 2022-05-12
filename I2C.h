
#include  <stdint.h> 
#include  <stdbool.h>
#include "nrf_drv_twi.h"
 

/* TWI instance ID. */
#define TWI_INSTANCE_ID     0

/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_done = false;

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Buffer for samples read from temperature sensor. */
static uint8_t m_sample;

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context);

void twi_init (void);

bool twi_register_write(uint8_t dev_address, uint8_t register_address, uint8_t value);

bool twi_register_read(uint8_t dev_address, uint8_t register_address, uint8_t * destination, uint8_t number_of_bytes);