/*
* SPI.h
*
* Created: 13-12-2021 17:11:35
*  Author: VATSAL and ADITHYA
*/


#ifndef SPI_H_
#define SPI_H_

void spiMastInit(void);
void spiMastTrans(unsigned char data);
unsigned char spiMastRec(void);
void stopSPI(void);


#endif /* SPI_H_ */