// WifiServer.h

#ifndef _WIFISERVER_h
#define _WIFISERVER_h

#include <Arduino.h>
#include <WiFi101.h>
#include "arduino_secrets.h"



class WifiServerExp {
private:
	char* ssid = SECRET_SSID;    // your network SSID (name)
	char* pass = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
	int keyIndex = 0;             // your network key Index number (needed o

	int status = WL_IDLE_STATUS;

public:
	WiFiServer* server;

	WifiServerExp();
	WifiServerExp(int port);

	void init();
	void connect();
	void start(int port);

	void printMacAddress();
	void listNetworks();
	void printEncryptionType(int thisType);
	void printWiFiStatus();

	void send(String msg);
	void send(float data);
	void send(float* data, int num);
	String recv();

	
};

#endif

