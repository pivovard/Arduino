/*
 Name:		MAX30003_mikroelib.ino
 Created:	2/11/2020 8:50:22 AM
 Author:	TOWGGZE
*/

#include <Arduino.h>
#include <SPI.h>
#include "Timer5.h"
#include "MAX30003.h"

//int CS_PIN = 7;
int CLK_PIN = 6;

uint32_t ecgData;
__uint16_t rrData;
__uint16_t hrData;
uint32_t measTimeCnt;
char text[50];

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	while (!Serial); // wait for serial port to connect. Needed for native USB port only

	initSPI();

	//external clock
	/*pinMode(CLK_PIN, OUTPUT);
	//Start CLK timer
	MyTimer5.begin(16);              // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
	MyTimer5.attachInterrupt(timerIsr); // attach the service routine here
	MyTimer5.start();*/

	delay(100);

	ecg3_swReset();
	ecg3_fifoReset();
	delay(300);

	ecg3_init();
	measTimeCnt = 0;
	delay(300);

	Serial.println("Initialized");
}

// 32KHz clock using timer1
void timerIsr()
{
	digitalWrite(CLK_PIN, digitalRead(CLK_PIN) ^ 1); // toggle Digital6 attached to FCLK  of MAX30003
}

// the loop function runs over and over again until power down or reset
void loop() {
	ecg3_getECG(&ecgData);
	//ecg3_checkStatus(ecgData);
	Serial.println(ecgData);
}
