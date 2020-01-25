
int dataPin = 3;
int STPin = 4;
int SHPin = 5;

uint8_t numbers[] = { 0b00111111, //0
                      0b00000110, //1
                      0b01011011, //2
                      0b01001111, //3
                      0b01100110, //4
                      0b01101101, //5
                      0b11111101, //6
                      0b00000111, //7
                      0b01111111, //8
                      0b11101111, //9
                      0b11111111  //all
                      };

uint32_t num = 0b00111111000001100101101101001111;
uint32_t b = 0b00000000000000000000000011111111;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(SHPin, OUTPUT);
}

void loop() {
//  for(int i = 0, w = 1; i < 8; i++, w=w<<1){
//    shiftOutToRegister(w);
//    delay(500);
//  }
//  for(int i = 0; i < 11; i++){
//    shiftOutToRegister(numbers[i]);
//    delay(500);
//  }
  write32bit(num);
}

void write32bit(uint32_t num){
  for(int i = 3; i >=0; i--){
    uint8_t w = (uint8_t)((num >> i*8) & b);
    shiftOutToRegister(w);
    delay(500);
  }
}

void shiftOutToRegister (byte toWrite) {
  bool pinState = 0;
  digitalWrite(STPin, 0);
  for(int i = 7; i>= 0; i--)
  {
    digitalWrite (SHPin, 0);
    if (toWrite & (1 << i)) {
      pinState = 1;
    }
    else { 
      pinState = 0;
    }
    digitalWrite (dataPin, pinState);
    digitalWrite (SHPin, 1);
    digitalWrite (dataPin, 0);
  }
  digitalWrite (SHPin, 0);
  digitalWrite (STPin, 1);
}
