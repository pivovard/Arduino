// 
// 
// 

#include "WifiServerExp.h"

WifiServerExp::WifiServerExp()
{
	WifiServerExp(80);
}

WifiServerExp::WifiServerExp(int port)
{
	init();
	connect();
	start(port);
}

void WifiServerExp::init() {
	if (!Serial) {
		Serial.begin(9600);
		while (!Serial); // wait for serial port to connect. Needed for native USB port only
	}
	if (WiFi.status() == WL_NO_SHIELD) {
		Serial.println("WiFi shield not present");
		Serial.println(WiFi.status());
		while (true);
	}
	Serial.println("WiFi avaible.");
	printMacAddress();
	listNetworks();
}

void WifiServerExp::connect()
{
	Serial.println("Connecting...");
	while (status != WL_CONNECTED) {
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);
		// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
		status = WiFi.begin(ssid, pass);

		delay(1000);
	}
	printWiFiStatus();
}

void WifiServerExp::start(int port)
{
	Serial.print("Starting server on port ");
	Serial.println(port);
	server = new WiFiServer(port);
	server->begin();
	Serial.println("Server is running.");
}

void WifiServerExp::printMacAddress() {
	// the MAC address of your Wifi shield
	byte mac[6];

	// print your MAC address:
	WiFi.macAddress(mac);
	Serial.print("MAC: ");
	for (int i = 5; i >= 0; i--) {
		Serial.print(mac[i], HEX);
		if (i > 0) {
			Serial.print(":");
		}
	}
	Serial.println();
}

void WifiServerExp::listNetworks() {
	// scan for nearby networks:
	Serial.println("** Networks **");
	int numSsid = WiFi.scanNetworks();
	if (numSsid == -1)
	{
		Serial.println("Couldn't get a wifi connection");
		while (true);
	}

	// print the list of networks seen:
	Serial.print("number of available networks: ");
	Serial.println(numSsid);

	// print the network number and name for each network found:
	for (int thisNet = 0; thisNet < numSsid; thisNet++) {
		Serial.print(thisNet);
		Serial.print(") ");
		Serial.print(WiFi.SSID(thisNet));
		Serial.print("\tSignal: ");
		Serial.print(WiFi.RSSI(thisNet));
		Serial.print(" dBm");
		Serial.print("\tEncryption: ");
		printEncryptionType(WiFi.encryptionType(thisNet));
		Serial.flush();
	}
}

void WifiServerExp::printEncryptionType(int thisType) {
	// read the encryption type and print out the name:
	switch (thisType) {
	case ENC_TYPE_WEP:
		Serial.println("WEP");
		break;
	case ENC_TYPE_TKIP:
		Serial.println("WPA");
		break;
	case ENC_TYPE_CCMP:
		Serial.println("WPA2");
		break;
	case ENC_TYPE_NONE:
		Serial.println("None");
		break;
	case ENC_TYPE_AUTO:
		Serial.println("Auto");
		break;
	}
}

void WifiServerExp::printWiFiStatus() {
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.print(rssi);
	Serial.println(" dBm");
}

void WifiServerExp::send(String msg)
{
	WiFiClient client = server->available();
	if (client && client.connected()) {
		Serial.println("Sending...");
		client.println(msg);
	}
}

void WifiServerExp::send(float data)
{
	WiFiClient client = server->available();
	if (client && client.connected()) {
		Serial.println("Sending...");
		byte *b = (byte *)&data;
		client.write(b, sizeof(float));
	}
}

void WifiServerExp::send(float* data, int num)
{
	WiFiClient client = server->available();
	if (client && client.connected()) {
		Serial.println("Sending...");
		byte *b = (byte *)data;
		size_t n = client.write(b, num*sizeof(float));
		//Serial.println(n);
	}
}

String WifiServerExp::recv()
{
	WiFiClient client = server->available();
	if (client && client.connected() && client.available()) { //client.available() = num of chars
		return client.readString();
	}
	return "";
}


