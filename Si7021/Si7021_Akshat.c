/*
 * Si7021_v1.c
 *
 * Created: 25-08-2021 23:01:38
 * Author : Akshat
 */ 

// Written for Atmega128 - Si7021
#include <avr/io.h>

// Command description
#define SI7021_ADDRESS           0x40                         // Slave (Si7021) Address
#define SI7021_MSR_RH_HOLD       0xE5                         // Measure RH, Hold master mode
#define SI7021_MSR_RH_NO_HOLD    0xF5                         // Measure RH, No hold master mode
#define SI7021_MSR_TEMP_HOLD     0xE3                         // Measure Temperature, Hold master mode
#define SI7021_MSR_TEMP_NO_HOLD  0xF3                         // Measure Temperature, No hold master mode
#define SI7021_READ_TEMP_PREV_RH 0xE0                         // Read temperature from previous RH measurement
#define SI7021_RESET             0xFE                         // Reset the sensor
#define SI7021_WRITE_RHT_UR1     0xE6                         // Write to RH/T to user register 1
#define SI7021_READ_RHT_UR1      0xE7                         // Read RH/T from user register 1
#define SI7021_WRITE_HEATER_CR   0x51                         // Write Heater Control Register
#define SI7021_READ_HEATER_CR    0x11                         // Read Heater Control Register
#define SI7021_READ_ID1          0xFA                         // Read 1st byte of electronic ID
#define SI7021_READ_ID2          0xFC                         // Read 2nd byte of electronic ID
#define SI7021_READ_FIRM_REV     0x84                         // Read firmware revision version

// Sensor related read write functions---------------------------------------
uint8_t readElecID();                                         // To read electronic ID (pending)
uint8_t measure();                                            // To make measurement (pending)
uint8_t getRH();                                              // To read Relative Humidity value (pending)
uint8_t getTemperature();                                     // To read Temperature value (pending)
void reset();                                                 // To reset the sensor (pending)
void enableHeater(bool h);                                    // To enable (h=1) or disable (h=0) heater (pending)
void heaterLevel();                                           // To set heater level (pending)


//TWI functions (to be modified) ---------------------------------------------
void TWI_Master_init();
void TWI_start();
void TWI_Repeated_Start();
void TWI_SLA_W(unsigned char sla_w);
void TWI_Master_transmit(unsigned char data);
unsigned char TWI_Master_receive(unsigned char isLast);
void TWI_stop();
//-----------------TWI done----------------------------

int main(void)
{
    TWI_Master_init();
    
    TWI_start();
	TWI_SLA_W(SI7021_ADDRESS + 0x01);            //Sensor address + Write bit
    TWI_Master_transmit(SI7021_MSR_TEMP_NO_HOLD); //Command for reading temperature in no hold mode
    
	TWI_Repeated_Start();
    TWI_SLA_W(SI7021_ADDRESS + 0x00);            //Sensor address + Read bit 
    unsigned char msb = TWI_Master_receive(0);   // MSB
	unsigned char lsb = TWI_Master_receive(1);   // LSB
    TWI_stop();
}

// Sensor functions
uint8_t measurement(uint8_t cmd) {
	
}

//TWI functions (to be modified) ---------------------------------------------
void TWI_Master_init() {
	//CPU Clock = 8MHz, SCL Freq = 50kHz (need to alter this*)
	TWBR = 0x47; //Bit rate
	TWSR = (0<<TWPS0) | (0<<TWPS1); //Prescalar
	TWCR = (1<<TWEN); //TWI enable
}

void TWI_start() {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //send start condition
	while(!(TWCR & (1<<TWINT))); //wait for TWINT to set
}

//add status codes
void TWI_Repeated_Start() {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

//Slave Address and W/R
void TWI_SLA_W(uint8_t sla_w) {
	TWDR = sla_w;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

void TWI_Master_transmit(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

unsigned char TWI_Master_receive(uint8_t isLast) {
	uint8_t received_data;
	if(isLast == 0) {
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	}
	else {
		TWCR = (1<<TWINT)|(1<<TWEN);
	}
	
	while(!(TWCR & (1<<TWINT)));
	received_data = TWDR;
	//PORTA = received_data;
	return received_data;
}

void TWI_stop() {
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
