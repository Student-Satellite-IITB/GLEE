#include <avr/io.h>
#include <util/delay.h>
#include "UART.c"
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void UART_init(long USART_BAUDRATE)
{
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);	/* Turn on transmission and reception */
	UCSR1C |= (1 << USBS1) | (1 << UCSZ10) | (1 << UCSZ11);/* Use 8-bit char size */
	UBRR1L = BAUD_PRESCALE;			/* Load lower 8-bits of the baud rate */
	UBRR1H = (BAUD_PRESCALE >> 8);		/* Load upper 8-bits*/
}
unsigned char UART_RxChar()
{
	while ((UCSR1A & (1 << RXC1)) == 0);/* Wait till data is received */
	return(UDR1);		/* Return the byte */
}
void UART_TxChar(char ch)
{
	while (! (UCSR1A & (1<<UDRE1)));  /* Wait for empty transmit buffer */
	UDR1 = ch ;
}
