#include "sdk_common.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_drv_twi.h"
#include "I2C.h"
#include "nrf_delay.h"
#include "bmp280.h"

bool read_calibration_data_bme280()
{ uint8_t rx_buf[33]={0};
 if( twi_register_read(BMP280_I2C_ADDRESS_0,BME280_REG_CAL_1part,rx_buf,BME280_REG_CAL_1part_number) == false) return false;
  //if( twi_register_read(BMP280_I2C_ADDRESS_0,BME280_REG_CAL_2part,&rx_buf[25],BME280_REG_CAL_2part_number) == false) return false;
  dig_T1=(uint16_t) ((rx_buf[1] << 8) | rx_buf[0]);
   NRF_LOG_INFO(":dig_T1 %d ", dig_T1);

  dig_T2=(uint16_t) ((rx_buf[3] << 8) | rx_buf[2]);
   NRF_LOG_INFO(":dig_T2 %d ", dig_T2);

   dig_T3=(uint16_t) ((rx_buf[5] << 8) | rx_buf[4]);
    NRF_LOG_INFO(":dig_T3 %d ", dig_T3);

  dig_P1=(uint16_t) ((rx_buf[7] << 8) | rx_buf[6]);
   NRF_LOG_INFO(":dig_P1 %d ",dig_P1);

  dig_P2=(uint16_t) ((rx_buf[9] << 8) | rx_buf[8]);
   NRF_LOG_INFO(":dig_P2 %d ", dig_P2);

  dig_P3=(uint16_t) ((rx_buf[11] << 8) | rx_buf[10]);
   NRF_LOG_INFO(":dig_P3 %d ", dig_P3);

  dig_P4=(uint16_t) ((rx_buf[13] << 8) | rx_buf[12]);
   NRF_LOG_INFO(":dig_P4 %d ", dig_P4);

  dig_P5=(uint16_t) ((rx_buf[15] << 8) | rx_buf[14]);
   NRF_LOG_INFO(":dig_P5 %d ", dig_P5);

  dig_P6=(uint16_t) ((rx_buf[17] << 8) | rx_buf[16]);
   NRF_LOG_INFO(":dig_P6 %d ", dig_P6);

  dig_P7=(uint16_t) ((rx_buf[19] << 8) | rx_buf[18]);
   NRF_LOG_INFO(":dig_P7 %d ", dig_P7);

  dig_P8=(uint16_t) ((rx_buf[21] << 8) | rx_buf[20]);
   NRF_LOG_INFO(":dig_P8 %d ", dig_P8);

  dig_P9=(uint16_t) ((rx_buf[23] << 8) | rx_buf[22]);
  NRF_LOG_INFO(":dig_P9 %d ", dig_P9);

return true;
 }

bool bme280_init()
{
   uint8_t rx_buf[1];
   if (twi_register_read(BMP280_I2C_ADDRESS_0,BMP280_REG_ID,rx_buf,1)==false)
    
    return false;
  
   NRF_LOG_INFO("ID: %d ", rx_buf[0]);
   if(rx_buf[0] != BME280_CHIP_ID  ) return false;
   if(twi_register_write(BMP280_I2C_ADDRESS_0, BMP280_REG_RESET, BMP280_RESET_VALUE) == false) return false;
   nrf_delay_ms(1000);
     
       
 if (twi_register_read(BMP280_I2C_ADDRESS_0,BMP280_REG_ID,rx_buf,1)==false)
    
    return false;
  
   NRF_LOG_INFO("ID: %d ", rx_buf[0]);
   if(rx_buf[0] != BME280_CHIP_ID  ) return false;
   
   if(read_calibration_data_bme280()==false) return false;
  ///// test
    if (twi_register_read(BMP280_I2C_ADDRESS_0,BMP280_REG_CONFIG,rx_buf,1)==false)
    return false;
    NRF_LOG_INFO("BMP280_REG_CONFIG: %d ", rx_buf[0]);
  ////// test 
   
   uint8_t config = (BMP280_STANDBY_250 << 5) | (BMP280_FILTER_16 << 2);
   if(twi_register_write(BMP280_I2C_ADDRESS_0, BMP280_REG_CONFIG, config)==false) 
   
   return false;
/////test
    if (twi_register_read(BMP280_I2C_ADDRESS_0,BMP280_REG_CONFIG,rx_buf,1)==false)
    return false;
    NRF_LOG_INFO("BMP280_REG_CONFIG: %d %d ", config, rx_buf[0]);
 ///// test  

 //// test
    if (twi_register_read(BMP280_I2C_ADDRESS_0,BMP280_REG_CTRL,rx_buf,1)==false)
    return false;
    NRF_LOG_INFO("BMP280_REG_CTRL: %d ", rx_buf[0]);
//// test 
   
   uint8_t ctrl = (BMP280_ULTRA_HIGH_RES << 5)
			| (BMP280_ULTRA_HIGH_RES << 2) | BMP280_MODE_NORMAL;

  
   if(twi_register_write(BMP280_I2C_ADDRESS_0, BMP280_REG_CTRL, ctrl)==false) 
   
   return false;
//// test
    if (twi_register_read(BMP280_I2C_ADDRESS_0,BMP280_REG_CTRL,rx_buf,1)==false)
    return false;
    NRF_LOG_INFO("BMP280_REG_CTRL: %d %d ", ctrl, rx_buf[0]);
//// test   
   return true;
    }

   static inline int32_t compensate_temperature(int32_t adc_temp,
		int32_t *fine_temp) 
                {
	int32_t var1, var2;

	var1 = ((((adc_temp >> 3) - ((int32_t) dig_T1 << 1)))
			* (int32_t) dig_T2) >> 11;
	var2 = (((((adc_temp >> 4) - (int32_t) dig_T1)
			* ((adc_temp >> 4) - (int32_t) dig_T1)) >> 12)
			* (int32_t) dig_T3) >> 14;
 
	*fine_temp = var1 + var2;
  int32_t teemp = (*fine_temp * 5 + 128) >> 8;
     NRF_LOG_INFO(":TEMP %d ", teemp);
       //  NRF_LOG_FLUSH();
	return teemp;
     
}

/**
 * Compensation algorithm is taken from BMP280 datasheet.
 *
 * Return value is in Pa, 24 integer bits and 8 fractional bits.
 */
static inline uint32_t compensate_pressure(int32_t adc_press,
		int32_t fine_temp) {
	int64_t var1, var2, p;

	var1 = (int64_t) fine_temp - 128000;
	var2 = var1 * var1 * (int64_t) dig_P6;
	var2 = var2 + ((var1 * (int64_t) dig_P5) << 17);
	var2 = var2 + (((int64_t) dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t) dig_P3) >> 8)
			+ ((var1 * (int64_t) dig_P2) << 12);
	var1 = (((int64_t) 1 << 47) + var1) * ((int64_t) dig_P1) >> 33;

	if (var1 == 0) {
		return 0;  // avoid exception caused by division by zero
	}

	p = 1048576 - adc_press;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = ((int64_t) dig_P9 * (p >> 13) * (p >> 13)) >> 25;
	var2 = ((int64_t) dig_P8 * p) >> 19;

	p = (((p + var1 + var2) >> 8) + ((int64_t) dig_P7 << 4))/256;
        NRF_LOG_INFO(":PRES %d ", p);
       //  NRF_LOG_FLUSH();

	return p;
}
bool bme280_read_adc(int32_t *temperature, uint32_t *pressure) {

int32_t adc_pressure;
  int32_t adc_temp;

 // nrf_delay_ms(4500);
   uint8_t rx_buf[8]={0};
   if (twi_register_read(BMP280_I2C_ADDRESS_0,BMP280_REG_adc_start,rx_buf,6)==false) return false;
  nrf_delay_ms(200);
   adc_pressure=rx_buf[0]<<12 | rx_buf[1]<<4 | rx_buf[2] >> 4;
   adc_temp=rx_buf[3]<<12 | rx_buf[4]<<4 | rx_buf[5] >> 4;
  
   int32_t fine_temp;
   *temperature=compensate_temperature(adc_temp, &fine_temp);
   *pressure = (compensate_pressure(adc_pressure, fine_temp));
  

   return true;
}