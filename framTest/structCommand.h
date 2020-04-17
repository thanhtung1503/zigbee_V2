#include<stdint.h>
#include<string.h>
#include "cJSON.h"
#include <stdlib.h>
// number,int string-> (encode)-> string->(json)-> string(dang json)

//b1 json-> struct packet(co chua json)
//b2 ->commandPacket
// NetDev // NetRes

typedef struct NetDeviceStruct
{
	uint16_t type;
	uint16_t endpoint;
	uint32_t address;
}netDeviceStruct;

typedef struct  NetResourceStruct
{
	uint32_t profile;
	uint32_t cluster;
	uint32_t attribute;
}netResourceStruct;

typedef struct  NetReading
{
	uint64_t netOrigin;
	char* 	 netResource;
	uint8_t  netValueType;
	char* 	 netValue;
} netReading;
 //  Command(packet)  -> json
typedef struct  Packet
{   // {0,0,"/0","/0","/0","/0",0,"/0",0,"/0"}
	uint8_t cmd;
	uint8_t statusCode;
	char* statusMessage;
	char* MAC;
	char* linkKey;
	char* netDevice;    //   -> int --> <<
	uint8_t timeOut;
	char* content;
	uint8_t netReadingsCount;
	//cJSON* netReadings;  // json array// or convert to struct  netReadings struct NetReading
	netReading *netReadings;   // 
}packet;

typedef struct  DevicePaket
{
	uint8_t Cmd;
	char* MAC;
	char* linkKey;
	char* netDevice;
	uint8_t statusCode;
	char* statusMessage;
}devicePacket;

typedef struct CommandPacket
{
	uint8_t cmd;
	char* netDevice;
	uint8_t netReadings;  // 
	uint8_t statusCode;
	char* statusMessage;
}commandPacket;


// netValue

typedef struct  realTime
{
	uint8_t enable;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}realTime;

typedef struct  time
{
	uint8_t enable;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}time;




