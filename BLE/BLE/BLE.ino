/*
 Name:		BLE.ino
 Created:	7/17/2020 9:55:59 PM
 Author:	pivov
*/

#include <Arduino.h>
//#include <SoftwareSerial.h>

#define RX 11
#define TX 10

//SoftwareSerial Serial1(RX, TX);

void setup() {
	Serial.begin(9600);
    Serial1.begin(9600);

    delay(100);

    setSlave();
}

// the loop function runs over and over again until power down or reset
void loop() {
    //byte data;
    //while (Serial1.available() > 0) {
    //    data = Serial1.read();
    //    Serial.write(data);
    //}

    //byte b;
    //while (Serial1.readBytes(&b, 1) == 1) // use "readBytes" and not "read" due to the timeout support
    //    Serial.write(b);

    byte data;
    uint16_t input;
    while (Serial1.available() > 0) {
        data = Serial1.read();
        for (int i = 0; i < 8; i++) {
            Serial.print((data >> i) & 1);
        }
        Serial.println();
    }
    
    delay(100);
}

void getType() {
    Serial1.print("AT");
    String s = Serial1.readString();
    if (s.length() == 2 && s.compareTo("OK") == 0)
    {
        Serial.println(s);
        Serial.println(F("HM-10 detected!"));
    }
    else if (s.length() == 0)
    {
        // check for CC41
        Serial1.println("");
        s = Serial1.readString();
        if (s.length() == 4 && s.compareTo("OK\r\n") == 0)
        {
            Serial.println(s);
            Serial.println(F("CC41 detected!")); // An HM-10 clone
        }
        else if (s.length() == 0)
        {
            // check for MLT_BT05
            Serial1.println("AT");
            s = Serial1.readString();
            if (s.length() == 4 && s.compareTo("OK\r\n") == 0)
            {
                Serial.println(s);
                Serial.println(F("MLT-BT05 detected!")); // An HM-10 clone
            }
            else if (s.length() == 0)
            {
                Serial.println(F("No response received from module."));
                Serial.println(F("Verify that the module is powered. Is the led blinking?"));
                Serial.println(F("Check that pins are correctly connected and the right values were entered."));
                Serial.println(F("Are you using a logic voltage converter for a module that already has such logic on board?"));
                Serial.println(F("Are you using a module that expects 3.3v logic? You might need to do logic convertion on Arduio's TX pin (module's RX pin)."));
            }
            else
            {
                Serial.print(F("Unexpected result of length="));
                Serial.println(s.length());
                Serial.println(s);
            }
        }
        else
        {
            Serial.print(F("Unexpected result of length="));
            Serial.println(s.length());
            Serial.println(s);
        }
    }
    else
    {
        Serial.print(F("Unexpected result of length="));
        Serial.println(s.length());
        Serial.println(s);
    }
}

void setMaster() {
    Serial1.print("AT+ROLE1");
    String s = Serial1.readString();
    Serial.println(s);

    Serial1.print("AT+IMME1");
    s = Serial1.readString();
    Serial.println(s);

    Serial1.print("AT+SHOW1");
    s = Serial1.readString();
    Serial.println(s);

    Serial1.print("AT+DISC?");
    s = Serial1.readString();
    Serial.println(s);
}

void setSlave() {
    Serial1.print("AT+ROLE0");
    String s = Serial1.readString();
    Serial.println(s);

    Serial1.print("AT+IMME0");
    s = Serial1.readString();
    Serial.println(s);

    Serial1.print("AT+SHOW0");
    s = Serial1.readString();
    Serial.println(s);
}
