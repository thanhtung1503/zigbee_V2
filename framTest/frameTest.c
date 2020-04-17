#include<stdio.h>
#include<stdint.h>
#include "jsonStruct.h"

void parse_object(cJSON *root);
void* createNetReadingsJsonTest(netReading netR, uint8_t count);
void freePacket(packet p);
int  main()
{


	// test create uint8_t[] to char*
	// char* v ="AA==";
	// uint64_t lenT;
	// char* value =base64_decode("AA==",&lenT);
	// printf("%d",*(uint8_t*)value);

	// for(int i=0;i<8;i++)
	// {
	// 	a+=8*i*sizeof(char);
	// 	sprintf(key+a,"%0X",test[i]);
	// }

	// printf("\neui64\n%s\n",key2);
	// char* macStr = (char*)test;
	// printf("%s",macStr);
	// char *eui64Str = base64_decode(macStr,&eui64_length);
	// printf("%s",eui64Str);
	char* inputPacket ="{\"cmd\":0,\"dev\":\"11120013\",\"evt\":[{\"o\":1586162461497206875,\"r\":\"001100120013\",\"t\":0,\"v\":\"AA==\"},{\"o\":1586162461497206875,\"r\":\"123400\",\"t\":0,\"v\":\"AA==\"}],\"sc\":\"0\",\"sm\":\"\"}";
	cJSON *array ;//= cJSON_CreateArray();
	packet inputPacketStruct = getPacketStruct(inputPacket);


	// test getDeviceStruct
	// netDeviceStruct test2 = getDeviceStruct(inputPacketStruct.netDevice);
	// printf("---------test.type:%d----test.endpoint:%d----test.address:%d---",test2.type,test2.endpoint,test2.address);
	// char str[100];
	// createDeviceJson(test2,str);
	// printf("\ndeviceJson:\n%s\n",str);

	char str1[100];
	netResourceStruct resourceS = getResourceStruct(inputPacketStruct.netReadings[0].netResource);
	createResourceJson(resourceS,str1);
	printf("createResourceJson\n%s",str1);
	// test createNetReadings
	char netTest[100];
	createNetReadingsJson(inputPacketStruct.netReadings, inputPacketStruct.netReadingsCount,netTest);
	printf("\ntest create netReading Json\n%s\n",netTest);
	// test create createDeviceJson
	// netDeviceStruct dviceS= getDeviceStruct(inputPacketStruct.netDevice);

	// test createDeviceResourceJ
	char deviceRJson[100];
	// createResourceJson(inputPacketStruct.netReadings[0]->netResource,deviceRJson);
	// printf("\ndeviceRJson\n:%s\n",deviceRJson);
	//createResourceJson(inputPacketStruct.netReadings->netResource,deviceRJson);


	//test create json packet
	// char packetJ[200];
	// respondPacket(inputPacketStruct,packetJ);
	// printf("\n--create packetJson\n%s\n",packetJ);

	// test MAc
	// userEUI64 euiTest;
	// getEUI64("1112131415161718",euiTest);

	// printf("\ninput(char): 1112131415161718");
	// for(int i=0;i<EUI64SIZE;i++)
	// {
	// 	printf("\nEUI64[%d]:%d",i,euiTest[i]);
	// }

	// uint8_t EUI64[8] ={11,22,33,44,55,66,7,8};
	// uint64_t test =atoi(inputPacketStruct.netDevice);
	// printf("\ntest:%ld\n",test);
	// char* strTest ="1111111111111111";
	// uint64_t structTest = strtol(strTest,NULL,16); //
	// printf("value =:%ld",structTest);
	freePacket(inputPacketStruct);
	createNetReadingsJson(inputPacketStruct.netReadings, inputPacketStruct.netReadingsCount,netTest);
	printf("\ntest create netReading Json\n%s\n",netTest);
	return 1;
}

void freePacket(packet p)
{
	if(p.MAC!=NULL)
	{
		free(p.MAC);
	}
	if(p.statusMessage!=NULL)
	{
		free(p.statusMessage);
	}
	if(p.linkKey!=NULL)
	{
		free(p.linkKey);
	}
	if(p.netDevice!=NULL)
	{
		free(p.netDevice);
	}
	if(p.content!=NULL)
	{
		free(p.content);
	}
	for(int i=0;i<p.netReadingsCount;i++)
	{
		if(p.netReadings[i].netResource!=NULL)
		{
			free(p.netReadings[i].netResource);
		}
		if(p.netReadings[i].netValue!=NULL)
		{
			free(p.netReadings[i].netValue);
		}
	}
}
// void* createNetReadingsJsonTest(netReading netR, uint8_t count)
// {
// 	char str[500];
//     // snprintf(string, size, “format string” , vars)
	
// 	for(int i=0;i<count;i++)
// 	{
// 		char originStr[16];
// 		char typeStr[8];
// 		// itoa(netR.netOrigin,originStr,10);
// 		// itoa(netR.netValueType,typeStr,10);
// 		//sprintf(str,"{\"MAC\":\"%s\",\"PAN\":%s,\"addr\":%s"));
// 	}

// 	char *string =(char*) malloc(sizeof(char)* strlen(str));
// 	//return str;
// }
/*
{"cmd":3,"mac":"12345678AABBCC22","lk":"This is a Link Key","dev":"","sc":0,"sm":""}
{"cmd":0,"dev":"000001","evt":[{"r":"123400","t":0}],"sc":0,"sm":""}
{"cmd":1,"dev":"000001","evt":[{"o":1586162461497206875,"r":"123400","t":0,"v":"AA=="}],"sc":0,"sm":""}
{"cmd":4,"mac":"12345678AABBCC11","lk":"","dev":"000001","sc":0,"sm":""}
*/