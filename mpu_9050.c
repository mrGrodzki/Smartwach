
#include "sdk_common.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_drv_twi.h"
#include "I2C.h"
#include "nrf_delay.h"
#include "mpu_9050.h"

#include "math.h"

int counter=0;
int counter_mass=0;
int stat=0;

uint16_t steeep=0;

uint32_t mass [100]= {0};
uint32_t sum_test = 0;
uint32_t sum_mass = 0;
uint32_t sum_beck = 0;
uint32_t avg_sum=0;
uint32_t max_sum =0;
uint32_t  sum_max =0;
uint32_t  sum_test_beck =0;
uint32_t  sum_max_beck =0;

double  mess[10]={'0'};

bool mpu9050_init()
{

 uint8_t rx_buf[1];
   if (twi_register_read(MPU9050_I2C_ADDRESS_0,MPU9050_REG_ID,rx_buf,1)==false)
    
    return false;
  
   NRF_LOG_INFO("ID: %d ", rx_buf[0]);
   if(rx_buf[0] != MPU9050_CHIP_ID  ) return false;
////////
if(twi_register_write(MPU9050_I2C_ADDRESS_0, MPU_9050_PWR_MGMT_1, MPU_9050_soft_reset)==false) 
   
   return false;
   nrf_delay_ms(1000);
  if (twi_register_read(MPU9050_I2C_ADDRESS_0,MPU_9050_PWR_MGMT_1,rx_buf,1)==false)
    
    return false;
  
   NRF_LOG_INFO("pwr_m: %d ", rx_buf[0]);
   nrf_delay_ms(1000);
//////
   if(twi_register_write(MPU9050_I2C_ADDRESS_0, MPU_9050_SMPLRT_DIV_REG, MPU_9050_Internal_Sample_Rate)==false) 
    return false;

///
 if(twi_register_write(MPU9050_I2C_ADDRESS_0, MPU_9050_ACCEL_CONFIG_REG, MPU_9050_ACCEL_CONFIG)==false) 
  return false;

//
   if(twi_register_write(MPU9050_I2C_ADDRESS_0, MPU_9050_GYRO_CONFIG_REG, MPU_9050_GYRO_CONFIG)==false) 
   
   return false;

   }

 

bool MPU9050_read(uint8_t * data_axis_mass)
{
   // uint8_t data_axis_mass[24]= {0};
   uint8_t Rec_Data[14]= {0};
   if (twi_register_read(MPU9050_I2C_ADDRESS_0,MPU_9050_ADD_MEAS_START,Rec_Data,14)==false)
    
    return false;
 // for(int i=0; i<7; i++)
  //{
    //mess[i] = uint16_big_decode(&rx_buf[(i*2)]);

    //}
 // mess[4] = uint16_big_decode(&rx_buf[8]);
 // mess[5] = uint16_big_decode(&rx_buf[10]);
 // mess[6] = uint16_big_decode(&rx_buf[12]);

  mess[0] = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    mess[1] = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
   mess[2] = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);
  //  mess[3] = (int16_t) (Rec_Data[6] << 8 | Rec_Data[7]);
   mess[3] = (int16_t) (Rec_Data[8] << 8 | Rec_Data[9]);
   mess[4] = (int16_t) (Rec_Data[10] << 8 | Rec_Data[11]);
  mess[5] = (int16_t) (Rec_Data[12] << 8 | Rec_Data[13]);
/*
  mess[0]=mess[0]/16384.0;
  mess[1]=mess[1]/16384.0;
  mess[2]=mess[2]/14418.0;
  //mess[3]=mess[3](float) ((int16_t) temp / (float) 340.0 + (float) 36.53);
  mess[3]=mess[3]/131.0;
  mess[4]=mess[4]/131.0;
  mess[5]=mess[5]/131.0;
*/

   NRF_LOG_INFO("ACCEL X: %g ", mess[0]);
   NRF_LOG_INFO("ACCEL Y: %g ", mess[1]);
   NRF_LOG_INFO("ACCEL Z: %g ", mess[2]);
   NRF_LOG_INFO("-------- ", Rec_Data[0]);
   NRF_LOG_FLOAT( mess[2]);

 double lsb=0;
  double msb=0;
 uint8_t sign=0; // 0 = +  1 = -

  for(int i=0; i<6; i++)
  {
  lsb=modf(mess[i], &msb);
  if(mess[i]<0) 
  {
    lsb=fabs(lsb);
    msb=fabs(msb);
    sign=1;
  }
  else sign=0;
  
  uint16_t ui_lsb= (uint16_t) (lsb*10000);
  uint8_t ui_msb= (uint8_t) msb;
  uint16_encode(ui_lsb, &data_axis_mass[i*4]);
  data_axis_mass[(i*4+2)]=ui_msb;
  data_axis_mass[(i*4+3)]=sign;
  }
}


void mpu_9050_steps()
{
    uint8_t Rec_Data[14]= {0};
   if (twi_register_read(MPU9050_I2C_ADDRESS_0,MPU_9050_ADD_MEAS_START,Rec_Data,14)==false)
    
    return false;
  int16_t mas_data[6];
   mas_data[0] = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    mas_data[1] = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
   mas_data[2] = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);
   mas_data[3] = (int16_t) (Rec_Data[8] << 8 | Rec_Data[9]);
   mas_data[4] = (int16_t) (Rec_Data[10] << 8 | Rec_Data[11]);
  mas_data[5] = (int16_t) (Rec_Data[12] << 8 | Rec_Data[13]);

  uint32_t sum=0;

	  	   sum_test=fabs(mas_data[3])+fabs(mas_data[4])+fabs(mas_data[5]);
	  	   if(max_sum>sum_test){
	  	if (counter_mass<100 ) counter_mass++; else counter_mass=0;
	  	mass[counter_mass] = max_sum;

	 for(int i=0; i<100; i++) {sum_mass =sum_mass+mass[i];}


		  	   avg_sum=sum_mass/100;
		  	 avg_sum= avg_sum- avg_sum*0.1;
		  	   sum_mass=0;
		  	   sum_max_beck = max_sum;
		  	 if(avg_sum<1000) avg_sum=1000;
		  	   if(max_sum>avg_sum) steeep++;


	  	 sum_max_beck =max_sum;
	  	 max_sum=sum_test;
	  	  }
	  	   else    {

	  		 max_sum=sum_test;
	  		   sum_beck=sum_test;
	  	   }

//return steeep;
} 
