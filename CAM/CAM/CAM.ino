/*
 Name:		CAM.ino
 Created:	2/13/2020 1:03:44 PM
 Author:	TOWGGZE
*/


#include "CamLib.h"
#include <MQTTClient.h>
#include <WiFi101.h>

//char *client_id = "d:<your Organization ID>:<your Device Type>:<your Device ID>";
char *client_id = "d:t434r5:MKR1000:CAM2";
char *user_id = "use-token-auth"; // telling that authentication will be done with token
//char *authToken = "dsfYrL5P5QkmShdWo3"; // Your IBM Watson Authentication Token
char *authToken = "3bv!m&r2bEgVMpZ8sc";

//char *ibm_hostname = “<your-org-id.messaging.internetofthings.ibmcloud.com>”;
char *ibm_hostname = "t434r5.messaging.internetofthings.ibmcloud.com";

WiFiClient wifi;
MQTTClient MQTTc(256);

//char ssid[] = "HAMKvisitor"; // your network SSID (name)
//char pass[] = "hamkvisitor"; // your network password (use for WPA)

char ssid[] = "UPC3421232"; // your network SSID (name)
char pass[] = "GTMPGVQR"; // your network password (use for WPA)

const size_t buffSize = 64;
const size_t jsonSize = 16;
char buff[buffSize];

int button = 6;
bool get = false;

void setup() {
	//setup cam
	start();

	Serial.println("Connecting to wifi.");
	while (WiFi.begin(ssid, pass) != WL_CONNECTED) delay(1000);
	printWiFiStatus();

	Serial.println("Connecting to IBM.");
	MQTTc.begin(ibm_hostname, 1883, wifi);
	
	Serial.println("Connection established.");

	pinMode(button, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(button), interrupt, RISING);
}

void loop() {
	if (!MQTTc.connected()) {
		Serial.println("Reconnecting to IBM.");
		while (!MQTTc.connect(client_id, user_id, authToken)) delay(2000);

		Serial.println(".");
	}
	MQTTc.loop();

	if (get) {
		long len = getJPEG();
		if (len < 0) return;

		uint8_t* img = new uint8_t(len);
		recvJPEG(len, img);
		uint8_t* it = img;

		Serial.println("Sending to IBM.");

		MQTTc.publish("iot-2/evt/img-info/fmt/json", "{\"size\":" + String(len) + "}");
		
		//bin is the right way, but either IoT or MQTT is not able receive 0 in an array
		/*
		for (int i = len; i > 0; i -= buffSize) {
			for (int j = 0; j < buffSize && j < i; ++j) {
				buff[j] = *it;
				++it;
			}
			MQTTc.publish("iot-2/evt/img-data/fmt/bin", buff);
		}
		*/

		//so lets make it in ungly json format - where stupid node-red receives only half of the data if they are too big
		String data = "";
		int pckg = 0;
		for (int i = len; i > 0; i -= jsonSize) {
			Serial.println("Sending pckg: " + String(pckg));
			++pckg;

			data = String(*it);
			++it;
			for (int j = 1; j < jsonSize && j < i; ++j) {
				data += "," + String(*it);
				++it;
			}
			MQTTc.publish("iot-2/evt/img-data/fmt/json", "{\"pckg\":" + String(pckg) + ",\"data\":[" + data + "]}");
		}

		//delete(img);
		get = false;

		Serial.println("Done.");
	}
}

void interrupt() {
	if (!get) {
		get = true;
	}
}

void printWiFiStatus() {
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
