/*
* SPI.c
*
* Created: 13-12-2021 17:10:14
*  Author: VATSAL
*/

#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"


void spiDataSend(unsigned char address, unsigned char data){
	enableSPI();
	spiMastInit();
	spiMastTrans(address);		// 1 - write, 0 - read + 7 bit address
	spiMastTrans(data);
	stopSPI();
}

void spiDataReceive(unsigned char address, unsigned char *data){
	enableSPI();
	spiMastInit();
	spiMastTrans(address);		// 1 - write, 0 - read + 7 bit address
	data = spiMastRec();
	stopSPI();
}

void enableSPI(void){
	NSS = 0;			// NSS pin low to enable SPI mode
}

void spiMastInit(void){
	DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2); DDRB &= ~(1 << DDB4);	// In portB, setting MOSI, SCK and SS resp. as output, MISO disable
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);	// | (1 << SPIE);			//enable SPI,  set as master,  set SCK Fq as Fosc/16, //enable local interrupt
	// PORTB2 &= ~ (1 << DDB2); 												//enable slave select pin
}


void spiMastTrans(unsigned char data){
	//sending data
	SPDR = data;
	
	// checking last transmission is completed or not
	while(!(SPSR & (1 << SPIF)));
}


unsigned char spiMastRec(void){
	//Checking if last reception is completed or not
	while(!(SPSR & (1 << SPIF)));
	
	//returning the received data
	return SPDR;
}

void stopSPI(void){
	NSS = 1;			// NSS pin high to stop SPI mode
}

//void spiSlavInit(void){
//DDRD |= (1 << DDD6); DDRD &= ~(1 << DDD5) & ~ (1 << DDD7);				// In port B, setting MISO output, MOSI input, SCK input
//SPCR |= (1 << SPE);		// | (1 << SPIE);										//Enable SPI,	// enable local interrupt
//}


// ISR(SPI_STC_vect){rData = SPDR;}
