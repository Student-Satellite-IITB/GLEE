# LSM9DS1 Sensor

## Introduction
LSM9DS1 is a 3D accelerometer, 3D gyroscope, 3D magnetometer sensor. This is one of the two sensors, as specified by the GLEE Team at CU Boulder, which will be present on all the chipstas. Acceleremoter data from this sensor will also be used by seismology payload for micrometeroid detection.

## Features
* 3 acceleration channels, 3 angular rate channels, 3 magnetic field channels
* SPI / I2C serial interfaces
* Embedded FIFO
* ±2/±4/±8/±16 g linear acceleration full scale

## LSM9DS1 Functionality
In the LSM9DS1, the accelerometer and gyroscope have two operating modes available: only accelerometer active and gyroscope in power down or both accelerometer and 
gyroscope sensors active at the same ODR(output data rate).\
The magnetic sensor has three operating modes available: power-down (default), continuous-conversion mode and single-conversion mode.

## Accelerometer and Gyroscope FIFO
The LSM9DS1 embeds 32 slots of FIFO for each of the gyroscope’s and accelerometer’s three output channels. This allows consistent power saving for the system since the 
host microcontroller does not need to continuously poll data from the sensor, but it can wake up only when needed and burst the significant data out from the FIFO. This buffer can work according to five different modes: Bypass mode, FIFO-mode, Continuous mode, Continuous-to-FIFO mode and Bypass-to-Continuous. These modes can be changed by changing values of certain bits in the designated register.
