/*
 * SX1272_Functions.h
 *
 * Created: 28-12-2021 12:05:23
 *  Author: Adithya Raj Mishra
 */ 


#ifndef SX1272_FUNCTIONS_H_
#define SX1272_FUNCTIONS_H_
#define INITREGSIZE 0x0A
#define SINGLEMODE 0x01

void writeRegister(uint8_t address,uint8_t *data,int size);
uint8_t readRegister(uint8_t address,uint8_t *data,int size);
void initTransceiver(void);
void transmit(uint8_t data);




#endif /* SX1272_FUNCTIONS_H_ */