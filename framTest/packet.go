

type Header struct {
	Cmd uint8 `json:"cmd, omitempty"`					// CMD cho biet loai yeu cau
}

type Response struct {
	StatusCode    uint8  `json:"sc, omitempty"`			// ma phan hoi cua coordinator khi thuc hien yeu cau
	StatusMessage string `json:"sm, omitempty"`         // neu co loi, coordinator se ghi ra thong bao loi
}

type NetEvent struct {
	NetDevice   string       `json:"dev,omitempty"` 	// Address (dang hex) = ObjectType(1B) + Endpoint(1B) + Object Address(2B) = "0100ABCD"
	NetReadings []NetReading `json:"evt,omitempty"`
}

type NetReading struct {
	NetOrigin    int64              `json:"o,omitempty"` // Thoi diem tao ra Reading --> Hien tai khong quan tam den thong tin nay
	NetResource  string             `json:"r,omitempty"` // Dang hex = "0000" + AttributeID(2B) + ClusterID(2B) + ProfileID(2B), vi du: "0000AAAACCCCDDDD"
	NetValueType int 				`json:"t,omitempty"` // bat dau tu 0: Bool, String, Unit8,16,32,86, Int8,16,32,64, Float32,64, Binary
	NetValue     string             `json:"v,omitempty"` // gia tri dang string da duoc ma hoa Base64, hay decode Base64 de dc ket qua: char value[N]
}

// Goi tin dung de gui lenh:
// Khi DS gui lenh chi co Header + NetEvent
// Khi Coordinate phan hoi, se gom tat ca
type CommandPacket struct {
	Cmd uint8 `json:"cmd, omitempty"`
	NetDevice   string       `json:"dev,omitempty"` 	// Address (dang hex) = ObjectType(1B) + Endpoint(1B) + Object Address(2B) = "0100ABCD"
	NetReadings []NetReading `json:"evt,omitempty"`
	StatusCode    uint8  `json:"sc, omitempty"`			// ma phan hoi cua coordinator khi thuc hien yeu cau
	StatusMessage string `json:"sm, omitempty"` 
}

// Goi tin Add, Delete device
// Add:
// 		Khi DS gui lenh chi co Header + MAC + LinkKey
// 		Khi Coordinate phan hoi, se gom tat ca
// Delete:
// 		Khi DS gui lenh chi co Header + MAC + NetDevice
// 		Khi Coordinate phan hoi, se gom Header + Response
type DevicePacket struct {
	Cmd uint8 `json:"cmd, omitempty"`					// CMD cho biet loai yeu cau
	MAC       string `json:"mac, omitempty"` // "AABBCCDD012345678"  uint8 []
	LinkKey   string `json:"lk, omitempty"`  // link key
	NetDevice string `json:"dev, omitempty"` // Address = ObjectType(1B) + Endpoint(1B) + Object Address(2B)
	StatusCode    uint8  `json:"sc, omitempty"`			// ma phan hoi cua coordinator khi thuc hien yeu cau
	StatusMessage string `json:"sm, omitempty"`
}

// Goi tin Scan thiet bi --> Hien tai chua su dung:
// 		Khi DS gui lenh chi co Header + TimeOut 
// 		Khi Coordinate phan hoi, se gom: Header + Content + Response
type Discovery struct {
	Header
	TimeOut uint8  `json:"to, omitempty"`
	Content string `json:"ct, omitempty"`
	Response
}

NetReading 
//
 1.packet--
 // cmd: get,put,delete,add, report
 2 (.cmd(0,1)-> DevicePacket or 3(get,put)CommandPacket)
 3.(CommandPacket)
(	Cmd uint8 `json:"cmd, omitempty"` 
	NetDevice   string       `json:"dev,omitempty"` 	// Address (dang hex) = ObjectType(1B) + Endpoint(1B) + Object Address(2B) = "0100ABCD"
	NetReadings []NetReading `json:"evt,omitempty"`
	StatusCode    uint8  `json:"sc, omitempty"`			// ma phan hoi cua coordinator khi thuc hien yeu cau
	StatusMessage string `json:"sm, omitempty"` )

for(int i=0;i<len(NetReadings);i++)
{
	Reading=NetReadings[i];

	parse(Reading,NetDevice,cmd)
}

2.DevicePacket (delete,add)
(	Cmd uint8 `json:"cmd, omitempty"`					// CMD cho biet loai yeu cau
	MAC       string `json:"mac, omitempty"` // "AABBCCDD012345678"
	LinkKey   string `json:"lk, omitempty"`  // link key
	NetDevice string `json:"dev, omitempty"` // Address = ObjectType(1B) + Endpoint(1B) + Object Address(2B)
	StatusCode    uint8  `json:"sc, omitempty"`			// ma phan hoi cua coordinator khi thuc hien yeu cau
	StatusMessage string `json:"sm, omitempty"`)

//

CommandPacket(0,1)(get,put) (string)



//struct ->json
// json->struct

// struct
1.packet--(string,int,struct netdevice,string NetReading)
2.DevicePacket
3.CommandPacket
//
4NetDev
5.NetRes ( nam trong NetReadingt)
// netvalue
// hoãn
6.Realtime
7.Time 
8.ScheduleOnOff
9.ScheduleDimming
10.HistoricalEvent
11.Group