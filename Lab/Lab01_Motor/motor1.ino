const int FETpin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(FETpin, OUTPUT);
  analogWrite(FETpin, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 256; i+=1){
    analogWrite(FETpin, i);
    delay(30);
  }
  for(int i = 255; i > -1; i-=1){
    analogWrite(FETpin, i);
    delay(30);
  }
}
