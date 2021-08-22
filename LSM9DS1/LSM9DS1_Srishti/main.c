#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "I2C.c"
#include "LSM9DS1.h"

int main(void)
{
   char sensor_data;
   
   I2C_Init();								//Initialize I2C 
   char reg_addr = 0x6B;			        //8 bit sub-address
   configure_acc(SADW,reg_addr);			
   
   while(1)
   {
	   I2C_Repeated_Start(SADR);
	   sensor_data=I2C_Read_Ack();
   }
   
   I2C_Stop();
   
   
}

