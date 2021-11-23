/*
 * Si7021_v1.c
 *
 * Created: 25-08-2021 23:01:38
 * Author : Akshat
 */ 

// Written for Atmega128 - Si7021
#include <avr/io.h>
#include "Si7021.h"
#include "I2C.h"

#define FOSC 16000000 // 16MHz Clock frequency
#define BAUD 9600
#define BAUD_REGISTER FOSC/16/BAUD - 1

//setup
void UART_init(unsigned int baud_reg) {
	// setting up baud rate
	UBRR0H = (baud_reg >> 8);
	UBRR0L = baud_reg;
	
	//enabling RX TX
	UCSR0B = (1<<RXEN)|(1<<TXEN);
	
	//Frame size is by default set to 8 bit (UCSZ=011) and 1 stop bit (USBS=0)
}

//receiver function
unsigned char UART_receive(void) {
	//wait for the data reception to complete
	while(!(UCSR0A & (1<<RXC)));
	
	//return the data
	return UDR0;
}

//transmitter function
void UART_transmit(unsigned char data){
	//wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE)));
	
	//store the data in UDR (buffer)
	UDR0 = data;
}

int main(void)
{
	UART_init(BAUD_REGISTER);
	
    TWI_init();
	uint8_t rev = readFirmRev();
	
	UART_transmit(rev);
}
