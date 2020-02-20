#include "CamLib.h"

const int _resetPin = 7;
const int _packageSize = 64; //512

void start()
{
	Serial.begin(9600);
	//while (!Serial);

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
	setBaudRate();
	setImageFormat(COMP_JPEG, R640x480); //JPEG max resolution
	setPackageSize(_packageSize);
	//setImageFormat(RAW_16BIT_RGB565, R160x120);
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
			return buff[3] | buff[4] << 8 | buff[5] << 16; // LSB // | 0x1000000;
		}
		else if (buff[1] == CMD_NAK) {
			Serial.println("Recv error!");
			return 0;
		}
	}

	Serial.println("Recv timed out.");
	return 0;
}

uint8_t* recvJPEG(long len)
{
	uint8_t buff[_packageSize];
	uint8_t* img = new uint8_t(len);
	uint16_t id = 0;
	uint16_t size = 0;
	int count = len / (_packageSize - 6) + 1;

	Serial.println("Receiving image(" + String(count) + " pkgs):");
	for (int i =0; i < count; i++) {
		Serial1.readBytes((char*)buff, sizeof(buff));

		id = buff[0] | buff[1] << 8;
		size = buff[2] | buff[3] << 8;

		Serial.println("Package " + String(id) + ", size " + String(size));
		//for(int j = 0; j < size; j++)
		//{
		//	img[i*(_packageSize - 6) + j] = buff[j + 4];
		//	Serial.print(buff[j+4]);
		//	Serial.print(" ");
		//}
		//Serial.println();

		send(CMD_ACK, 0, 0, buff[0], buff[1]);
	}

	Serial.println("Image received.");

	return img;
}

uint8_t* getJPEG()
{
	Serial.println("\nGet JPEG");
	//takeSnapshot(SNAP_JPEG);
	//send(CMD_GET_PICTURE, TYPE_SNAPSHOT);

	send(CMD_GET_PICTURE, TYPE_JPEG);
	delay(200);
	if (!recv(CMD_ACK, CMD_GET_PICTURE)) return nullptr; //GET_PICTURE doesn't reply ACK but sends DATA instantly

	Serial.println("Receiving data:");
	uint8_t* img;
	long len = 0;

	if (len = recv(CMD_DATA, TYPE_JPEG)) {
		Serial.println("Length is " + String(len));
		send(CMD_ACK);
		img = recvJPEG(len);
	}
	else {
		Serial.println("Data receive failed!");
		return nullptr;
	}

	//for (int j = 0; j < len; j++)
	//{
	//	Serial.print(img[j]);
	//	Serial.print(" ");
	//}

	return img;
}

void getRAW()
{
	//takeSnapshot(SNAP_RAW);
	//send(CMD_GET_PICTURE, TYPE_SNAPSHOT);
	
	send(CMD_GET_PICTURE, TYPE_RAW);
	delay(200);
	if (!recv(CMD_ACK, CMD_GET_PICTURE)) return; //GET_PICTURE doesn't reply ACK but sends DATA instantly

	Serial.println("Receiving data:");

	long len = 0;
	if (len = recv(CMD_DATA, TYPE_RAW)) {
		Serial.println("Length is " + String(len));
		send(CMD_ACK);
		//recvJPEG(len);
	}
	else {
		Serial.println("Data receive failed!");
		return;
	}
}


