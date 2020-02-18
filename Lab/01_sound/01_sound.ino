
// Writing to MCP4821 SPI DAC with Arduino MKR1000, MKRZERO, ....
// 
//Connect:
//                                       --------------
//3,3V from Arduino MKR Vcc          - I Vdd   Vout I - The oputput 0 V ...2.046 V
//chip select from MKR 0             - I CS     Vss I - 0,0 V from Arduino GND
//SPI serial clock from MKR 9        - I SCLK  SHDN I - shut down, connect to 3,3V
//SPI MOSI from MKR 8                - I DIN   LDAC I - Load data to output, MKR 5
//                                       --------------
// DAC 16 bit word = Highbyte lowbyte = CCCCDDDD DDDDDDDD
// CCCC = 0011 for output Gain 1.
// CCCC = 0001 for output Gain 2.
//
// Timo Karppinen 2020. Tested 13.1.2020 and works correctly.

// include the SPI library:
#include <SPI.h>

const int chipSelectPin = 0;
const int loaddacPin = 5;
byte highbyte = 0B00011111; // write here the data for SPI
byte lowbyte = 0B11111000;  // write here the data for SPI

// for testing first with constant values   //  (Vout/Vref)2^N-1
const byte highbyte2volt = 0B00111111;  // 2,0 V on 12 bit DAC  (2/2,048)4096 = 1111 1010 0000
const byte lowbyte2volt  = 0B10100000;  // 2,0 V on 12 bit DAC

const float Vref = 2.048;

int out12bit = 0;

// timing of the samples.  fs =8 kHz -> T = 125 micro seconds
const int samplingPeriod = 125;
int previousMicros = 0;

void setup() {
  pinMode(chipSelectPin, OUTPUT);
  pinMode(loaddacPin, OUTPUT);
  digitalWrite(loaddacPin, HIGH); // for not loading immediately to dac output 
//digitalWrite(loaddacPin, LOW); // for loading to dac output immediately after transfer
  // initialize SPI:
  SPI.begin();
}

void loop() {
// Calculating output and writing to DAC once in sampling period.

double value = 1;

if( micros() - previousMicros > samplingPeriod )
{
  previousMicros = micros();
  // Calculate 12 bit value
  // with the formula (Vout/Vref)(2^N-1)
   
   //out12bit = 2047;    // Write here your calculated output value!
   //out12bit = 0B11111111111;
   out12bit = (value/Vref)*4096;


  // Calculate the highByte and the lowByte. Highbyte lowbyte = CCCCDDDD DDDDDDDD
  highbyte = ((out12bit >> 8)& 0B00001111) | 0B00110000;
  lowbyte = out12bit & 0B11111111;
  
  // Write to DAC input register without updating
  // the DAC output register.

  // Settings for SPI
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

     // take the CS pin low to select the chip:
     digitalWrite(chipSelectPin, LOW);
     //  send in the value in two bytes via SPI:
     SPI.transfer(highbyte);
     SPI.transfer(lowbyte);
     // take the CS pin high to de-select the chip:
     digitalWrite(chipSelectPin, HIGH);

  SPI.endTransaction();

  // update DAC output. Not needed if LDAC is permanently connected to 0 V.
    digitalWrite(loaddacPin, LOW);
    delayMicroseconds(10);
    digitalWrite(loaddacPin, HIGH);
}
}
