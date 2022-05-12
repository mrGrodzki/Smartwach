

#include  <stdint.h> 
#include  <stdbool.h> 



#define  BMP280_I2C_ADDRESS_0       0x76
#define BMP280_REG_ID          0xD0
#define BMP280_REG_RESET       0xE0
#define BME280_REG_CAL_1part 0x88
#define BME280_REG_CAL_1part_number 25
#define BME280_REG_CAL_2part 0xE3
#define BME280_REG_CAL_2part_number 8
#define BMP280_REG_CONFIG      0xF5 /* bits: 7-5 t_sb; 4-2 filter; 0 spi3w_en */
#define BMP280_REG_CTRL        0xF4 /* bits: 7-5 osrs_t; 4-2 osrs_p; 1-0 mode */
#define BMP280_REG_adc_start   0xF7


#define BME280_CHIP_ID  0x58
#define BMP280_RESET_VALUE     0xB6
#define BMP280_STANDBY_250  3
#define BMP280_STANDBY_4000  7
#define BMP280_STANDBY_250  3
#define BMP280_FILTER_OFF  0
#define BMP280_FILTER_16  4
#define BMP280_MODE_SLEEP 0
#define BMP280_MODE_NORMAL  3
#define BMP280_STANDARD 3
#define BMP280_ULTRA_HIGH_RES  5

  uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;



bool read_calibration_data_bme280();

bool bme280_init();

static inline uint32_t compensate_pressure(int32_t adc_press, int32_t fine_temp);

bool bme280_read_adc(int32_t *temperature, uint32_t *pressure);