#include <avr/io.h>							
#include <util/delay.h>						
#include <string.h>							
#include <math.h>						    
#include <stdio.h>
#include "I2C.h"


void I2C_Init()												
{
	TWBR = BITRATE(TWSR = 0x00);							/*Get bit rate register value by formula*/
}


uint8_t I2C_Start(char write_address)						/* I2C start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != START)								    /* Check whether start condition transmitted successfully or not */
		return 0;												/* If not then return 0 to indicate start condition fail */
	TWDR = write_address;									/* If yes then write SLA+W in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == MT_SLA_ACK)							    /* Check whether SLA+W transmitted & ACK received or not? */
		return 1;												/* If yes then return 1 to indicate ACK received i.e. ready to accept data byte */
	if (status == MT_SLA_NACK)								/* Check whether SLA+W transmitted & NACK received or not? */
		return 2;												/* If yes then return 2 to indicate NACK received i.e. device is busy */
	else
		return 3;												/* Else return 3 to indicate SLA+W failed */
}

uint8_t I2C_Repeated_Start(char read_address)				/* I2C repeated start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != REPEATED_START)							/* Check whether repeated start condition transmitted successfully or not? */
		return 0;												/* If no then return 0 to indicate repeated start condition fail */
	TWDR = read_address;									/* If yes then write SLA+R in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == MR_SLA_ACK)								/* Check whether SLA+R transmitted & ack received or not? */
		return 1;												/* If yes then return 1 to indicate ack received */
	if (status == MR_SLA_NACK)								/* Check whether SLA+R transmitted & nack received or not? */
		return 2;												/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
		return 3;												/* Else return 3 to indicate SLA+W failed */
}

void I2C_Stop()												/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Enable TWI, generate stop condition and clear interrupt flag */
	while(!(TWCR & (1<<TWSTO)));								/* Wait until stop condition execution */
}

void I2C_Start_Wait(char write_address)						/* I2C start wait function */
{
	uint8_t status;											/* Declare variable */
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				/* Enable TWI, generate start condition and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (start condition) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != START)									/* Check whether start condition transmitted successfully or not? */
			continue;											/* If no then continue with start loop again */
		TWDR = write_address;								/* If yes then write SLA+W in TWI data register */
		TWCR = (1<<TWEN)|(1<<TWINT);						/* Enable TWI and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != 0x18 )								/* Check whether SLA+W transmitted & ack received or not? */
		{
			I2C_Stop();										/* If not then generate stop condition */
			continue;										/* continue with start loop again */
		}
		break;												/* If yes then break loop */
	}
}

uint8_t I2C_Write(char data)								/* I2C write function */
{
	uint8_t status;											/* Declare variable */
	TWDR = data;											/* Copy data in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == MT_DATA_ACK)								/* Check whether data transmitted & ACK received or not? */
		return 0;												/* If yes then return 0 to indicate ACK received */
	if (status == MT_DATA_NACK)								/* Check whether data transmitted & NACK received or not? */
		return 1;												/* If yes then return 1 to indicate NACK received */
	else
		return 2;												/* Else return 2 to indicate data transmission failed */
}

char I2C_Read_Ack()											/* I2C read ACK function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Enable TWI, generation of ACK and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

char I2C_Read_Nack()										/* I2C read NACK function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);								/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

uint8_t configure_acc(char SLA, char SUB){
	
	uint8_t start = I2C_Start(SLA);
	if(start == 1)											/* Start I2C */
	{
		TWDR = SUB;										        /* If yes then write SUB in TWI data register */
		TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
		if (status == MT_SLA_ACK)							    /* Check whether SUB transmitted & ACK received or not? */
			return 4;											    /* If yes then return 4 to indicate SUB successfully transmitted*/
		else if (status == MT_SLA_NACK)						/* Check whether SUB transmitted & NACK received or not? */
			return 5;												/* If yes then return 5 to indicate NACK received i.e. device is busy */
		else
			return 6;										    /* Transmission failed*/
	}
	
	return start;										/* Start Condition failed */
}

