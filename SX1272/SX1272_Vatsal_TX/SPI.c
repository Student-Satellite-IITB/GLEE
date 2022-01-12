/*
* SPI.c
*
* Created: 13-12-2021 17:10:14
*  Author: VATSAL and ADITHYA
*/

#include <avr/io.h>
//#include <util/delay.h>
#include "SPI.h"


void spiMastInit(void){
	DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2); DDRB &= ~(1 << DDB4);	// In portB, setting MOSI, SCK and SS resp. as output, MISO disable
	PORTB &= ~ (1 << 2); 													//enable slave select pin PB2
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPIE);		//enable SPI,  set as master,  set SCK Fq as Fosc/16, //enable local interrupt
}


void spiMastTrans(unsigned char data){
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));											// checking last transmission is completed or not
}


unsigned char spiMastRec(void){
	while(!(SPSR & (1 << SPIF)));											//Checking if last reception is completed or not
	return SPDR;
}

void stopSPI(void){
	PORTB |= (1 << 2);														// NSS pin high to stop SPI mode
}


// ISR(SPI_STC_vect){rData = SPDR;}
