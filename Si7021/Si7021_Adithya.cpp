/*
 * Si7021Code.cpp
 *
 * Created: 18-08-2021 22:33:30
 * Author : Adithya Raj Mishra
 */ 

#include <avr/io.h>
void waitForFlagSet(bool ack){
	TWCR|=1<<TWINT|1<<TWEA;
	while(!(TWCR &&(1<<TWINT)));
	
}
//if rw=1, read mode; rw=0,write mode

void sendAddress(bool rw){
	TWDR=0b10000000<<rw;
	waitForFlagSet(true);
}
void i2cinit(int rate){
	TWCR=1<<TWEN;
	TWBR=rate;
}

void start(){
	TWCR|=1<<TWSTA;
	waitForFlagSet(true);
}
void stop(){
	TWCR|=1<<TWSTO|1<<TWINT;
	
}
void sendCommand(int command){
	TWDR=command;
	waitForFlagSet(true);
}

void reset(){
	start();
	sendAddress(0);
	sendCommand(0xFE);
	stop();
}

int readTemp(bool hold){
	int result;
	start();
	sendAddress(0);
	if(hold){
		sendCommand(0xF3);
	}
	else{
		sendCommand(0xE3);
	}
	start();
	sendAddress(1);
	result=TWDR;
	stop();
	return result;
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

