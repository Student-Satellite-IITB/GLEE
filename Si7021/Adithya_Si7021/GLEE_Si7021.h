#ifndef GLEE_SI7021_H_
#define GLEE_Si7021_H_

#define ERR -1

#define I2CADR 0x40

#define SI_7021_HUMD_HOLD_CMD 0xE5
#define SI_7021_HUMD_NO_HOLD_CMD 0xF5

#define SI7021_TEMP_HOLD_CMD 0xE3
#define SI7021_TEMP_NOHOLD_CMD 0xF3

#define SI7021_PREVTEMP_CMD 0xE0


#define SI7021_RESET_CMD 0xFE

#define TEMP_14BIT_CONV_TIME 10.8

#define RH_12BIT_CONV_TIME 12

#define SI7021_WRITERHT_REG_CMD 0xE6  
#define SI7021_READRHT_REG_CMD 0xE7#define SI7021_WRITEHEATER_REG_CMD 0x51
#define SI7021_READHEATER_REG_CMD 0x11#define SI7021_REG_HTRE_BIT 0x02    


enum si_heatLevel {
	SI_HEATLEVEL_LOWEST = 0x00,
	SI_HEATLEVEL_LOW = 0x01,
	SI_HEATLEVEL_MEDIUM = 0x02,
	SI_HEATLEVEL_HIGH = 0x04,
	SI_HEATLEVEL_HIGHER = 0x08,
	SI_HEATLEVEL_HIGHEST = 0x0F,
};

void writeToReg(uint8_t cmd,uint8_t value);
uint8_t readRegVal(uint8_t cmd);
uint8_t getHeatLevel();
void setHeatLevel(uint8_t level);
void heater(bool h);
uint8_t readHumid(bool hold);
uint8_t readTemp(bool hold);
void reset();


bool checkStatus(uint8_t statCode);
uint8_t read();
void stop();
void sendCommand(uint8_t cmd);
void sendAddress(uint8_t adr,bool rw);
void start();
void sendAck(bool ack);
void waitForFlagSet();


#endif /* SI7021_H_ */