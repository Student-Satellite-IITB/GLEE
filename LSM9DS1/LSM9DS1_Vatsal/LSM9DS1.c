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



//new gyro part
void gyro_init(){
	
	write_reg(CTRL_REG1_G, 0x20);		// Output Data Rate=14.9Hz, full scale deflection = 245dps, bandwidth selection = n.a.
	write_reg(CTRL_REG4, 0x38);			// Enable output of Yaw axis(z), Roll axis(y), Pitch axis(x)
}

void read_gyro(){
	
	Gx = (uint16_t) ((uint16_t)read_reg(OUT_X_H_G)<<8) | (read_reg(OUT_X_L_G));
	Gy = (uint16_t) ((uint16_t)read_reg(OUT_Y_H_G)<<8) | (read_reg(OUT_Y_L_G));
	Gz = (uint16_t) ((uint16_t)read_reg(OUT_Z_H_G)<<8) | (read_reg(OUT_Z_L_G));
}

uint8_t gyro_data_available(){
	
	uint8_t status = read_reg(STATUS_REG1);
	
	if(status&(1<<1)) return 1;			//Returns 1 if new data available, else returns 0
	else return 0;
}



// new different modes part
void reset_FIFO_mode(){
	
	write_reg(FIFO_CTRL, 0x00);				// setting bypass mode
	write_reg(FIFO_CTRL, 0x21);				// reset the FIFO mode
}

void FIFO_mode(){
	
	acc_init();
	write_reg(FIFO_CTRL, 0x21);								// Set FIFO mode, threshold level 1
	write_reg(CTRL_REG9, 0x03);								// Enable FIFO memory, Stop on FIFO threshold
	_delay_ms(100);
	if(read_reg(FIFO_SRC) & (1<<7)){						// check if no. of unread samples exceeds threshold value
		int samples = read_reg(FIFO_SRC) & 0b00111111;		// no. of unread samples
		for (int i = 0; i < samples; i++)
		{
			read_acc();
		}
	}
}

void continuous_mode(){
	
	acc_init();
	write_reg(FIFO_CTRL, 0xDF);								// Set continuous mode, threshold level 31
	// ??
	
}

void contin_to_FIFO_mode(){
	
	write_reg(FIFO_CTRL, 0x7F);								// Set continuous to FIFO mode, threshold level 31
	
	write_reg(INT_GEN_SRC_XL, 0b40);						// FIFO in FIFO mode - 1
	write_reg(INT_GEN_SRC_XL, 0x00);						// FIFO in Continuous mode - 0
}


void bypass_to_contin_mode(){
	
	write_reg(FIFO_CTRL, 0x9F);								// Set continuous to FIFO mode, threshold level 31
	
	write_reg(INT_GEN_SRC_XL, 0b40);						// FIFO in Continuous mode - 1
	write_reg(INT_GEN_SRC_XL, 0x00);						// FIFO in Bypass mode - 0
}



//new magneto part
void magneto_init(){
	
	// default - write_reg(CTRL_REG1_M, 0x10);				// Low power mode for x,y axes, ODR = 10Hz
	// default - write_reg(CTRL_REG2_M, 0x00);				// full scale deflection = 4 gauss
	write_reg(CTRL_REG3_M, 0x81);							// Enable I2C, SPI only write enabled, Single Conversion operating mode 
}

void read_gyro(){
	
	Mx = (uint16_t) ((uint16_t)read_reg(OUT_X_H_M)<<8) | (read_reg(OUT_X_L_M));
	My = (uint16_t) ((uint16_t)read_reg(OUT_Y_H_M)<<8) | (read_reg(OUT_Y_L_M));
	Mz = (uint16_t) ((uint16_t)read_reg(OUT_Z_H_M)<<8) | (read_reg(OUT_Z_L_M));
}

uint8_t gyro_data_available(){
	
	uint8_t status = read_reg(STATUS_REG_M);
	
	if(status&(1<<3)) return 1;			//Returns 1 if new data available in x,y,z axis, else returns 0
	else return 0;
}
