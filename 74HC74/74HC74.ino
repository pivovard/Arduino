int CLR = 0;
int PRE = 1;
int D = 4;
int CLK = 5;
int i =0;
void setup() {
  // put your setup code here, to run once:

  pinMode(CLR, OUTPUT);
  pinMode(PRE, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(CLK, OUTPUT);

  digitalWrite(CLR, HIGH);
  digitalWrite(PRE, HIGH);

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  i++;
  digitalWrite(CLK, LOW);
  digitalWrite(D, i%2);
  
  digitalWrite(CLK, HIGH);
  
  delay(1000);
}
