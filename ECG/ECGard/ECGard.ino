/*
 Name:		ECGard.ino
 Created:	1/25/2020 11:34:05 PM
 Author:	TOWGGZE
*/

// the setup function runs once when you press reset or power the board
//#include <WiFi101.h>
#include "WifiServerExp.h"

WifiServerExp* server;
float data[3];

//f = 100Hz -> T =  0.01
const int samplingPeriod = 100; //ms 
unsigned long previousMillis = 0;


void setup() {
	server = new WifiServerExp(666);
}

// the loop function runs over and over again until power down or reset
void loop() {
	unsigned long m = millis();

	if (m - previousMillis >= samplingPeriod)
	{
		previousMillis = m;
		data[0] = *((float *)&m); //assign value without cast to float

		data[1] = random();
		data[2] = random();

		server->send(data, 3);
	}	
}
