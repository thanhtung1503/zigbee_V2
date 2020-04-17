/*
 * jsonStruct.c
 *
 *  Created on: Dec 7, 2019
 *      Author: who_you_are
 */
#include<stdio.h>
#include <stdlib.h>
#include"jsonStruct.h"
#include "userBase64.h"

packet getPacketStruct(char* packetString)
{
 	packet  packetStruct={0,0,NULL,NULL,NULL,NULL,0,NULL,0,NULL};
    cJSON *string_json = cJSON_Parse(packetString);
    //JSONArray arr = obj.getJSONArray("value");
    if (string_json == NULL)
    {
    	goto end;
    }
    if(cJSON_GetObjectItemCaseSensitive(string_json, "cmd")!=NULL)
    {
    	packetStruct.cmd =cJSON_GetObjectItemCaseSensitive(string_json, "cmd")->valuedouble;
    }

    if(cJSON_GetObjectItemCaseSensitive(string_json, "sc")!=NULL)
    {
    	packetStruct.statusCode =cJSON_GetObjectItemCaseSensitive(string_json, "sc")->valuedouble;
    }

        if(cJSON_GetObjectItemCaseSensitive(string_json, "sm")!=NULL)
    {
    	packetStruct.statusMessage =strdup(cJSON_GetObjectItemCaseSensitive(string_json, "sm")->valuestring);
    }

        if(cJSON_GetObjectItemCaseSensitive(string_json, "mac")!=NULL)
    {
    	packetStruct.MAC =strdup(cJSON_GetObjectItemCaseSensitive(string_json, "mac")->valuestring);
    }

        if(cJSON_GetObjectItemCaseSensitive(string_json, "lk")!=NULL)
    {
    	packetStruct.linkKey =strdup(cJSON_GetObjectItemCaseSensitive(string_json, "lk")->valuestring);
    }

        if(cJSON_GetObjectItemCaseSensitive(string_json, "dev")!=NULL)
    {
    	packetStruct.netDevice =strdup(cJSON_GetObjectItemCaseSensitive(string_json, "dev")->valuestring);
    }

        if(cJSON_GetObjectItemCaseSensitive(string_json, "to")!=NULL)
    {
    	packetStruct.timeOut =cJSON_GetObjectItemCaseSensitive(string_json, "to")->valuedouble;
    }

    if(cJSON_GetObjectItemCaseSensitive(string_json, "ct")!=NULL)
    {
    	packetStruct.content =strdup(cJSON_GetObjectItemCaseSensitive(string_json, "ct")->valuestring);
    }
    cJSON* jnetReadings =cJSON_GetObjectItem(string_json, "evt"); // array
    // struct Vector *retVal = malloc (sizeof (struct Vector));
	packetStruct.netReadingsCount=cJSON_GetArraySize(jnetReadings);
	printf("netReadingsCount:%d",packetStruct.netReadingsCount);
    packetStruct.netReadings = malloc(sizeof(netReading)*cJSON_GetArraySize(jnetReadings));

	// printf("--------------:%d",cJSON_GetArraySize(jnetReadings));

    for (int i = 0 ; i <packetStruct.netReadingsCount; i++)
	{
		cJSON * subitem = cJSON_GetArrayItem(jnetReadings, i);
		packetStruct.netReadings[i].netResource = strdup(cJSON_GetObjectItem(subitem, "r")->valuestring);
		packetStruct.netReadings[i].netValueType = cJSON_GetObjectItem(subitem, "t")->valuedouble;
		packetStruct.netReadings[i].netValue= strdup(cJSON_GetObjectItem(subitem, "v")->valuestring);
		packetStruct.netReadings[i].netOrigin =	cJSON_GetObjectItem(subitem, "o")->valuedouble;
		//cJSON_free(subitem);
		//packetStruct.netReadings[i].netResource =resource->valuestring;
		//printf("Event[%d]:\n\tresource:%s\n\ttype:%d\n\tvalue:%s\n", i, packetStruct.netReadings[i].netResource, packetStruct.netReadings[i].netValueType, packetStruct.netReadings[i].netValue);
	}
end:

    cJSON_Delete(string_json);

     return packetStruct;
}


//
/*

typedef struct NetDeviceStruct
{
	uint16_t type;
	uint16_t endpoint;
	uint32_t address;
}netDeviceStruct;

*/
netDeviceStruct getDeviceStruct(char* str)
{
	netDeviceStruct netDeviceStructTest ={0,0,0};
	uint64_t intNetDevice = strtol(str,NULL,16);// 000002// 11120013
	netDeviceStructTest.type = (intNetDevice >>24)&0xff;//  
	netDeviceStructTest.endpoint = (intNetDevice >>16)&0xff;
	netDeviceStructTest.address = intNetDevice&0xffff;
	printf("\ngetDeviceStruct\ntype:%d endpoint:%d address:%d\n",
				netDeviceStructTest.type,
				netDeviceStructTest.endpoint,
				netDeviceStructTest.address);
	return netDeviceStructTest;
}
/*
	uint16_t type;
	uint16_t endpoint;
	uint32_t address;
*/

void createDeviceJson(netDeviceStruct D,char* str)
{
	uint64_t type =(uint64_t)D.type;
	uint64_t endpoint =(uint64_t)D.endpoint;
	uint64_t address    =(uint64_t)D.address;
	uint64_t value = (type<<24)+ (endpoint<<16)+(address);
	sprintf(str,"%08lX",value);	
	printf("createDeviceJson---:\n%s\n",str);
}

netResourceStruct getResourceStruct(char* str)
{
	netResourceStruct resourceStruct;
	uint64_t intRes = strtol(str,NULL,16);
	printf("\n\nintRes:%lx--%ld\n",intRes,intRes); //110012013--4563476499
	resourceStruct.profile =(intRes>>32)&0xffff;
	resourceStruct.cluster =(intRes>>16)&0xffff;
	resourceStruct.attribute =(intRes)&0xffff;
	printf("\ngetResourceStruct\nprofile:%d  cluster:%d  attribute:%d\n",resourceStruct.profile,resourceStruct.cluster,resourceStruct.attribute);
	return resourceStruct;
}

void createResourceJson(netResourceStruct R,char* str)
{
	uint64_t profile =(uint64_t)R.profile;
	uint64_t cluster =(uint64_t)R.cluster;
	uint64_t attr    =(uint64_t)R.attribute;
	uint64_t value = (profile<<32)+ (cluster<<16)+(attr);   // 0xff =16bit ffffffff
	sprintf(str,"%08lX",value);
}


void getEUI64(char* str,uint8_t* eui64)
{
	uint64_t intEUI64 =strtol(str,NULL,16);
	//userEUI64 Mac;
	for(int i=0;i<EUI64SIZE;i++)
	{
		eui64[i]= (intEUI64>>((EUI64SIZE-i-1)*8))&0xff;
		//printf("MAC[%d]:%d",i,eui64[i]);
	}
}

void getIstallcode(char* str,uint8_t* installCode)
{
	uint64_t intCode = strtol(str,NULL,16);
	for(int i=0;i<INSTALLCODE_LENGTH;i++)
	{
		installCode[i] =(intCode>>((INSTALLCODE_LENGTH-i-1)*8))&0xff;
	}
}
void printfPacket(packet p)
{
	printf("cmd:%d\nstatusCode:%d\nstatusMessage:%sMAC:%s\nlinkKey:%s\nnetDevice:%s\ntimeOut:%d\ncontent:%s\nnetReadingsCount:%d\n",p.cmd,p.statusCode,p.statusMessage,p.MAC,p.linkKey,p.netDevice,p.timeOut,p.content,p.netReadingsCount);
}
/*
typedef struct  NetReading
{
	uint64_t netOrigin;
	char* 	 netResource; 
	uint8_t  netValueType;
	char* 	 netValue;
} netReading;
*/

void createNetReadingsJson(netReading* netR, uint8_t count,char* str)
{
	char originStr[16];
	char typeStr[8];
	uint32_t lengthR=0;
	printf("\ncount:%d\n",count);
	for(int i=0;i<count;i++)
	{
		//netReading rTest ={0,"netResource",0,"netValue"};
		if(i==count-1)
		{
			sprintf(str+lengthR,"{\"r\":\"%s\",\"v\":\"%s\"}",netR[i].netResource,netR[i].netValue);
		}
		else
		{
			sprintf(str+lengthR,"{\"r\":\"%s\",\"v\":\"%s\"},",netR[i].netResource,netR[i].netValue);
		}
		lengthR+=strlen(netR[i].netResource)+strlen(netR[i].netValue) + 16;
	}
}
/*
	uint8_t cmd;
	uint8_t statusCode;
	char* statusMessage;
	char* MAC;
	char* linkKey;
	char* netDevice;    //   -> int --> <<  // maybe call create netDeviceJson
	uint8_t timeOut;
	char* content;
	uint8_t netReadingsCount;
	//cJSON* netReadings;  // json array// or convert to struct  netReadings struct NetReading
	netReading *netReadings;  call create netReadingJson
*/

void respondPacket(packet p,char* str)
{
	//char str[500];
	char cmdStr[10] ="cmdStr";
	char statusCodeStr[16]="statusCodeStr";
	char timeOutStr[16]="timeOutStr";
	char netReadStr[100];
	createNetReadingsJson(p.netReadings,p.netReadingsCount,netReadStr);// co cap phat vung nho, phai free

	// netReading and netDevice chua xu ly
	// itoa(p.cmd,cmdStr,10);
	// itoa(p.statusCode,statusCodeStr,10);
	// itoa(p.timeOut,timeOutStr,10);
	sprintf(str,"{\"cmd\":%s,\"sc\":%s,\"sm\":\"%s\",\"mac\":\"%s\",\"lk\":\"%s\",\"dev\":\"%s\",\"evt\":[{\"%s\"}],\"to\":%s,\"ct\":\"%s\"}",
								cmdStr,
								statusCodeStr,
								p.statusMessage,
								p.MAC,
								p.linkKey,
								p.netDevice,
								netReadStr,                //p.netReadings,   // net repair
								timeOutStr,
								p.content);

	// char *string =(char*) malloc(sizeof(char)* strlen(str));	
	// strcpy(string,str);
	// printf("prepare---packet:\n%s\n",string);				
	// return string;
}


