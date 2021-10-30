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
	
	acc_init();							//Initialize Accelerometer
	//FIFO_init();
	Cont_init();							//Initialize continuous mode for FIFO buffer
	
	while(1){
		
		read_FIFO_buffer();
	}
	
}

