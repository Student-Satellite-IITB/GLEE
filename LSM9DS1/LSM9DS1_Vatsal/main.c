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
	
	acc_init();								//Initialize Accelerometer
	
	while(1){
		
		if(data_available) {
			read_acc(); 						//Acc data gets stored in Ax, Ay, Az
		}
	}
	
}
