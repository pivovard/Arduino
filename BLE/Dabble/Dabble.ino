/*
 Name:		Dabble.ino
 Created:	7/20/2020 7:45:01 PM
 Author:	pivov
*/
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <Dabble.h>

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Dabble.begin(9600);
}

	// the loop function runs over and over again until power down or reset
	void loop() {
	Dabble.processInput();
	Serial.println(GamePad.getx_axis());
	Serial.println(GamePad.getYaxisData());
	Serial.println();
}
