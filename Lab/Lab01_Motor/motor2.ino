const int ENA = 0;
const int IN1 = 1;
const int IN2 = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
}

void loop() {
  analogWrite(ENA,100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2,HIGH);
  delay(2000);
  analogWrite(ENA,200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2,LOW);
  delay(2000);
}
