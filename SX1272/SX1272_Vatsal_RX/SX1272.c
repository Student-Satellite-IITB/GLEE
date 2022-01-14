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
	uint8_t settingslength = sizeof(sx1272InitSettings)/sizeof(registerSettings);
	for(int i=0; i<settingslength; i++){
		writeRegister(sx1272InitSettings[i].regaddr, sx1272InitSettings[i].regvalue, SINGLEMODE);
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

void readRegister(uint8_t address, int size, int start = 0){
	// int receivedData[size];
	spiMastInit();
	spiMastTrans(address);					// 1 - write, 0 - read + 7 bit address
	for(int i=start;i<size+start;i++){
		receivedData[i] = spiMastRec();
	}
	stopSPI();
	// return receivedData;
}

void getRXFIFO(){
	
	for(int i = 0; i<5; i++){														// Initial RX settings
		writeRegister(RXSettings[i].regaddr, RXSettings[i].regvalue, SINGLEMODE);
	}
		
	while((receivedData[0] & 0x40) != 1){						//Check if RX is done or not
		readRegister(0x12, SINGLEMODE);
	}
	
	for(int i = 0; i<10; i++){									//Read all values and store them in an array
		readRegister(0x00, SINGLEMODE, i);
	}
}

void sendTXFIFO(uint8_t data[]){
	
	for(int i = 0; i<4; i++){														// Initial TX settings
		writeRegister(TXSettings[i].regaddr, TXSettings[i].regvalue, SINGLEMODE);
	}
	
	for(int i = 0; i<10; i++){						//Sending sample data to FIFO data register
		writeRegister(0x80, data[i], SINGLEMODE);
	}
	
	writeRegister(TXSettings[4].regaddr, TXSettings[4].regvalue, SINGLEMODE);		//Turn on TX mode
	
	while((receivedData[0] & 0x08) != 1){						//Check if TX is done or not
		readRegister(0x12, SINGLEMODE);
	}
}




