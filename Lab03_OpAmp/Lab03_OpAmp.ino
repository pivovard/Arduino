int inPin = A1;
int refPin = A2;
int outPin = 1;

int val =0;
int valR=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(outPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(inPin);
  valR = analogRead(refPin);
  Serial.print(val);
  Serial.print(" ");
  Serial.print(valR);
  Serial.print(" ");
  Serial.println("uT");
  //Serial.println();
//  if(val > 0){
//    digitalWrite(outPin, LOW);
//  }
//  else{
//    digitalWrite(outPin, HIGH);
//  }
delay(50);
}
