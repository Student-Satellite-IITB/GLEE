
/*
* Transceiver SX1272 interfacing code.c
*
* Created: 13-12-2021 16:38:11
* Author : VATSAL
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SPI.c"



int main(void)
{
	/* Replace with your application code */
	unsigned char address = 0x00, data = 0x00;
	spiDataSend(address, data);
	while (1)
	{
	}
}