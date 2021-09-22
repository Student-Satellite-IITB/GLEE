#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "LSM9DS1.h"
#include "I2C.h"

uint8_t read_reg(uint8_t address){
	uint8_t temp;
	I2C_Init();
	configure_acc(SADW,address);
	I2C_Repeated_Start(SADR);
	temp=I2C_Read_Ack;
	I2C_Stop();
	return temp;
	
}

void write_reg(uint8_t address, uint8_t value){
	I2C_Init();
	configure_acc(SADW,address);
	I2C_Write(value);
	I2C_Stop();
}

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
	
	Ax = (uint16_t) ((uint16_t)read_reg(OUT_X_H_XL)<<8) | (read_reg(OUT_X_L_XL));
	Ay = (uint16_t) ((uint16_t)read_reg(OUT_Y_H_XL)<<8) | (read_reg(OUT_Y_L_XL));
	Az = (uint16_t) ((uint16_t)read_reg(OUT_Z_H_XL)<<8) | (read_reg(OUT_Z_L_XL));
}

// new part
void FIFO_setup(){
	
	acc_init();
	write_reg(FIFO_CTRL, 0x21);								// Set FIFO mode, threshold level 1
	write_reg(CTRL_REG9, 0x02);								// Enable FIFO memory
	_delay_ms(100);
	if(read_reg(FIFO_SRC) & (1<<7)){						// check if no. of unread samples exceeds threshold value
		int samples = read_reg(FIFO_SRC) & 0b00111111;		// no. of unread samples
		for (int i = 0; i < samples; i++)
		{
			read_acc();
		}
	}
}