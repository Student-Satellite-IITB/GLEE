/*
 * Si7021.c
 *
 * Created: 03-09-2021 21:21:39
 *  Author: Akshat
 */ 
#define F_CPU 8000000 // 16MHz Clock frequency
#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>
#include "Si7021.h"
#include "I2C.h"


// check whether it is si7021 using EID
uint8_t SI7021_getDevice() {
	TWI_start();
	TWI_SLA_W(SI7021_ADDRESS<<1);
	TWI_transmit(SI7021_READ_EID_SNB_1);
	TWI_transmit(SI7021_READ_EID_SNB_2);
	TWI_Repeated_Start();   
	TWI_transmit((SI7021_ADDRESS<<1) + 0x01);
	uint8_t snb_1=TWI_receive(1);
	TWI_stop();
	return(snb_1);
	//TWI_transmit(SI7021_READ_ID1);
}

uint8_t SI7021_readFirmRev() {
	TWI_start();
	TWI_SLA_W((SI7021_ADDRESS<<1) + 0x00);
	TWI_transmit(SI7021_READ_FIRM_REV_1);
	TWI_transmit(SI7021_READ_FIRM_REV_2);
	TWI_Repeated_Start();
	TWI_SLA_W((SI7021_ADDRESS<<1) + 0x01);
	uint8_t firm = TWI_receive(0);
	TWI_stop();
	return firm;
}
float SI7021_Get_Measurment(uint8_t hold_command,uint8_t no_hold_command,int hold,int check){
	uint8_t msb,lsb;
	TWI_start();
	TWI_transmit((SI7021_ADDRESS<<1)+0x00);
	if(hold){
		TWI_transmit(hold_command);
		TWI_start();
		TWI_transmit((SI7021_ADDRESS<<1)+0x01);
		_delay_us(100);
	}
	else{
		
		TWI_transmit(no_hold_command);
		TWI_start();
		TWI_transmit((SI7021_ADDRESS<<1)+0x01);
		while((TWSR&0xF8)==0x48){
			TWI_start();
			TWI_transmit((SI7021_ADDRESS<<1)+0x01);
			_delay_us(10);
		}
	}
	msb=TWI_receive(0);
	if(check){
		lsb=TWI_receive(0);
		uint8_t checksum=TWI_receive(1);
		//idk do checksum algo
		TWI_stop();
		float val=((msb<<8)|lsb);
		if(!SI7021_error_check(val)){
			val*=175.72;
			val/=65536;
			val-=46.85;
			return val;
		}
		else{
			return -1;
		}

	}
	else{
		lsb=TWI_receive(1);
		TWI_stop();
		float val=((msb<<8)|lsb);
		val*=175.72;
		val/=65536;
		val-=46.85;
		return val;
	}
	
}
/*int SI7021_error_check(uint16_t data, uint8_t checkSum){
	uint32_t poly=0x131;//polynomial x8+x5+x4+1
	uint32_t num=data<<8;
	for
	return data;
}*/

// Sensor functions
/*uint16_t measurement(uint8_t cmd) {
	//Uncomment this when checksum is implemented
	//uint8_t n_bytes = 3; // MSB + LSB + Checksum
	//if (cmd == 0xE0) n_bytes = 2; //No checksum transfered when previous temperature (from RH measurement) is read
	

	
	TWI_init();
	TWI_start();
	TWI_SLA_W(SI7021_ADDRESS + 0x01);  // Address + Write bit
	TWI_transmit(cmd);
	TWI_Repeated_Start();
	TWI_SLA_W(SI7021_ADDRESS);
	
	uint8_t msb = TWI_receive(0);   // MSB
	uint8_t lsb = TWI_receive(1);   // LSB
	
	//uint8_t checksum = TWI_receive(1); // 
	
	TWI_stop();
	
	// lsb &= 0xFC; // LSB is of the form 0bxxxxxx00
	uint16_t measured_value = (msb << 8) | lsb;
	
	return measured_value;
}*/

/*float getRH(uint8_t hold) {
	
	if(hold){
		TWI_start();
		TWI_transmit((SI7021_ADDRESS<<1)+0x00);
		TWI_transmit(SI7021_MSR_RH_HOLD);
		TWI_Repeated_Start();	
		TWI_transmit((SI7021_ADDRESS<<1)+0x01);
		//_delay_ms(1);
		
		uint8_t msb=TWI_receive(0);
		uint8_t lsb=TWI_receive(1);
		uint8_t rh=(lsb);
		
		
		TWI_stop();
		
		return rh; 
		
	}
	else{
		TWI_start();
		TWI_transmit((SI7021_ADDRESS<<1)+0x00);
		TWI_transmit(SI7021_MSR_RH_NO_HOLD);
		while(TWDR!=0){
			TWI_transmit(SI7021_ADDRESS+0x00);
		}
		uint8_t lsb=TWI_receive(true);
		uint8_t msb=TWI_receive(true);
		return(lsb);
	}
}*/
float SI7021_Get_RH(int hold,int check){
	return (SI7021_Get_Measurment(SI7021_MSR_RH_HOLD,SI7021_MSR_RH_NO_HOLD,hold,check));
}
/*float getTemperature(uint8_t hold,int check) {
	uint8_t msb,lsb;
	TWI_start();
	TWI_transmit((SI7021_ADDRESS<<1)+0x00);
	if(hold){
		TWI_transmit(SI7021_MSR_TEMP_HOLD);
		TWI_start();
		TWI_transmit((SI7021_ADDRESS<<1)+0x01);
		_delay_us(100);
	}
	else{
		
		TWI_transmit(SI7021_MSR_TEMP_NO_HOLD);
		TWI_start();
		TWI_transmit((SI7021_ADDRESS<<1)+0x01);
		while((TWSR&0xF8)==0x48){
			TWI_start();
			TWI_transmit((SI7021_ADDRESS<<1)+0x01);
			_delay_us(10);			
		}
	}
	msb=TWI_receive(0);
	if(check){
		lsb=TWI_receive(0);
		uint8_t checksum=TWI_receive(1);
		//idk do checksum algo
		int isOk=error_check(temp,checksum);
	}
	else{
		lsb=TWI_receive(1);
	}
	TWI_stop();
	float temp=((msb<<8)|lsb);
	temp*=175.72;
	temp/=65536;
	temp-=46.85;
	return temp;

}*/
float SI7021_Get_Temperature(int hold,int check) {
	return (SI7021_Get_Measurment(SI7021_MSR_TEMP_HOLD,SI7021_MSR_TEMP_NO_HOLD,hold,check));
}



uint8_t getPrevTempRh(uint8_t hold) {
		TWI_start();
		TWI_transmit(SI7021_ADDRESS<<1);
		TWI_transmit(SI7021_READ_TEMP_PREV_RH);
		TWI_Repeated_Start();
		TWI_transmit((SI7021_ADDRESS<<1)+0x01);
		uint8_t msb=TWI_receive(0);
		uint8_t lsb=TWI_receive(1);
		TWI_stop();
		uint8_t temp=(msb<<8)|(lsb);
		temp*=175.72;
		temp/=65536;
		temp-=46.85;
		return temp;
		
		
}
