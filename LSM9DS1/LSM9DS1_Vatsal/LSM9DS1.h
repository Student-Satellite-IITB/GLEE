#ifndef _LSM9DS1_
#define _LSM9DS1_

//Address
#define SADW  0xD4
#define SADR  0xD5

// Accelerometer and Gyro. Registers Address
#define ACT_THS 			0x04
#define ACT_DUR 			0x05
#define INT_GEN_CFG_XL 		0x06
#define INT_GEN_THS_X_XL 	0x07
#define INT_GEN_THS_Y_XL 	0x08
#define INT_GEN_THS_Z_XL 	0x09
#define INT_GEN_DUR_XL 		0x0A
#define REFERENCE_G 		0x0B
#define INT1_CTRL 			0x0C
#define INT2_CTRL 			0x0D
#define WHO_AM_I 			0x0F
#define CTRL_REG1_G 		0x10
#define CTRL_REG2_G 		0x11
#define CTRL_REG3_G 		0x12
#define ORIENT_CFG_G 		0x13
#define INT_GEN_SRC_G 		0x14
#define OUT_TEMP_L 			0x15
#define OUT_TEMP_H 			0x16
#define STATUS_REG1 	    0x17
#define OUT_X_L_G 			0x18
#define OUT_X_H_G 			0x19
#define OUT_Y_L_G 			0x1A
#define OUT_Y_H_G 			0x1B
#define OUT_Z_L_G 			0x1C
#define OUT_Z_H_G 			0x1D
#define CTRL_REG4 			0x1E
#define CTRL_REG5_XL 		0x1F
#define CTRL_REG6_XL 		0x20
#define CTRL_REG7_XL 		0x21
#define CTRL_REG8 			0x22
#define CTRL_REG9 			0x23
#define CTRL_REG10 			0x24
#define INT_GEN_SRC_XL 		0x26
#define STATUS_REG2 		0x27
#define OUT_X_L_XL 			0x28
#define OUT_X_H_XL 			0x29
#define OUT_Y_L_XL 			0x2A
#define OUT_Y_H_XL 			0x2B
#define OUT_Z_L_XL 			0x2C
#define OUT_Z_H_XL 			0x2D
#define FIFO_CTRL 			0x2E
#define FIFO_SRC 			0x2F
#define INT_GEN_CFG_G 		0x30
#define INT_GEN_THS_XH_G 	0x31
#define INT_GEN_THS_XL_G 	0x32
#define INT_GEN_THS_YH_G 	0x33
#define INT_GEN_THS_YL_G 	0x34
#define INT_GEN_THS_ZH_G 	0x35
#define INT_GEN_THS_ZL_G 	0x36
#define INT_GEN_DUR_G 		0x37

// Magneto. Register Address
#define OFFSET_X_REG_L_M	0x05
#define OFFSET_X_REG_H_M	0x06
#define OFFSET_Y_REG_L_M	0x07
#define OFFSET_Y_REG_H_M	0x08
#define OFFSET_Z_REG_L_M	0x09
#define OFFSET_Z_REG_H_M	0x0A
#define WHO_AM_I_M			0x0F
#define CTRL_REG1_M			0x20
#define CTRL_REG2_M			0x21
#define CTRL_REG3_M			0x22
#define CTRL_REG4_M			0x23
#define CTRL_REG5_M			0x24
#define STATUS_REG_M		0x27
#define OUT_X_L_M			0x28
#define OUT_X_H_M			0x29
#define OUT_Y_L_M			0x2A
#define OUT_Y_H_M			0x2B
#define OUT_Z_L_M			0x2C
#define OUT_Z_H_M			0x2D
#define INT_CFG_M			0x30
#define INT_SRC_M			0x31
#define INT_THS_L_M			0x32
#define INT_THS_H_M			0x33

//Variables to store sensor data

//accelerometer data
uint16_t Ax, Ay, Az;

//gyroscope data
uint16_t Gx, Gy, Gz;

//magnetometer data
uint16_t Mx, My, Mz;

//Read value of a particular register
uint8_t read_reg(uint8_t address);

//Write value to a particular register
void write_reg(uint8_t address, uint8_t value);

//Initialize accelerometer, set up scale and output rate
void acc_init();

//Polls the accelerometer status register to check if data available
uint8_t acc_data_available();

//Reads accelerometer output registers, stores values in Ax, Ay, Az
void read_acc();

//Reads a specific axis of the accelerometer
uint16_t read_acc_axis();

//Converts the 16 bit accelerometer output data to g's
float convert_acc_data(uint16_t acc_data);

void gyro_init();
void read_gyro();
uint8_t gyro_data_available();
void reset_FIFO_mode();
void FIFO_mode();
void continuous_mode();
void contin_to_FIFO_mode();
void bypass_to_contin_mode();
void magneto_init();
void read_magneto();
uint8_t magneto_data_available();
void enableSensorInterrupts();


#endif