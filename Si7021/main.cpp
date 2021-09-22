/*
 * SensorLibrary.cpp
 *
 * Created: 01-09-2021 23:11:20
 * Author : Adithya Raj Mishra
 */ 

#include <avr/io.h>
#include "GLEE_Si7021.h"
#include "TWI.h"



Si7021::Si7021(){
	i2cAdr=SI_7021_I2C_ADDRESS;
	
}
void Si7021::reset(){
	TWI::start();
	TWI::sendAddress(i2cAdr,0);
	TWI::sendCommand(0xFE);
	TWI::stop();
	_delay_ms(50);
}
int Si7021::readTemp(bool hold){//hold decides the mode of reading temp
	int resultMS,resultLS;
	TWI::start();
	TWI::sendAddress(i2cAdr,0);
	if(hold){
		TWI::sendCommand(0xF3);
	}
	else{
		TWI::sendCommand(0xE3);
	}
	TWI::start();
	TWI::sendAddress(i2cAdr,1);
	resultMS=TWI::read();
	TWI::waitForFlagSet(1);
	resultLS=TWI::read();
	TWI::stop();
	return (resultMS<<8)|(resultLS);
}

int Si7021::readHumid(bool hold){
	int resultLS,resultMS;
	TWI::start();
	TWI::sendAddress(i2cAdr,0);
	TWI::sendCommand(0xF5);
	_delay_ms(13);
	if(TWI::checkStatus()){
		return -1;
	}
	
	TWI::start();
	TWI::sendAddress(i2cAdr,1);
	
	TWI::stop();
	return (TWI::read()<<8)|(TWI::read());
	
	
	
}

void Si7021::heater(bool h){
	uint8_t curVal=readRegVal(SI7021_READRHT_REG_CMD);
	if(h){
		curVal|=(1<<SI7021_REG_HTRE_BIT);
	}
	else{
		curVal&=~(1<<(SI7021_REG_HTRE_BIT));
	}
	writeToReg(SI7021_WRITERHT_REG_CMD);
	
}
void Si7021::setHeatLevel(uint8_t level){ //levels are between 0 to 15 with linear relationship between 3.09 to 94.20 mA
	writeToReg(SI7021_WRITEHEATER_REG_CMD,level);
}

int Si7021::getHeatLevel(){
	return(readRegVal(SI7021_READHEATER_REG_CMD));
}

void Si7021::writeToReg(uint8_t cmd,uint8_t value){
	TWI::start();
	TWI::sendAddress(i2cAdr,0);
	TWI::sendCommand(cmd);
	TWI::sendCommand(value);
	TWI::waitForFlagSet(true);
	TWI::stop();	
}

int Si7021::readRegVal(int cmd){
	TWI::start();
	TWI::sendCommand(cmd);
	TWI::start();
	TWI::sendAddress(i2cAdr,1);
	TWI::stop();
	return(TWI::read());
}

int main(){
	
}




