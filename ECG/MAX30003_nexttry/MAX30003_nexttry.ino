/*
 Name:		MAX30003_nexttry.ino
 Created:	2/3/2020 4:17:53 PM
 Author:	TOWGGZE
*/

#include <Arduino.h>
#include <SPI.h>
#include "MAX30003.h"
#include "Timer5.h"
//#include <TimerOne.h>

const int samplingPeriod = 3900; //3.9ms 
unsigned long prev = 0;

int MAX30003_CS_PIN = 7;
int CLK_PIN = 6;
int INT = 0;

signed long ecgdata;
unsigned long data;

byte SPI_temp_32b[4];
char SPI_temp_Burst[100];


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	while (!Serial); // wait for serial port to connect. Needed for native USB port only

	pinMode(CLK_PIN, OUTPUT);
	pinMode(MAX30003_CS_PIN, OUTPUT);
	pinMode(INT, OUTPUT);
	digitalWrite(MAX30003_CS_PIN, HIGH);
	
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE1);

	SPI.setClockDivider(SPI_CLOCK_DIV8);
	
	//Start CLK timer
	//MyTimer5.begin(16);              // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
	MyTimer5.begin(30.517578125);
	MyTimer5.attachInterrupt(timerIsr); // attach the service routine here
	MyTimer5.start();

	//Timer1.initialize(16);              // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
	//Timer1.attachInterrupt(timerIsr); // attach the service routine here

	MAX30003_begin();   // initialize MAX30003 

	//delay(100);
	max30003_synch();

	MAX30003_Reg_Read(STATUS);
	unsigned long data0 = (unsigned long)(SPI_temp_32b[0]);
	data0 = data0 << 24;
	unsigned long data1 = (unsigned long)(SPI_temp_32b[1]);
	data1 = data1 << 16;
	unsigned long data2 = (unsigned long)(SPI_temp_32b[2]);
	data2 = data2 >> 6;
	data2 = data2 & 0x03;

	data = (unsigned long)(data0 | data1 | data2);
	ecgdata = (signed long)(data);

	Serial.println(data);

}

// 32KHz clock using timer1
void timerIsr()
{
	digitalWrite(CLK_PIN, digitalRead(CLK_PIN) ^ 1); // toggle Digital6 attached to FCLK  of MAX30003
}

// the loop function runs over and over again until power down or reset
void loop() {

	unsigned long m = micros();

	if (m - prev >= samplingPeriod)
	{
		prev = m;

		Serial.println("Reading");
		

		MAX30003_Reg_Read(ECG_FIFO);
		Serial.println(SPI_temp_32b[0]);
		Serial.println(SPI_temp_32b[1]);
		Serial.println(SPI_temp_32b[2]);
		return;
		MAX30003_Reg_Read(ECG_FIFO);
		unsigned long data0 = (unsigned long)(SPI_temp_32b[0]);
		data0 = data0 << 24;
		unsigned long data1 = (unsigned long)(SPI_temp_32b[1]);
		data1 = data1 << 16;
		unsigned long data2 = (unsigned long)(SPI_temp_32b[2]);
		data2 = data2 >> 6;
		data2 = data2 & 0x03;

		data = (unsigned long)(data0 | data1 | data2);
		ecgdata = (signed long)(data);

		Serial.println(data);
		Serial.println(ecgdata);

		MAX30003_Reg_Read(RTOR);
		
		unsigned long RTOR_msb = (unsigned long)(SPI_temp_32b[0]);
		// RTOR_msb = RTOR_msb <<8;
		unsigned char RTOR_lsb = (unsigned char)(SPI_temp_32b[1]);

		unsigned long rtor = (RTOR_msb << 8 | RTOR_lsb);
		rtor = ((rtor >> 2) & 0x3fff);

		float hr = 60 / ((float)rtor*0.008);
		unsigned int HR = (unsigned int)hr;  // type cast to int

		unsigned int RR = (unsigned int)rtor * 8;  //8ms

		 Serial.print(RTOR_msb);
		 Serial.print(",");
		 Serial.print(RTOR_lsb);
		 Serial.print(",");
		 Serial.print(rtor);
		 Serial.print(",");
		 Serial.print(RR);
		 Serial.print(",");
		 Serial.println(hr);      
	}
}

void MAX30003_Reg_Write(unsigned char WRITE_ADDRESS, unsigned long data)
{

	// now combine the register address and the command into one byte:
	byte dataToSend = (WRITE_ADDRESS << 1) | WREG;

	// take the chip select low to select the device:
	digitalWrite(MAX30003_CS_PIN, LOW);
	digitalWrite(INT, HIGH);

	delay(2);
	SPI.transfer(dataToSend);   //Send register location
	SPI.transfer(data >> 16);     //number of register to wr
	SPI.transfer(data >> 8);      //number of register to wr
	SPI.transfer(data);      //Send value to record into register
	delay(2);

	// take the chip select high to de-select:
	digitalWrite(MAX30003_CS_PIN, HIGH);
	digitalWrite(INT, LOW);
}

void MAX30003_Reg_Read(uint8_t Reg_address)
{
	uint8_t SPI_TX_Buff;

	digitalWrite(MAX30003_CS_PIN, LOW);
	digitalWrite(INT, HIGH);
	delay(1);
	SPI_TX_Buff = (Reg_address << 1) | RREG;
	SPI.transfer(SPI_TX_Buff); //Send register location
	delay(1);
	for (int i = 0; i < 3; i++)
	{
		//Serial.println(SPI.transfer(0x00));
		SPI_temp_32b[i] = SPI.transfer(0xff);
	}

	digitalWrite(MAX30003_CS_PIN, HIGH);
	digitalWrite(INT, LOW);
}

void MAX30003_Read_Data(int num_samples)
{
	uint8_t SPI_TX_Buff;

	digitalWrite(MAX30003_CS_PIN, LOW);

	SPI_TX_Buff = (ECG_FIFO_BURST << 1) | RREG;
	SPI.transfer(SPI_TX_Buff); //Send register location

	for (int i = 0; i < num_samples * 3; ++i)
	{
		SPI_temp_Burst[i] = SPI.transfer(0xff);
	}

	digitalWrite(MAX30003_CS_PIN, HIGH);
}

void max30003_sw_reset(void)
{
	MAX30003_Reg_Write(SW_RST, 0x000000);
	delay(100);
}

void max30003_synch(void)
{
	MAX30003_Reg_Write(SYNCH, 0x000000);
}

void MAX30003_begin()
{
	max30003_sw_reset();
	delay(100);
	MAX30003_Reg_Write(CNFG_GEN, 0x081007);
	delay(100);
	MAX30003_Reg_Write(CNFG_CAL, 0x720000);  // 0x700000  
	delay(100);
	MAX30003_Reg_Write(CNFG_EMUX, 0x0B0000);
	delay(100);
	MAX30003_Reg_Write(CNFG_ECG, 0x805000);  // d23 - d22 : 10 for 250sps , 00:500 sps
	delay(100);

	MAX30003_Reg_Write(CNFG_RTOR1, 0x3fc600);
	max30003_synch();
	delay(100);
}
