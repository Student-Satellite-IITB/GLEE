#ifndef _I2C_
#define _I2C_

#define SCL_CLK 100000L
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

//status codes
#define START 0x08
#define REPEATED_START 0x10
#define MT_SLA_ACK 0x18
#define MT_SLA_NACK 0x20
#define MT_DATA_ACK 0x28
#define MT_DATA_NACK 0x30
#define MR_SLA_ACK 0x40
#define MR_SLA_NACK 0x38


//function definitions
void I2C_Init();
uint8_t I2C_Start(char write_address);
uint8_t I2C_Repeated_Start(char read_address);
void I2C_Stop();
void I2C_Start_Wait(char write_address);
uint8_t I2C_Write(char data);
char I2C_Read_Ack();
char I2C_Read_Nack();
uint8_t configure_acc(char SLA, char SUB);
#endif