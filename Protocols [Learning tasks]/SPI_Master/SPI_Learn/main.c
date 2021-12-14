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

void SPI_MasterInit(void)
{
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
		;
}

int main(void)
{
	USART_Init(MYUBRR);
	SPI_MasterInit();
	unsigned char msg;
	while(1){
		msg = receive();
		
		SPI_MasterTransmit(msg);
		transmit(SPDR);
	}
}


