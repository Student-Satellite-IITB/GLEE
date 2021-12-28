/*
* Sx1272_Transceiver_code.c
*
* Created: 28-12-2021 12:04:07
* Author :  ADITHYA and VATSAL
*/

#include <avr/io.h>
#include "SX1272.h"
#include "SPI.h"

//assuming the size of optimumValues to be 10
//if size=1, single access, else burst/FIFO access

void sx1272Init(){
	uint8_t settingslength = sizeof(optimumValues)/sizeof(registerSettings);
	for(int i=0; i<settingslength; i++){
		writeRegister(optimumValues[i].regaddr,optimumValues[i].regvalue, SINGLEMODE);
	}
}

void writeRegister(uint8_t address,uint8_t data,int size){
	spiMastInit();
	spiMastTrans(address);					// 1 - write, 0 - read + 7 bit address
	for(int i=0; i<size; i++){
		spiMastTrans(data[i]);
	}
	stopSPI();
}

void readRegister(uint8_t address, int size){
	// int receivedData[size];
	spiMastInit();
	spiMastTrans(address);					// 1 - write, 0 - read + 7 bit address
	for(int i=0;i<size;i++){
		receivedData[i] = spiMastRec();
	}
	stopSPI();
	// return receivedData;
}

void transmit(uint8_t data){
	
}




