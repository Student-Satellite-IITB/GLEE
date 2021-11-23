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

void FIFO_init(){
	
	write_reg(CTRL_REG9, 0x02);			//FIFO Memory enable
	write_reg(FIFO_CTRL,0x3F);			//FIFO Mode on, FIFO_CTRL=00111111
}

void Cont_init(){
	
	write_reg(CTRL_REG9, 0x02);			//FIFO Memory enable
	write_reg(FIFO_CTRL,0xDF);			//Continuous Mode on, FIFO_CTRL=11011111
}

uint8_t acc_data_available(){
	
	uint8_t status = read_reg(STATUS_REG1);
	
	if(status&(1<<0)) return 1;			//Returns 1 if new data available, else returns 0
	else return 0;
}

void configure_interrupt(){
	
	write_reg(INT1_CTRL, 0x08);			//generates interrupt when 32 unread samples in FIFO, INT1_FTH=1
}

uint8_t FIFO_full(){
	
	uint8_t status = read_reg(FIFO_SRC);
	
	if(status==0xE0) return 1;
	else return 0;
	
}

void read_acc(){
	
	Ax=(read_reg(OUT_X_H_XL)<<8)|(read_reg(OUT_X_L_XL));
	Ay=(read_reg(OUT_Y_H_XL)<<8)|(read_reg(OUT_Y_L_XL));
	Az=(read_reg(OUT_Z_H_XL)<<8)|(read_reg(OUT_Z_L_XL));
}

void read_FIFO_buffer(){
	
	if(FIFO_full){
		for(int i=0;i<32;i++){
			read_acc(); 						//Acc data gets stored in Ax, Ay, Az
			_delay_ms(100);						//Rate of reading data from FIFO to be decided
		}
	}
}
