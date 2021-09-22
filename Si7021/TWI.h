/*
 * TWI.h
 *
 * Created: 04-09-2021 16:00:47
 *  Author: Adithya Raj Mishra
 */ 


#ifndef TWI_H_
#define TWI_H_

class TWI{
	public:
	TWI(int rate);
	void sendCommand(int command);
	void stop();
	void start();
	void sendAddress(int address,bool rw);
	void waitForFlagSet(bool ack);
	void i2cinit(int rate);
	int checkStatus(int statCode);
	int read();
	};




#endif /* TWI_H_ */