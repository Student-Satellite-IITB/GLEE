/*
* SX1272.h
*
* Created: 18-12-2021 17:57:09
*  Author: VATSAL and ADITHYA
*/


#ifndef SX1272_H_
#define SX1272_H_

// Register address

#define RegFifo					0x00		//
#define RegOpMode				0x01		//
#define RegFrMsb				0x06		//
#define RegFrMib				0x07		//
#define RegFrLsb				0x08		//
#define RegPaConfig				0x09		//
#define RegPaRamp				0x0A		//
#define RegOcp					0x0B		//
#define RegLna					0x0C		//
#define RegFifoAddrPtr			0x0D		//
#define RegFifoTxBaseAddr		0x0E		//
#define RegFifoRxBaseaddr		0x0F		//
#define RegFifoRxCurrentAddr	0x10		//
#define ReggIrqFlagsMask		0x11		//
#define RegIrqFlags				0x12		//
#define RegRxNbBytes			0x13		//
#define RegRxHeaderCntValueMsb	0x14		//
#define RegRxHeaderCntValueLsb	0x15		//
#define RegRxPacketCntValueMsb	0x16		//
#define RegRxPacketCntValueLsb	0x17		//
#define RegModemStat			0x18		//
#define RegPktSnrValue			0x19		//
#define RegPktRssiValue			0x1A		//
#define RegRssiValue			0x1B		//
#define RegHopChannel			0x1C		//
#define RegModemConfig1			0x1D		//
#define RegModemConfig2			0x1E		//
#define RegSymbTimeoutLsb		0x1F		//
#define RegPreambleMsb			0x20		//
#define RegPreambleLsb			0x21		//
#define RegPayloadLength		0x22		//
#define RegMaxPayloadLength		0x23		//
#define RegHopPeriod			0x24		//
#define RegFifoRxByteAddr		0x25		//
#define RegFeiMsb				0x28		//
#define RegFeiMid				0x29		//
#define RegFeiLsb				0x2A		//
#define RegRssiWideband			0x2C		//
#define RegDetectOptimize		0x31		//
#define RegInvertIQ				0x33		//
#define RegDetectionThreshold	0x37		//
#define RegSyncWord				0x39		//
#define RegInvertIQ2			0x3B		//
#define RegChirpFilter			0x3D		//

//initial register values
typedef struct
{
	uint8_t		regaddr;
	uint8_t		regvalue;
}registerSettings;


const registerSettings optimumValues[] =
{
	{RegFifo,					0x00},		//default value - LoRa based FIFO input/output
	{RegOpMode,					0x01},		//LoRa mode, LoRa registers, Standby mode
	{RegFrMsb,					0xE4},		//default value - MSB of RF carrier freq (23:16) i.e. 915 MHz
	{RegFrMib,					0xC0},		//default value - MIB of RF carrier freq (15:8)
	{RegFrLsb,					0x00},		//default value - LSB of RF carrier freq (7:0)
	{RegPaConfig,				0x0F},		//default value ???
	{RegPaRamp,					0x19},		//default value ???
	{RegOcp,					0x2B},		//default value ???
	{RegLna,					0x20},		//default value ???
	{RegFifoAddrPtr,			0x??},		//
	{RegFifoTxBaseAddr,			0x??},		//
	{RegFifoRxBaseaddr,			0x??},		//
	//{RegFifoRxCurrentAddr,		0x??},		//
	//{ReggIrqFlagsMask,			0x00},		//default value  - Interrupt registers
	//{RegIrqFlags,					0x00},		//default value  - Interrupt registers
	//{RegRxNbBytes,				0x??},		//
	//{RegRxHeaderCntValueMsb,		0x??},		//
	//{RegRxHeaderCntValueLsb,		0x??},		//
	//{RegRxPacketCntValueMsb,		0x00},		//default value  - Interrupt registers
	//{RegRxPacketCntValueLsb,		0x??},		//
	//{RegModemStat,				0x??},		//
	//{RegPktSnrValue,				0x??},		//
	//{RegPktRssiValue,				0x??},		//
	//{RegRssiValue,				0x??},		//
	//{RegHopChannel,				0x??},		//
	{RegModemConfig1,			0x0E},		//BW = 125kHz, CR=4/5, Implicit Header, CRC on, Data Rate..??
	{RegModemConfig2,			0x6C},		//SF = 6 = 64 chips/symbol, LNA gain - AGC loop ?, RX timeout MSB = 0..  
	//{RegSymbTimeoutLsb,			0x??},		//Not valid in RX continuous mode
	//{RegPreambleMsb,				0x??},		//Not valid in implicit header mode
	//{RegPreambleLsb,				0x??},		//Not valid in implicit header mode
	{RegPayloadLength,			0x01},		//Expected payload length ????
	{RegMaxPayloadLength,		0xFF},		//Max. payload length after which header CRC error will arise 
	{RegHopPeriod,				0x00},		//No frequency hopping
	//{RegFifoRxByteAddr,			0x??},		//
	//{RegFeiMsb,					0x??},		//
	//{RegFeiMid,					0x??},		//
	//{RegFeiLsb,					0x??},		//
	//{RegRssiWideband,			0x??},		//
	{RegDetectOptimize,			0x??},		//default value ???
	{RegInvertIQ,				0x26},		//No invert I and Q signals in RX/TX, which is ??
	{RegDetectionThreshold,		0x0C},		//Detection threshold for SF6
	{RegSyncWord,				0x12},		//Sync word to match
	{RegInvertIQ2,				0x1D},		//default value - to be changed when RX invert is set
	{RegChirpFilter,			0xA0}		//default value ???
}


#define SINGLEMODE 0x01

uint8_t receivedData[6];

void sx1272Init();
void writeRegister(uint8_t address,uint8_t data,int size);
void readRegister(uint8_t address, int size);
void transmit(uint8_t data);


#endif /* SX1272_H_ */