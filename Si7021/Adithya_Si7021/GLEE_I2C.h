/*
 * I2C.h
 *
 * Created: 03-09-2021 21:30:07
 *  Author: Adithya
 */ 


#ifndef I2C_H_
#define I2C_H_

void TWI_init();
void TWI_start();
void TWI_Repeated_Start();
void TWI_SLA_W(unsigned char sla_w);
void TWI_transmit(unsigned char data);
uint8_t TWI_receive(bool isLast);
void TWI_stop();


#endif /* I2C_H_ */
