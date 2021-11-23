/*
 * Si7021.c
 *
 * Created: 03-09-2021 21:21:39
 *  Author: Akshat
 */ 
#include <avr/io.h>
#include <stdbool.h>
#include "Si7021.h"
#include "I2C.h"

// Electronic ID
//uint16_t readElecID () {
	//TWI_start();
	//TWI_SLA_W(SI7021_ADDRESS + 0x01);
	//TWI_transmit(SI7021_READ_ID1);
//}

uint8_t readFirmRev() {
	TWI_start();
	TWI_SLA_W(SI7021_ADDRESS + 0x01);
	TWI_transmit(SI7021_READ_FIRM_REV_1);
	TWI_transmit(SI7021_READ_FIRM_REV_2);
	TWI_Repeated_Start();
	TWI_SLA_W(SI7021_ADDRESS);
	uint8_t firm = TWI_receive(1);
	TWI_stop();
	return firm;
}

// Sensor functions
uint16_t measurement(uint8_t cmd) {
	//Uncomment this when checksum is implemented
	//uint8_t n_bytes = 3; // MSB + LSB + Checksum
	//if (cmd == 0xE0) n_bytes = 2; //No checksum transfered when previous temperature (from RH measurement) is read
	
	uint8_t n_bytes = 2; // MSB + LSB
	
	TWI_init();
	TWI_start();
	TWI_SLA_W(SI7021_ADDRESS + 0x01);  // Address + Write bit
	TWI_transmit(cmd);
	TWI_Repeated_Start();
	TWI_SLA_W(SI7021_ADDRESS);
	
	uint8_t msb = TWI_receive(0);   // MSB
	uint8_t lsb = TWI_receive(1);   // LSB
	
	uint8_t checksum = TWI_receive(1); // 
	
	TWI_stop();
	
	// lsb &= 0xFC; // LSB is of the form 0bxxxxxx00
	uint16_t measured_value = (msb << 8) | lsb;
	
	return measured_value;
}

uint16_t getRH(uint8_t hold) {
	//master no hold mode
	if(!hold) {
		uint16_t rh = measurement(SI7021_MSR_RH_NO_HOLD);
		return rh;
	}
}

uint8_t getTemperature(uint8_t hold) {
	//master no hold mode
	if(!hold) {
		uint16_t rh = measurement(SI7021_MSR_TEMP_NO_HOLD);
		return rh;
	}

}

uint8_t getPrevTemp(uint8_t hold) {
		//master no hold mode
		if(!hold) {
			uint16_t temp = measurement(SI7021_READ_TEMP_PREV_RH);
			return temp;
		}
		//master hold mode
		else {
			
		}
}
