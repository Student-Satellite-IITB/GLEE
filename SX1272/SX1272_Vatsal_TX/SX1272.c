/*
* Sx1272_Transceiver_code.c
*
* Created: 28-12-2021 12:04:07
* Author :  ADITHYA and VATSAL
*/

#include <avr/io.h>
#include "SX1272.h"
#include "SPI.h"


void sx1272Init(){																	//initialize transceiver with optimum register values
	uint8_t settingsLength = sizeof(sx1272InitSettings)/sizeof(registerSettings);
	for(int i=0; i<settingsLength; i++){
		writeRegister(sx1272InitSettings[i].registerAddress, sx1272InitSettings[i].registerValue, SINGLE_MODE);
	}
}

void writeRegister(uint8_t address,uint8_t data, uint8_t size){								//address of register to write, data to write, size of data
	spiMastInit();
	spiMastTrans(address);					// 1 - write, 0 - read + 7 bit address
	for(int i=0; i<size; i++){
		spiMastTrans(data[i]);
	}
	stopSPI();
}

void readRegister(uint8_t address, uint8_t size, uint8_t start = 0){		//address of register to read from, size of data to be read, the i'th data reading foe index
	// int receivedData[size];
	spiMastInit();
	spiMastTrans(address);					// 1 - write, 0 - read + 7 bit address
	for(int i=start;i<size+start;i++){
		receivedData[i] = spiMastRec();
	}
	stopSPI();
	// return receivedData;
}

void sendTxFIFO(uint8_t data[]){
	
	for(int i = 0; i<4; i++){														// Initial TX settings
		writeRegister(registerTxSettings[i].registerAddress, registerTxSettings[i].registerValue, SINGLE_MODE);
	}
	
	for(int i = 0; i<10; i++){						//Sending sample data to FIFO data register
		writeRegister(0x80, data[i], SINGLE_MODE);
	}
	
	writeRegister(registerTxSettings[4].registerAddress, registerTxSettings[4].registerValue, SINGLE_MODE);		//Turn on TX mode
	
	while((receivedData[0] & 0x08) != 1){						//Check if TX is done or not
		readRegister(0x12, SINGLE_MODE);
	}
	
}




