1.	NetDev		:		string  	=	{B7--B6		B5--B4		B3--B0		}
									=	{Type 		Endpoint	Address		}
						format=Hex	=	{00-01		00-F0		0000-FFFF	}
						example 	=   "0100ABCD"
				NetDev.uint32 		=	0x0100ABCD

2.	NetRes	    :		string 		=	{B11--B8	B7--B4		B3--B0		}
									=	{Profile 	Cluster		Attribute	}
						format=Hex	=	{0000-FFFF	0000-FFFF	0000-FFFF	}
						example 	=   "012344321ABCD"
				NetRes.uint64 		=	0x0000012344321ABCD

3. 	Realtime 	: 		uint64		=	{B7		B6--B5		B4		B3 		B2 		B1 		B0	  	}
									=	{0		Year		Month	Day		Hour	Minute	Second	}
									=   {0		0-0xFFFF	1-12	1-31	0-23	0-59	0-59	}			

4. 	Time 	 	: 		uint32		= 	{B3 	B2 		B1 		B0 		}
									= 	{1		Hour	Minute	Second	}
									= 	{0	-- khong phai lap lich		}
									
5.	ScheduleOnOff :		NetDev.uint32 + arr[15][5]	= 4 + arr[15][5] :
				NetDev.uint32 		= 	{B3--B0}
						arr[0-14]	=	{B4--B1		B0  }
									=	{Time 		bool}
									=   {...		0-1	}

6.	ScheduleDimming :	NetDev.uint32 + arr[15][6] = 4 + arr[15][6] :
				NetDev.uint32 		= 	{B3--B0}
						arr[0-14]	=	{B5--B2		B1--B0	}
									=	{Time	 	uint16 	}
									=	{...		0-0xFFFF}

7. 	HistoricalEvent:	arr[10][50] :
						arr[0-9]	=	{B49--B41		B40--B0	}
									=	{Realtime	 	Event 	}	

8.	Group	:arr[50]NetDev.uint32 	= arr[50]4										


//
/*
typedef struct  Packet
{
	uint8_t cmd;
	uint8_t statusCode;
	char* statusMessage;
	char* MAC;
	char* linkKey;
	char* netDevice;    // 
	cJSON netReadings  // json array// or convert to struct 
	uint8_t timeOut;
	char* content;
}packet;
*/