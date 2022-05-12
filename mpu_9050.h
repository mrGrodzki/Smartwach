

#include  <stdint.h> 
#include  <stdbool.h> 


//addres
#define MPU9050_I2C_ADDRESS_0 0x68
#define MPU9050_REG_ID 0x75
#define MPU_9050_PWR_MGMT_1 0x6B
#define MPU_9050_FIFO_EN 0x23
#define MPU_9050_ADD_MEAS_START  0x3B
#define MPU_9050_SMPLRT_DIV_REG 0x19
#define MPU_9050_ACCEL_CONFIG_REG 0x1C
#define MPU_9050_GYRO_CONFIG_REG 0x1B
#define MPU_9050_int_bypass_REG 0x37



//data
#define MPU_9050_ACCEL_CONFIG 0x00
#define MPU_9050_GYRO_CONFIG 0x00
#define MPU_9050_Internal_Sample_Rate 0x07
#define MPU_9050_soft_reset 0x80
#define MPU9050_CHIP_ID 0x71
#define MPU9050_fifo_en 0x78
#define MPU9050_bypass_en 0x22


bool mpu9050_init();

bool MPU9050_read();

//void mpu_9050_steps();
