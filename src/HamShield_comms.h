


#ifndef _HAMSHIELD_COMMS_H_
#define _HAMSHIELD_COMMS_H_


#if defined(ARDUINO) // using arduino?

#include "Arduino.h"

#define nCS A1 //15 //
#define CLK A5 //19 //
#define DAT A4 //18 //
#define MIC 3

#else // assume Raspberry Pi

#include "stdint.h"
#include <wiringPi.h>
#include <softTone.h>

#define GPIOBOARD true // set true when using Compute Module with IO Board

#if GPIOBOARD // using GPIOBOARD

// use GPIO layout without re-mapping
#define nCS 17 //BCM17
#define CLK 22 //BCM22
#define DAT 27 //BCM27
#define MIC 18 //BCM18

#else // using regular Raspberry Pi

#define nCS 0 //BCM17, HW pin 11 
#define CLK 3 //BCM22, HW pin 15 
#define DAT 2 //BCM27, HW pin 13 
#define MIC 1 //BCM18, HW pin 12

#endif

#endif

void HSsetPins(uint8_t ncs, uint8_t clk, uint8_t dat);

int8_t HSreadBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data);
int8_t HSreadBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data);
int8_t HSreadWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data);

bool HSwriteBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data);
bool HSwriteBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);
bool HSwriteWord(uint8_t devAddr, uint8_t regAddr, uint16_t data);


// hardware abstraction layer

unsigned long HSmillis();
void HSdelay(unsigned long ms);
void HSdelayMicroseconds(unsigned int us);


#endif /* _HAMSHIELD_COMMS_H_ */
