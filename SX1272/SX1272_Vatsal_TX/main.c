
/*
* Transceiver SX1272 interfacing code.c
*
* Created: 13-12-2021 16:38:11
* Author : VATSAL and ADITHYA
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SPI.c"
#include "SX1272.h"


int main(void)
{
	spiMastInit();
	
	sei();
	
	sx1272Init();		
	
	//testing data
	uint8_t testData[6] = [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A];
	
	//FIFO transmit
	sendTXFIFO(testData);
	
	while (1) {}
	return 0;
}