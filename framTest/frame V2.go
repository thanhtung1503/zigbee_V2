// 
// --------------- Định nghĩa thông tin NetDevice và NetResource trong gói tin JSON -------------------
1.	NetDev		:		string  	=	{B7--B6		B5--B4		B3--B0		}
									=	{Type 		Endpoint	Address		}
						format=Hex	=	{00-01		00-F0		0000-FFFF	}
						example 	=   "0100ABCD"//0xcd =1 byte// 100-> 
				NetDev.uint32 		=	0x0100ABCD

2.	NetRes	    :		string 		=	{B11--B8	B7--B4		B3--B0		}
									=	{Profile 	Cluster		Attribute	}
						format=Hex	=	{0000-FFFF	0000-FFFF	0000-FFFF	}
						example 	=   "012344321ABCD"
				NetRes.uint64 		=	0x0000012344321ABCD

// ----------------------------------- Danh sách một số NetValue của Atrribute ---------------------------------
3. 	Realtime 	: 		uint64		=	{B7		B6--B5		B4		B3 		B2 		B1 		B0	  	}// char* encode --> decode
									=	{0		Year		Month	Day		Hour	Minute	Second	}
									=   {0		0-0xFFFF	1-12	1-31	0-23	0-59	0-59	}			

define:	Time  	: 		uint32		= 	{B3 	B2 		B1 		B0 		}
									= 	{0		Hour	Minute	Second	}
									= 	{FFFFFFFF-- khong phai lap lich	}
define: Address uint16:
		if type = Device --> Address	= 0x0000
		if type = Group --> Address 	= NetDev.uint32 & 0xFFFF

4.	ScheduleOnOff :		arr[16][7]	:
									=	{B6--B5 	B4--B1		B0}
									=	{Address	Time 		bool}
									=   {...		...			0-1	}

5.	ScheduleDimming :	arr[15][8]	:						
									=	{B7-B6		B5--B2		B1--B0	}
									=	{Address	Time	 	uint16 	}
									=	{...		...			0-0xFFFF}

7.	Group	:arr[50]Address 	= arr[50]2										


// ---------------------------------- Minh hoạ các gói tin JSON gửi tới Coordinator ---------------------------------
Add Device:
{"cmd":3,"mac":"12345678AABBCC22","lk":"This is a Link Key","dev":"","sc":0,"sm":""}
Rep:
{"cmd":3,"mac":"12345678AABBCC22","lk":"This is a Link Key","dev":"00001234","sc":0,"sm":""}

Get Command:
{"cmd":0,"dev":"000001","evt":[{"r":"123400","t":0}],"sc":0,"sm":""}
rep: {"cmd":0,"dev":"000001","evt":[{"r":"123400","t":0,"v":"AA=="}],"sc":0,"sm":""}

Put Command:
{"cmd":1,"dev":"000001","evt":[{"o":1586234682954542112,"r":"123400","t":0,"v":"AQ=="}],"sc":0,"sm":""}
Rep:
{"cmd":1,"dev":"000001","sc":0,"sm":""}

Delete Device:
{"cmd":4,"mac":"12345678AABBCC22","lk":"","dev":"00001234","sc":0,"sm":""}
Rep:
{"cmd":4,"mac":"12345678AABBCC22","sc":0,"sm":""}