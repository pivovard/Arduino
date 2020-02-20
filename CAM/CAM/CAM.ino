/*
 Name:		CAM.ino
 Created:	2/13/2020 1:03:44 PM
 Author:	TOWGGZE
*/


#include "CamLib.h"
#include <MQTTClient.h>
#include <WiFi101.h>

//char *client_id = "d:<your Organization ID>:<your Device Type>:<your Device ID>";
char *client_id = "d:t434r5:MKR1000:CAM";
char *user_id = "use-token-auth"; // telling that authentication will be done with token
char *authToken = "dsfYrL5P5QkmShdWo3"; // Your IBM Watson Authentication Token

//char *ibm_hostname = “<your-org-id.messaging.internetofthings.ibmcloud.com>”;
char *ibm_hostname = "t434r5.messaging.internetofthings.ibmcloud.com";

WiFiClient wifi;
MQTTClient MQTTc;

char ssid[] = "HAMKvisitor"; // your network SSID (name)
char pass[] = "hamkvisitor"; // your network password (use for WPA)

int button = 6;
bool get = false;

void setup() {
	start();

	Serial.println("Connecting to wifi.");
	WiFi.begin(ssid, pass);
	delay(5000);

	Serial.println("Connecting to IBM.");
	MQTTc.begin(ibm_hostname, 1883, wifi);
	MQTTc.connect(client_id, user_id, authToken);
	delay(3000);

	

	pinMode(button, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(button), interrupt, RISING);
}

void loop() {
	MQTTc.loop();

	if (get) {
		uint8_t* img = getJPEG();

		Serial.println("Sending to IBM.");
		//MQTTc.publish("JPEG", (char*)img);
		//MQTTc.publish("iot-2/evt/imf/fmt/bin", (char*)img);
		String data = String(img[0]);
		for (int i = 1; i < 100; i++) data += "," + String(img[i]);
		Serial.println(data);
		MQTTc.publish("iot-2/evt/imf/fmt/json", "{\"img\":[" + data + "]}");

		delete(img);
		get = false;

		Serial.println("Done.");
	}
}

void interrupt() {
	if (!get) {
		get = true;
	}
}
