/* Testing the interrupt
Connect a switch between D2 and GND on Arduino Nano. Between D4 and GND in MKR1000.
 ----------------
 I I
 I I
 I D2 I ----------/ ------I D2 on Nano, D4 on MKR1000
 I GND I -------------------I
 I I
 ---------------
Switch change will cause an interrupt. With a mechanical switch there is always some
bouncing.
Probably you will get more increments than one when closing or opening the switch!
On purpose, there is nothing done for timing of the writing to serial monitor.
Timo Karppinen 19.2.2017
*/
const byte ledPin = LED_BUILTIN; // automatically sets LED pin: Nano pin 13, MKR1000 pin 6
const byte interruptPin = 4; // 2 for Nano. Replace with 4 for MKR1000
const byte clkPin = 1;
const byte dtPin = 2;
volatile byte ledState = LOW;
volatile int count = 0;
int prev = 0;

void setup() {
 pinMode(ledPin, OUTPUT);
 pinMode(interruptPin, INPUT_PULLUP); // sets internal pull up resistor
 pinMode(clkPin, INPUT_PULLUP);
 pinMode(dtPin, INPUT_PULLUP);
 
 Serial.begin(9600);
 //attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(clkPin), change, CHANGE);
 
 Serial.println("ready for interrupts");
}
void loop() {
 
 Serial.println(count);
 delay(1000);
}
void change(){
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  
    if(digitalRead(dtPin)){
      count++;
    }
    else{
      count--;
    }
  
}
void blink() {
 ledState = !ledState;
 digitalWrite(ledPin, ledState);
 count = count + 1;
}
