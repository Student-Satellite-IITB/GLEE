#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "LSM9DS1.h"

void acc_init(){
	
	write_reg(CTRL_REG5_XL,0x38);		//Accelerometer X,Y,Z output enable
	write_reg(CTRL_REG6_XL,0x20);		//Output Data Rate=10 Hz, full scale deflection=2g
}

uint8_t acc_data_available(){
	
	uint8_t status = read_reg(STATUS_REG1);
	
	if(status&(1<<0)) return 1;			//Returns 1 if new data available, else returns 0
	else return 0;
}

void read_acc(){
	
	Ax=(read_reg(OUT_X_H_XL)<<8)|(read_reg(OUT_X_L_XL));
	Ay=(read_reg(OUT_Y_H_XL)<<8)|(read_reg(OUT_Y_L_XL));
	Az=(read_reg(OUT_Z_H_XL)<<8)|(read_reg(OUT_Z_L_XL));
}
