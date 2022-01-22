/*
 * Transceiver SX1272 RX code.c
 *
 * Created: 14-01-2022 21:59:05
 * Author : VATSAL
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SPI.c"
#include "SX1272.h"


int main(void)
{
	spiMastInit();		//initialize master SPI mode
	
	sei();				//enable global interrupts
	
	sx1272Init();		//initialize transceiver
	
	//testing data
	//uint8_t testData[6] = [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A];
	
	getRxFIFO();		//receive the data and store it on variable
	
	DDRD = 0xFF;		//Register D as output
	
	for(int i = 0; i<10; i++){		//display the received values on pins of PORT D
		PORTD = receivedData[i];
		_delay_ms(500);
	}
	
	while (1) {}
	return 0;
}

