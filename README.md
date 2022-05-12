# Smartwach

## Idea:
To create a universal tool for writing and testing algorithms to detect human activity and interact with him in a convenient way.

In addition, one of the tasks of the device is to retrain from a smartwatch to a sports tool.
For example, a cyclist - the clock is mounted on the handlebar, it connects the sensors for cadence and speed, wind speed, accelerometer via bluetooth. with the help of which you can absolutely accurately describe the cyclist, what power he performs in what time, how he reacts to climbs and descents.

## Hardware tasks:
   - Module GPS.
   - Electricity consumption measuring system to calculate the exact working time.
_____________________________
Selection of electronic components in times of difficult availability in warehouses:

Microcontroller: nRF52840 
   - Built-in BLE which allows full communication with a smartphone or auxiliary sensors.
   - 32Mhz SPI, which allows you to quickly update the screen.
   - Very low energy consumption compared to other companies.

Due to the low availability of chips on the market or the overpriced price, I use the module EBYTE E73-2G4M08S1C, which has a chip, necessary parts for work and an antenna.

Sensors:
   -BMP280 allows you to measure the temperature and pressure of the atmosphere with a fairly high accuracy.
   -MPU9250 3-axis accelerometer, gyroscope and magnetometer.
   -MAX30100 pulse and saturation sensor (mounted on the housing).
   -APDS-9960 a light sensor, as well as a gesture detection tool that you can use to control the device.

With the help of these two sensors, human activity can be read quite accurately.
Example:
    -number of steps taken + at what angle to the horizon.
    -various physical activities: running, cycling, swimming, etc.

Version 0.9 is designed to check sensors, write test firmware to check functionality already v1.0 PCB.
Also to check the stability of Bluetooth connections and activity calculation algorithms.


## HW 
V0.9

![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/2d%20v_0.9(prot).jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/3d%20v_0.9(prot).jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/photo1%20v_0%2C9(prot).jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/photo2%20v_0%2C9(prot).jpg)


Praca BLE VIDEO: https://youtu.be/vYCpAYbpFlk

_____________________________

V1.0 Oczekiwanie na dostawę PCB i elementów elektronicznych...

![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/2d%20v_1.0.jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/3d%20v_1.0.jpg)

_____________________________


