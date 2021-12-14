/*
 * main.c
 *
 * Created: 11/23/2021 5:01:29 PM
 *  Author: advai
 */ 

#include <xc.h>
#include <avr/io.h>
#define F_CPU 8000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <util/delay.h>

void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned int)(ubrr>>8);
	UBRR0L = (unsigned int)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	UCSR0C = (0<<USBS) | (3<<UCSZ0);
}
void transmit(unsigned char data)
{
	while( !(UCSR0A & (1<<UDRE))){
		;
	}
	UDR0 = data;
}

unsigned char receive()
{
	while( !(UCSR0A & (1<<RXC))){
		;
	}
	return UDR0;
}

int main(void)
{
    USART_Init(MYUBRR);
	while(1){
	unsigned char msg = receive();
	msg = msg-32;
	transmit(msg);}
}



