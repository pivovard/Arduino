// Writing to MCP4821 SPI DAC with Arduino MKR1000, MKRZERO, ....
// Option on connecting an audio amplifier IC.
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
// The Audio Amplifier LM380. Connection examples on the data sheet. 
// http://www.ti.com/product/LM380
//
// Timo Karppinen 2020. Tested 13.1.2020 and works correctly.

// include the SPI library:
#include <SPI.h>

const float Vref = 2.048;

const int chipSelectPin = 0;
const int loaddacPin = 5;
byte highbyte = B00011111; // write here the data for SPI
byte lowbyte = B11111000;  // write here the data for SPI

// for testing first with constant values   //  (Vout/Vref)2^N-1
const byte highbyte2volt = B00111111;  // 2,0 V on 12 bit DAC  (2/2,048)4095 = 1111 1010 0000
const byte lowbyte2volt  = B10100000;  // 2,0 V on 12 bit DAC

// timing of the audio samples.  fs =8 kHz -> T = 125 micro seconds
const int samplingPeriod = 125;
int previousMicros = 0;

// audio samples
int audio12bit = 0;
int y_n = 0;
int y_n1 = 0;
int y_n2 = 1023;

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

if( micros() - previousMicros > samplingPeriod )
{
  previousMicros = micros();
  // Calculate 10 bit value. 

  //audio12bit = 4095;    // 2047 = 1,023 volt , 4095 = 2,050 volt

  // The formula comes from DSP z-transform table: z-function for sin(2 pi f T) 
  // y_n = 1.3616335 * y_n1 - y_n2;   // 1046,5 Hz High C
  
   y_n = 1.9579344 * y_n1 - y_n2;     // 261,6 Hz Middle C
  
  // y_n = 1.9938347 * y_n1 - y_n2;      // 100 Hz
  
   y_n2 = y_n1;
   y_n1 = y_n;
  
   audio12bit = 2047 + 1 * y_n;       // The Gain can be changed in here.  1volt + Gain*audio
   audio12bit = (audio12bit/Vref)*4096;

  // Calculate the highByte and the lowByte
  highbyte = ((audio12bit >> 8)& B00001111) | B00110000;
  lowbyte = audio12bit & B11111111;
  
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
