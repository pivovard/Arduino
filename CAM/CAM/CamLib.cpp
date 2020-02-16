#include "CamLib.h"

const int _resetPin = 7;
const int _packageSize = 512;

void start()
{
	Serial.begin(9600);
	while (!Serial);

	Serial.println("Initializing camera...");
	Serial1.begin(9600);

	hardReset();
	sync();
	initial();

	Serial.println("Camera ready.\n");
}

void sync()
{
	Serial.println("\nSyncing.");
	unsigned long t = 4; //starts with 5

	do {
		//Serial1.setTimeout(++t);
		send(CAM_CMD::CMD_SYNC);
	} while (!recv(CAM_CMD::CMD_ACK, CAM_CMD::CMD_SYNC));

	if (recv(CAM_CMD::CMD_SYNC)) {
		send(CAM_CMD::CMD_ACK, CAM_CMD::CMD_SYNC);
	}

	delay(2000);
}

void hardReset()
{
	if (_resetPin > 0)
	{
		pinMode(_resetPin, OUTPUT);
		digitalWrite(_resetPin, LOW);
		delay(10);
		pinMode(_resetPin, INPUT);
		delay(10);
	}
}

void initial()
{
	Serial.println("\nSetting.");
	setImageFormat(COMP_JPEG, R640x480); //JPEG max resolution
	setPackageSize(_packageSize);
	setBaudRate();
}

void send(CAM_CMD cmd, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4)
{
	uint8_t buff[6] = { 0xAA, cmd, p1, p2, p3, p4 };
	Serial.println("Sending: " + String(buff[1], HEX) +" "+ String(buff[2], HEX) + " " + String(buff[3], HEX) + " " + String(buff[4], HEX) + " " + String(buff[5], HEX));
	Serial1.write(buff, 6);
}

long recv(CAM_CMD cmd, uint8_t option)
{
	uint8_t buff[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//memset(buff, 0x00, sizeof(buff));

	if (Serial1.readBytes((char*)buff, sizeof(buff)) == sizeof(buff))
	{
		Serial.println("Received: " + String(buff[1], HEX) + " " + String(buff[2], HEX) + " " + String(buff[3], HEX) + " " + String(buff[4], HEX) + " " + String(buff[5], HEX));
		if (buff[1] == cmd && (buff[2] == option || option == DONT_CARE)) {
			Serial.println("ACK");
			return buff[3] | buff[4] << 8 | buff[5] << 16 | 0x1000000;
		}
		else if (buff[1] == CMD_NAK) {
			Serial.println("Recv error!");
			return 0;
		}
	}

	Serial.println("Recv timed out.");
	return 0;
}

long recvData(long len)
{
	uint8_t buff[_packageSize];

	for (; len > _packageSize; len -= _packageSize) {
		Serial1.readBytes((char*)buff, sizeof(buff));
	}
	Serial1.readBytes((char*)buff, len);

	return 0;
}

void getJPEG()
{
	Serial.println("\nGet JPEG");
	//takeSnapshot(SNAP_JPEG);
	//send(CMD_GET_PICTURE, TYPE_SNAPSHOT);
	send(CMD_GET_PICTURE, TYPE_JPEG);
	delay(200);
	if (!recv(CMD_ACK, CMD_GET_PICTURE)) return; //GET_PICTURE doesn't reply ACK but sends DATA instantly

	Serial.println("Receiving data:");

	long len = 0;
	if (len = recv(CMD_DATA, TYPE_JPEG)) {
		Serial.println("Length is " + String(len));
		send(CMD_ACK);
		recvData(len);
	}
	else {
		Serial.println("Data receive failed!");
		return;
	}
}

void getRAW()
{
	takeSnapshot(SNAP_RAW);
	send(CMD_GET_PICTURE, TYPE_SNAPSHOT);
	if (!recv(CMD_GET_PICTURE)) return;
}


