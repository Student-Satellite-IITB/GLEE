/*
 * Sx1272_Transceiver_code.c
 *
 * Created: 28-12-2021 12:04:07
 * Author : Adithya Raj Mishra
 */ 

#include <avr/io.h>
#include "SX1272.h"
#include "SPI.h"
#include "SX1272_Functions.h"

//assuming the size of optimumValues to be 10
//if size=1, single access, else burst/fifo access

void writeRegister(uint8_t address,uint8_t *data,int size){ 
	if(size<1){
		return;
	}
	enableSPI();
	spiMastInit();
	spiMastTrans(address);		// 1 - write, 0 - read + 7 bit address
	for(int i=0;i<size;i++){
		spiMastTrans(data[i]);
	}
	stopSPI();
}

int* readRegister(uint8_t address,uint8_t *data,int size){
	if(size<1){
		return;
	}
	int* receivedData;
	enableSPI();
	spiMastInit();
	spiMastTrans(address);		// 1 - write, 0 - read + 7 bit address
	for(int i=0;i<size;i++){
		receivedData[i]=spiMastRec()	;
	}
	stopSPI();
	return receivedData;
}

void initTransceiver(void){
	for(int i=0;i<INITREGSIZE;i++){
		writeRegister(optimumValues[i].regaddr,optimumValues[i].regvalue,SINGLEMODE);
	}
}
//payload sent 1 byte for now
void transmit(uint8_t data){
	//changing mode to stand-by
	changeMode(STDBY);
	writeRegister(RegFifoAddrPtr,RegFifoTxBaseAddr);
	//Tx init
	PORTB|=1<<PORTB0;  //assuming RX-TX pin connected to pb0
	
	writeRegister(RegPayloadLength,1);
	//writing data to fifo
	writeRegister(RegFifoTxBaseAddr,data);
}



