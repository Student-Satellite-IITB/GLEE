#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "I2C.c"
#include "LSM9DS1.c"

int main(void)
{
   uint8_t data_available= acc_data_available();
  /*uint8_t data_available= acc_data_available_FIFO();*/                //Incase FIFO Mode is used
   
	
   					
   acc_init();								//Initialize Accelerometer
   /*FIFO_init()*/
   
   while(1){
	   
	   if(data_available) {
		   /* for(int i=0;i<32;i++){*/
		   read_acc(); 						//Acc data gets stored in Ax, Ay, Az
		   _delay_ms(100);
		  /* }*/
	   }
   }
   
}

