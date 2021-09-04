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

// Sensor functions
uint16_t measurement(uint8_t cmd) {
	TWI_init();
	TWI_start();
	TWI_SLA_W(SI7021_ADDRESS + 0x01);  // Address + Write bit
	TWI_transmit(cmd);
	TWI_Repeated_Start();
	TWI_SLA_W(SI7021_ADDRESS);
	uint8_t msb = TWI_receive(0);   // MSB
	uint8_t lsb = TWI_receive(1);   // LSB
	TWI_stop();
	
	lsb &= 0xFC; // LSB is of the form 0bxxxxxx00
	uint16_t measured_value = (msb << 8) | lsb;
}

uint16_t getRH(bool hold) {
	//master no hold mode
	if(!hold) {
		uint16_t rh = measurement(SI7021_MSR_RH_NO_HOLD);
		return rh;
	}
	//master hold mode
	else {
		
	}
}

uint8_t getTemperature(bool hold) {
	//master no hold mode
	if(!hold) {
		uint16_t rh = measurement(SI7021_MSR_TEMP_NO_HOLD);
		return rh;
	}
	//master hold mode
	else {
		
	}
}
