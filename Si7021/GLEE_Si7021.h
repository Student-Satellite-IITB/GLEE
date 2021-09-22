#ifndef GLEE_SI7021_H_
#define GLEE_Si7021_H_



#define SI_7021_I2C_ADDRESS 0x40

#define SI_7021_HUMD_HOLD_CMD 0xE5;
#define SI_7021_HUMD_NO_HOLD_CMD 0xF5;

#define SI7021_TEMP_HOLD_CMD 0xE3
#define SI7021_TEMP_NOHOLD_CMD 0xF3

#define SI7021_PREVTEMP_CMD 0xE0


#define SI7021_RESET_CMD 0xFE

#define TEMP_14BIT_CONV_TIME 10.8

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


class Si7021{
	public:
	Si7021();
	int readTemp(bool hold);
	int readHumid(bool hold);
	int readRegVal(int cmd);
	void reset();
	
	void heater(bool h);
	void setHeatLevel(uint8_t level);
	
	
	
	
	private:
	
	const static int _TRANSACTION_TIMEOUT = 100;
	int i2cAdr;
	
	void writeToReg(uint8_t cmd,uint8_t value);
	//Two_Wire1 the_wire;
	
	
	
};



#endif /* SI7021_H_ */