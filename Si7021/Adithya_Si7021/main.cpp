/*
 * SensorLibrary.cpp
 *
 * Created: 01-09-2021 23:11:20
 * Author : Adithya Raj Mishra
 */ 

//twi0 bus is used here


#define F_CPU 100000000UL  //havent checked F_CPU from datasheet 

#include <avr/io.h>
#include <avr/delay.h>



#include "GLEE_Si7021.h"
#include "TWI.h"

void initTWI(){
	
	TWSR0=0x00;
	TWBR0=0x0C;
	TWDR0=0;
}

void waitForFlagSet(){
	while(!(TWCR0 & 1<<TWINT));
}

void sendAck(bool ack){
	TWCR0=ack<<TWEA|1<<TWINT|1<<TWEN;
	waitForFlagSet();
}

void start(){
	TWCR0=1<<TWEN|1<<TWSTA|1<<TWINT;
	waitForFlagSet();
	
}
void sendAddress(uint8_t adr,bool rw){//rw=0,SLA+W;rw=1,SLA+R
	TWDR0=adr<<1|rw;
	TWCR0=1<<TWINT|1<<TWEN;
	waitForFlagSet();
	
}
void sendCommand(uint8_t cmd){
	TWDR0=cmd;
	TWCR0=1<<TWINT|1<<TWEN;
	waitForFlagSet();
	
}
void stop(){
	TWCR0=(1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
	
}

uint8_t read(){
	return TWDR0;
}
bool checkStatus(uint8_t statCode){
	if((TWSR0 &0xF8 )!=statCode){
		return false;
	}
	return true;
}

void reset(){
	start();
	sendAddress(I2CADR,0);
	sendCommand(SI7021_RESET_CMD);
	stop();
	
}
uint8_t readTemp(bool hold){//hold decides the mode of reading temp
	
	start();
	
	sendAddress(I2CADR,0);
	
	if(hold){
		sendCommand(SI7021_TEMP_HOLD_CMD);
		_delay_us(TEMP_14BIT_CONV_TIME);
	}
	else{
		sendCommand(SI7021_TEMP_NOHOLD_CMD);
		_delay_us(TEMP_14BIT_CONV_TIME);
		start();
		sendAddress(I2CADR,1);
		
	}
	if(!checkStatus(0x50)){ //if data and ACK not received, return error
		return ERR;
	}
	
	sendAck(1);
	waitForFlagSet();
	sendAck(0);
	
	stop();
	return (read()<<8)|(read());
}

uint8_t readHumid(bool hold){
	
	start();
	sendAddress(I2CADR,0);
	if(hold){
		sendCommand(SI_7021_HUMD_HOLD_CMD);
		_delay_us(RH_12BIT_CONV_TIME);
	}
	
	else{
		sendCommand(SI_7021_HUMD_NO_HOLD_CMD);
		_delay_ms(RH_12BIT_CONV_TIME);
		start();
		sendAddress(I2CADR,1);
		
	}
	if(!checkStatus(0x50)){  //if data and ACK not received, return error
		return ERR;
	}
	
	
	sendAck(1);
	waitForFlagSet();
	sendAck(0);
	

	
	stop();
	return (read()<<8)|(read());
	
	
	
}

void heater(bool h){
	uint8_t curVal=readRegVal(SI7021_READRHT_REG_CMD);
	if(h){
		curVal|=(1<<SI7021_REG_HTRE_BIT);
	}
	else{
		curVal&=~(1<<(SI7021_REG_HTRE_BIT));
	}
	writeToReg(SI7021_WRITERHT_REG_CMD,curVal);
	
}
void setHeatLevel(uint8_t level){ //levels are between 0 to 15 with linear relationship between 3.09 to 94.20 mA
	writeToReg(SI7021_WRITEHEATER_REG_CMD,level);
}

uint8_t getHeatLevel(){
	return(readRegVal(SI7021_READHEATER_REG_CMD));
}

void writeToReg(uint8_t cmd,uint8_t value){
	start();
	sendAddress(I2CADR,0);
    sendCommand(cmd);
	sendCommand(value);
	waitForFlagSet();
	stop();	
}

uint8_t readRegVal(uint8_t cmd){
	start();
	sendCommand(cmd);
	start();
	sendAddress(I2CADR,1);
	stop();
	return(read());
}

int main(){
	

	
	
}




