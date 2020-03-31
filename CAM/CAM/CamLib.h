// CamLib.h

#ifndef _CAMLIB_h
#define _CAMLIB_h

#include <Arduino.h>

enum CAM_CMD
{
	CMD_INIT = 0x01
	, CMD_GET_PICTURE = 0x04
	, CMD_SNAPSHOT = 0x05
	, CMD_SET_PACKSIZE = 0x06
	, CMD_SET_BAUDRATE = 0x07
	, CMD_RESET = 0x08
	, CMD_DATA = 0x0A
	, CMD_SYNC = 0x0D
	, CMD_ACK = 0x0E
	, CMD_NAK = 0x0F
	, CMD_SET_FREQ = 0x13
	, CMD_SET_CBE = 0x14
	, CMD_SLEEP = 0x15
	, STARTBYTE = 0xAA
	, ZERO = 0x00
	, DONT_CARE = 0xFF
};

enum CAM_IMAGE_FORMAT
{
	RAW_8BIT = 0x03
	, RAW_16BIT_RGB565 = 0x06
	, COMP_JPEG = 0x07
	, RAW_16BIT_CRYCBY = 0x08
};

enum CAM_RES
{
	R80x60 = 0x01
	, R160x120 = 0x03
	, R160x128 = 0x03
	, R320x240 = 0x05
	, R640x480 = 0x07
	, R128x96 = 0x08
	, R128x128 = 0x09
};

enum CAM_PIC_TYPE
{
	TYPE_SNAPSHOT = 0x01
	, TYPE_RAW = 0x02
	, TYPE_JPEG = 0x05
};

enum CAM_SNAP_TYPE
{
	SNAP_JPEG = 0x00
	, SNAP_RAW = 0x01
};

enum CAM_RESET_TYPE
{
	RESET_FULL = 0x00
	, RESET_STATE = 0x01
	, RESET_FORCE = 0xFF
};

enum CAM_FREQ
{
	F50Hz = 0x00
	, F60Hz = 0x01
};

enum CAM_CBE
{
	CMIN = 0x00  // Exposure -2
	, CLOW = 0x01  //          -1
	, CDEFAULT = 0x02  //           0
	, CHIGH = 0x03  //          +1
	, CMAX = 0x04  //          +2
};

enum CAM_ERROR
{
	ERROR_PIC_TYPE = 0x01
	, ERROR_PIC_UPSCALE = 0x02
	, ERROR_PIC_SCALE = 0x03
	, ERROR_UNEXP_REPLY = 0x04
	, ERROR_PIC_TIMEOUT = 0x05
	, ERROR_UNEXP_CMD = 0x06
	, ERROR_JPEG_TYPE = 0x07
	, ERROR_JPEG_SIZE = 0x08
	, ERROR_PIC_FORMAT = 0x09
	, ERROR_PIC_SIZE = 0x0A
	, ERROR_PARAM = 0x0B
	, ERROR_SEND_TIMEOUT = 0x0C
	, ERROR_CMD_ID = 0x0D
	, ERROR_PIC_NOT_RDY = 0x0F
	, ERROR_PKG_NUM = 0x10
	, ERROR_PKG_SIZE = 0x11
	, ERROR_CMD_HEADER = 0xF0
	, ERROR_CMD_LENGTH = 0xF1
	, ERROR_PIC_SEND = 0xF5
	, ERROR_CMD_SEND = 0xFF
};

extern const int _resetPin;
extern const int _packageSize;

void start();
void sync();
void hardReset();
void initial();

void send(CAM_CMD cmd, uint8_t p1 = 0, uint8_t p2 = 0, uint8_t p3 = 0, uint8_t p4 = 0);
long recv(CAM_CMD cmd, uint8_t option = 0);
uint8_t* recvJPEG(long len, uint8_t* img);
long getJPEG();
void getRAW();

inline void setImageFormat(CAM_IMAGE_FORMAT format = COMP_JPEG, CAM_RES resolution = R640x480)
{
	send(CMD_INIT, 0x00, format, resolution, resolution);
	recv(CAM_CMD::CMD_ACK, CAM_CMD::CMD_INIT);
}
inline void takeSnapshot(CAM_SNAP_TYPE type = SNAP_JPEG, uint16_t frame = 0)
{
	send(CMD_SNAPSHOT, type, frame & 0xFF, (frame >> 8) & 0xFF); 
	delay(100);
	recv(CAM_CMD::CMD_ACK, CAM_CMD::CMD_SNAPSHOT);
}
inline void reset(CAM_RESET_TYPE type = RESET_FULL, bool force = true)
{
	send(CMD_RESET, type, 0x00, 0x00, force ? RESET_FORCE : 0x00);
	recv(CAM_CMD::CMD_ACK, CAM_CMD::CMD_RESET);
}
inline void setFrequency(CAM_FREQ frequency = F50Hz)
{
	send(CMD_SET_FREQ, frequency);
}
inline void setCBE(CAM_CBE contrast = CDEFAULT, CAM_CBE brightness = CDEFAULT, CAM_CBE exposure = CDEFAULT)
{
	send(CMD_SET_CBE, contrast, brightness, exposure);
}
inline void setIdleTime(uint8_t seconds = 15)
{
	send(CMD_SLEEP, seconds);
}
inline void setPackageSize(uint16_t size = 64)
{
	//send(CMD_SET_PACKSIZE, 0x08, size & 0xFF, ((size >> 8) & 0xFF) ? (_packageSize = size) : 0);
	//send(CMD_SET_PACKSIZE, 0x08, size & 0xFF, ((size >> 8) & 0xFF) ? (size) : 0);
	send(CMD_SET_PACKSIZE, 0x08, size & 0xFF, (size >> 8) & 0xFF);
	recv(CAM_CMD::CMD_ACK, CAM_CMD::CMD_SET_PACKSIZE);
}

inline void setBaudRate() {
	send(CMD_SET_BAUDRATE, 0x1F, 0x0B); //9600
	recv(CAM_CMD::CMD_ACK, CAM_CMD::CMD_SET_BAUDRATE);
}

#endif

