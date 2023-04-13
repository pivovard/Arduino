/*
 Name:		ECGard.ino
 Created:	1/25/2020 11:34:05 PM
 Author:	TOWGGZE
*/

// the setup function runs once when you press reset or power the board
#include <WiFi101.h>
#include "WifiServerExp.h"
#include <MQTTClient.h>
#include "arduino_secrets.h"
#include "MAX30003.h"

const bool IoT = false;

//char *client_id = "d:<your Organization ID>:<your Device Type>:<your Device ID>";
const char *client_id = "d:t434r5:MKR1000:ECG";
const char *user_id = "use-token-auth";
const char *authToken = "hBElLeepXO3MVWyfRp";
const char *ibm_hostname = "t434r5.messaging.internetofthings.ibmcloud.com";

WiFiClient wifi;
MQTTClient MQTTc;
WifiServerExp* server;

uint32_t data[3];
uint16_t hr;
uint16_t rr;

const int samplingPeriod = 100; //ms 
unsigned long previousMillis = 0;


void setup() {
	if (IoT) {
		Serial.println("Connecting to wifi.");
		while (WiFi.begin(SECRET_SSID, SECRET_PASS) != WL_CONNECTED) delay(1000);

		Serial.println("Connecting to IBM.");
		MQTTc.begin(ibm_hostname, 1883, wifi);
		MQTTc.connect(client_id, user_id, authToken);
	}
	else {
		//start TCP server
		server = new WifiServerExp(333);
	}

	//init ECG 3 module
	initSPI();

	ecg3_swReset();
	ecg3_fifoReset();
	delay(300);

	ecg3_init();
	delay(300);

	Serial.println("Initialized");
}

// the loop function runs over and over again until power down or reset
void loop() {
		data[0] = millis();

		if (data[0] - previousMillis >= samplingPeriod)
		{
			previousMillis = data[0];

			ecg3_getECG(&data[1]);

			ecg3_getRTOR(&hr, &rr);
			data[2] = hr;

			if (IoT) {
				sendIoT();
			}
			else {
				sendApp();
			}
		}
}

void sendApp() {
	server->send(data, 3);
}

void sendIoT() {
	if (!MQTTc.connected()) {
		Serial.println("Reconnecting to IBM.");
		while (!MQTTc.connect(client_id, user_id, authToken)) delay(1000);
	}
	MQTTc.loop();

	MQTTc.publish("iot-2/evt/ecg/fmt/json", 
		"{\"time\":" + String(data[0]) + 
		",\"ecg\":" + String(data[1]) +
		",\"hr\":" + String(data[2]) +
		"}");
}
