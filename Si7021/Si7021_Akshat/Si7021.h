/*
 * Si7021.h
 *
 * Created: 03-09-2021 21:19:44
 *  Author: Akshat
 */ 


#ifndef SI7021_H_
#define SI7021_H_

// Sensor address
#define SI7021_ADDRESS           0x40                         // Slave (Si7021) Address

//Command description
#define SI7021_MSR_RH_HOLD       0xE5                         // Measure RH, Hold master mode
#define SI7021_MSR_RH_NO_HOLD    0xF5                         // Measure RH, No hold master mode
#define SI7021_MSR_TEMP_HOLD     0xE3                         // Measure Temperature, Hold master mode
#define SI7021_MSR_TEMP_NO_HOLD  0xF3                         // Measure Temperature, No hold master mode
#define SI7021_READ_TEMP_PREV_RH 0xE0                         // Read temperature from previous RH measurement
#define SI7021_RESET             0xFE                         // Reset the sensor
#define SI7021_WRITE_RHT_UR1     0xE6                         // Write to RH/T to user register 1
#define SI7021_READ_RHT_UR1      0xE7                         // Read RH/T from user register 1
#define SI7021_WRITE_HEATER_CR   0x51                         // Write Heater Control Register
#define SI7021_READ_HEATER_CR    0x11                         // Read Heater Control Register
#define SI7021_READ_ID1          0xFA                         // Read 1st byte of electronic ID
#define SI7021_READ_ID2          0xFC                         // Read 2nd byte of electronic ID
#define SI7021_READ_FIRM_REV     0x84                         // Read firmware revision version

//Sensor functions
uint8_t readElecID();                                         // To read electronic ID (pending)
uint8_t measurement(uint8_t cmd);                                            // To make measurement (pending)
uint8_t getRH(bool hold);                                              // To read Relative Humidity value (pending)
uint8_t getTemperature(bool hold);                                     // To read Temperature value (pending)
void reset();                                                 // To reset the sensor (pending)
void enableHeater();                                          // To enable or disable heater (pending)
void heaterLevel();                                           // To set heater level (pending)



#endif /* SI7021_H_ */