
#include <avr/io.h>
#include "I2C.h"

void TWI_init() {
	TWDR=0;
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
void TWI_SLA_W(uint8_t sla_w) {
	TWDR = sla_w;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

void TWI_transmit(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

uint8_t TWI_receive(bool isLast) {
	uint8_t received_data;
	if(!isLast) {
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
