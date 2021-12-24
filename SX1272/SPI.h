/*
* SPI.h
*
* Created: 13-12-2021 17:11:35
*  Author: VATSAL
*/


#ifndef SPI_H_
#define SPI_H_

void spiDataSend(unsigned char address, unsigned char data);
void spiDataReceive(unsigned char address, unsigned char *data);
void enableSPI(void);
void spiMastInit(void);
void spiMastTrans(unsigned char data);
unsigned char spiMastRec(void);
void stopSPI(void);
// void spiSlavInit(void);


#endif /* SPI_H_ */