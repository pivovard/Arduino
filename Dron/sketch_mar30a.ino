
int LF = 5;
int RF = 6;
int LR = 9;
int RR = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LF, OUTPUT);
  analogWrite(LF, 255);
  pinMode(RF, OUTPUT);
  analogWrite(RF, 255);
  pinMode(LR, OUTPUT);
  analogWrite(LR, 255);
  pinMode(RR, OUTPUT);
  analogWrite(RR, 255);
  delay(100);
  // analogWrite(LF, 0);
  // analogWrite(RF, 0);
  // analogWrite(LR, 0);
  // analogWrite(RR, 0);
}

void loop() {
//  for(int i=100; i<255; i++){
//    analogWrite(led_pin, i);
//    delay(10);
//  }
//  for(int i=255; i>100; i--){
//    analogWrite(led_pin, i);
//    delay(10);
//  }
}
