/*
 * Si7021_v1.c
 *
 * Author : Akshat
 */ 

// Written for Atmega128 - Si7021
#include <avr/io.h>

// Register mapping
#define SI7021_ADDRESS 0x40
#define SI7021_TEMP_HOLD_CMD 0xE3
#define SI7021_TEMP_NOHOLD_CMD 0xF3


//TWI functions (to be modified) ---------------------------------------------
void TWI_Master_init() {
	//CPU Clock = 8MHz, SCL Freq = 50kHz (need to alter this*)
	TWBR = 0x47; //Bit rate
	TWSR = (0<<TWPS0) | (0<<TWPS1); //Prescalar
	TWCR = (1<<TWEN); //TWI enable
}

void TWI_start() {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //send start condition
	while(!(TWCR & (1<<TWINT))); //wait for TWINT to set
}

//add status codes
void TWI_Repeated_Start() {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

//Slave Address and W/R
void TWI_SLA_W(unsigned char sla_w) {
	TWDR = sla_w;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

void TWI_Master_transmit(unsigned char data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

unsigned char TWI_Master_receive(unsigned char isLast) {
	unsigned char received_data;
	if(isLast == 0) {
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	}
	else {
		TWCR = (1<<TWINT)|(1<<TWEN);
	}
	
	while(!(TWCR & (1<<TWINT)));
	received_data = TWDR;
	//PORTA = received_data;
	return received_data;
}

void TWI_stop() {
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

int main(void)
{
    TWI_Master_init();
    
    TWI_start();
	TWI_SLA_W(SI7021_ADDRESS + 0x01);            //Sensor address + Write bit
    TWI_Master_transmit(SI7021_TEMP_NOHOLD_CMD); //Command for reading temperature in no hold mode
    
	TWI_Repeated_Start();
    TWI_SLA_W(SI7021_ADDRESS + 0x00);            //Sensor address + Read bit 
    unsigned char msb = TWI_Master_receive(0);   // MSB
	unsigned char lsb = TWI_Master_receive(1);   // LSB
    TWI_stop();    
}
