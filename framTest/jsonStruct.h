/*
 * jsonStruct.h
 *
 *  Created on: Dec 7, 2019
 *      Author: who_you_are
 */

#ifndef JSONSTRUCT_H_
#define JSONSTRUCT_H_

#include "cJSON.h"
#include "structCommand.h"   // lib for malloc

#define HEADER 0x55
#define EUI64SIZE 8
#define INSTALLCODE_LENGTH 18
typedef uint8_t userInstallCode[INSTALLCODE_LENGTH];
typedef uint8_t userEUI64[EUI64SIZE];

// parse receive;
packet getPacketStruct(char* packetString);
void respondPacket(packet p,char* str);

netDeviceStruct getDeviceStruct(char* Str);
void createDeviceJson(netDeviceStruct D,char* str);
netResourceStruct getResourceStruct(char* Str);
void createResourceJson(netResourceStruct R,char* str);
void getEUI64(char* str,uint8_t* eui64);

void getIstallcode(char* str,uint8_t* installCode);
void printfPacket(packet p);

// prepare to send


void createNetReadingsJson(netReading* netR, uint8_t count,char* str);


#endif /* JSONSTRUCT_H_ */

//
// Add Device:
// {"cmd":3,"mac":"12345678AABBCC22","lk":"This is a Link Key","dev":"","sc":0,"sm":""}
// Rep:
// {"cmd":3,"mac":"12345678AABBCC22","lk":"This is a Link Key","dev":"00001234","sc":0,"sm":""}

// Get Command:
// {"cmd":0,"dev":"000001","evt":[{"r":"123400","t":0}],"sc":0,"sm":""}
// rep: {"cmd":0,"dev":"000001","evt":[{"r":"123400","t":0,"v":"AA=="}],"sc":0,"sm":""}

// Put Command:
// {"cmd":1,"dev":"000001","evt":[{"o":1586234682954542112,"r":"123400","t":0,"v":"AQ=="}],"sc":0,"sm":""}
// Rep:
// {"cmd":1,"dev":"000001","sc":0,"sm":""}

// Delete Device:
// {"cmd":4,"mac":"12345678AABBCC22","lk":"","dev":"00001234","sc":0,"sm":""}
// Rep:
// {"cmd":4,"mac":"12345678AABBCC22","sc":0,"sm":""}