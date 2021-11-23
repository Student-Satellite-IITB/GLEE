#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "I2C.c"
#include "LSM9DS1.c"

void configure_ext_interrupt(){
	EIMSK|=(1<<INT0);						//Enable INT0
	EICRA|=(1<<ISC00)|(1<<ISC01);					//Configure INT0 as rising edge triggered
		
	sei();								//Global interrupt enable
}

ISR(INT0_vect){
	
	for(int i=0;i<32;i++){
		read_acc(); 						//Acc data gets stored in Ax, Ay, Az
		_delay_ms(100);						//Rate of reading data from FIFO to be decided; should be > ODR for no overwrite
	}	

}


int main(void)
{
	uint8_t data_available= acc_data_available();
	
	acc_init();							//Initialize Accelerometer
	//Cont_init();
	
	//configure_ext_interrupt();
	//configure_interrupt();					//Enable interrupt generation when FIFO is full (32 unread samples)
	
	while(1){
		
		if(data_available) {
		   read_acc(); 						//Acc data gets stored in Ax, Ay, Az
	   	}
	}
	
}

