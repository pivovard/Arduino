//-----------------------------------------------------------------------------
// Copyright 2018 Peter Balch
// subject to the GNU General Public License
// sends samples to PC to be displayed
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Defines and Typedefs
//-----------------------------------------------------------------------------

// get register bit - faster: doesn't turn it into 0/1
#ifndef getBit
#define getBit(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#endif

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

const long BAUDRATE = 115200;  // Baud rate of UART in bps
const int COMMANDDELAY = 10;  // ms to wait for the filling of Serial buffer
const int COMBUFFERSIZE = 4; // Size of buffer for incoming numbers

const int testSignalPin = 3;

const char ack = '@'; // acknowledge for comms command

const int FreeRunTimeout = 0x10; // 0.5 sec for free run

const int SampPerA = 6; // sample period = n*SampPerA+SampPerB clocks
const int SampPerB = 18;

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

uint8_t curAdcPin = 0;
uint8_t curVref = 1;
uint8_t curPeriod = 200;
uint8_t curPrescaler = 7;
char commandBuffer[COMBUFFERSIZE + 1];
bool TrigRising = true;

const int ADCBUFFERSIZE = 1000;
uint8_t ADCBuffer[ADCBUFFERSIZE];

//-----------------------------------------------------------------------------
// initADC()
//-----------------------------------------------------------------------------
void initADC(void)
{
    //  ADCSRA = 0x00; // ADC Control and Status Register A
    // 0  Bit 7 – ADEN: ADC Enable
    // 0  Bit 6 – ADSC: ADC Start Conversion
    // 1  Bit 5 – ADATE: ADC Auto Trigger Enable
    // 0  Bit 4 – ADIF: ADC Interrupt Flag
    // 1  Bit 3 – ADIE: ADC Interrupt Enable
    // 111  Bits 2:0 – ADPSn: ADC Prescaler Select [n = 2:0]

    ADCSRB = 0x0; //ADC Control and Status Register B
    // 0 Bit 6 – ACME: Analog Comparator Multiplexer Enable
    // 000 Bits 2:0 – ADTSn: ADC Auto Trigger Source [n = 2:0] Free Running mode

    ADMUX = 0x20 + (curVref << 6) + curAdcPin; // ADC Multiplexer Selection Register
    // rr    Bits 7:6 – REFSn: Reference Selection = Vcc
    // 1     Bit 5 – ADLAR: ADC Left Adjust Result
    // aaaa  Bits 3:0 – MUXn: Analog Channel Selection

    DIDR0 = 0x3F; // Digital Input Disable Register 0
    // ADC0D=1, ADC1D=1, ADC2D=1, ADC3D=1, ADC4D=1, ADC5D=1, ADC6D=0, ADC7D=0

}

//-----------------------------------------------------------------------------
// fillBuffer
//-----------------------------------------------------------------------------
// Fills the given buffer with bufferSize chars from a Serial object

void fillBuffer(char* buffer, byte bufferSize)
{
    // Clean buffer
    memset((void*)buffer, '\0', sizeof(char) * bufferSize);

    byte limit = (bufferSize < Serial.available()) ? bufferSize : Serial.available();

    // Fill buffer
    for (byte i = 0; i < limit; i++) {
        buffer[i] = Serial.read();
    }
}

void printStatus(void)
{
    Serial.print("Baud rate: ");  Serial.println(BAUDRATE);

    Serial.print("curAdcPin: "); Serial.println(curAdcPin);
    Serial.print("curVref: "); Serial.println(curVref);
    Serial.print("curPeriod: "); Serial.println(curPeriod);
    Serial.print("curPrescaler: "); Serial.println(curPrescaler);

    Serial.print("TIMSK0: "); Serial.println(TIMSK0, HEX);
    Serial.print("TIMSK1: "); Serial.println(TIMSK1, HEX);
    Serial.print("TIMSK2: "); Serial.println(TIMSK2, HEX);
    Serial.print("ACSR: "); Serial.println(ACSR, HEX);
    Serial.print("ADCSRA: "); Serial.println(ADCSRA, HEX);
    Serial.print("ADCSRB: "); Serial.println(ADCSRB, HEX);
    Serial.print("ADMUX: "); Serial.println(ADMUX, HEX);
    Serial.print("DIDR0: "); Serial.println(DIDR0, HEX);
    Serial.print("DIDR1: "); Serial.println(DIDR1, HEX);

    Serial.print("TCCR0A: "); Serial.println(TCCR0A, HEX);
    Serial.print("TCCR0B: "); Serial.println(TCCR0B, HEX);

    Serial.print("TCCR1A: "); Serial.println(TCCR1A, HEX);
    Serial.print("TCCR1B: "); Serial.println(TCCR1B, HEX);
    Serial.print("TCCR1C: "); Serial.println(TCCR1C, HEX);
    Serial.print("TCNT1L: "); Serial.println(TCNT1L, HEX);
    Serial.print("TCNT1H: "); Serial.println(TCNT1H, HEX);
    Serial.print("ICR1L: "); Serial.println(ICR1L, HEX);
    Serial.print("ICR1H: "); Serial.println(ICR1H, HEX);
    Serial.print("OCR1AL: "); Serial.println(OCR1AL, HEX);
    Serial.print("OCR1AH: "); Serial.println(OCR1AH, HEX);
    Serial.print("OCR1BL: "); Serial.println(OCR1BL, HEX);
    Serial.print("OCR1BH: "); Serial.println(OCR1BH, HEX);
    Serial.print("TIMSK1: "); Serial.println(TIMSK1, HEX);
    Serial.print("TIFR1: "); Serial.println(TIFR1, HEX);

    Serial.print("TCCR2A: "); Serial.println(TCCR2A, HEX);
    Serial.print("TCCR2B: "); Serial.println(TCCR2B, HEX);
}

//-----------------------------------------------------------------------------
// setPwmFrequency
//         mode=1     mode=2     mode=3      mode=4       mode=5        mode=6       mode=7
// pin=5   f=62500/1  f=62500/8  f=62500/64  f=62500/256  f=62500/1024
// pin=6   f=62500/1  f=62500/8  f=62500/64  f=62500/256  f=62500/1024
// pin=9   f=31250/1  f=31250/8  f=31250/64  f=31250/256  f=31250/1024
// pin=10  f=31250/1  f=31250/8  f=31250/64  f=31250/256  f=31250/1024
// pin=3   f=31250/1  f=31250/8  f=31250/32  f=31250/64   f=31250/128   f=31250/256  f=31250/1024
// pin=11  f=31250/1  f=31250/8  f=31250/32  f=31250/64   f=31250/128   f=31250/256  f=31250/1024
//-----------------------------------------------------------------------------
void setPwmFrequency(int pin, byte mode) {
    Serial.print(ack);

    if (mode == 0) {
        analogWrite(pin, 0);
    }
    else {
        analogWrite(pin, 128);
        if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
            if (pin == 5 || pin == 6) {
                TCCR0B = TCCR0B & 0b11111000 | mode;
            }
            else {
                TCCR1B = TCCR1B & 0b11111000 | mode;
            }
        }
        else if (pin == 3 || pin == 11) {
            TCCR2B = TCCR2B & 0b11111000 | mode;
        }
    }
}

//-----------------------------------------------------------------------------
// StartTimer1
// TIFR1 becomes non-zero after
//    overflow*1024/16000000 sec
//-----------------------------------------------------------------------------
void StartTimer1(word overflow) {
    TCCR1A = 0xC0; // Set OC1A on Compare Match
    TCCR1B = 0x05; // prescaler = 1024
    TCCR1C = 0x00; // no pwm output
    //  ICR1L  = 0xC6;
    //  ICR1H  = 0x00;
    OCR1AH = highByte(overflow);
    OCR1AL = lowByte(overflow);
    OCR1BH = 0;
    OCR1BL = 0;
    TIMSK1 = 0x00; // no interrupts

    TCNT1H = 0; // must be written first
    TCNT1L = 0; // clear the counter
    TIFR1 = 0xFF; // clear all flags
}

//-----------------------------------------------------------------------------
// readBatt
//-----------------------------------------------------------------------------
long readBatt() {
    long result;
    // Read 1.1V reference against AVcc
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(2); // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC));
    result = ADCL;
    result |= ADCH << 8;
    result = 1125300L / result; // Back-calculate AVcc in mV
    return result;
}

//-----------------------------------------------------------------------------
// GetLogicSamples
//   read and Tx a buffer-full of bits
//   curPeriod: sample period
//     0:  16 clocks
//     n:  n*SampPerA+SampPerB clocks
//-----------------------------------------------------------------------------

void GetLogicSamples(void) {
    uint8_t d;
    uint8_t* p;

    StartTimer1(0); // no timeout

    if (curPeriod == 0) { // 1Msps
        while (TrigRising == ((PINB & 1) > 0)) {
            d = TCNT1L; // to force read of TCNT1H
            if (TCNT1H > FreeRunTimeout) goto freeRunFast;
        }

        while (TrigRising == ((PINB & 1) == 0)) {
            d = TCNT1L; // to force read of TCNT1H
            if (TCNT1H > FreeRunTimeout) goto freeRunFast;
        }

    freeRunFast:

        digitalWrite(6, HIGH); //>>>>>>>>remove
        for (p = ADCBuffer; p < ADCBuffer + ADCBUFFERSIZE; p++) {
            *p = PINB;
            __asm__("nop\n nop\n nop\n nop\n ");
            __asm__("nop\n nop\n ");
        }
        digitalWrite(6, LOW); //>>>>>>>>remove
    }
    else { // slower than 1Msps
        do { // wait for comparator low
            for (d = 0; d < curPeriod; d++) __asm__("nop");
        } while (TrigRising == ((PINB & 1) > 0));

        do { // wait for comparator high
            for (d = 0; d < curPeriod; d++) __asm__("nop");
        } while (TrigRising == ((PINB & 1) == 0));

    freeRunSlow:

        digitalWrite(6, HIGH); //>>>>>>>>remove
        for (p = ADCBuffer; p < ADCBuffer + ADCBUFFERSIZE; p++) {
            for (d = 0; d < curPeriod; d++) __asm__("nop\n nop\n ");
            *p = PINB;
            __asm__("nop\n nop\n nop\n nop\n ");
            __asm__("nop\n nop\n nop\n nop\n ");
            __asm__("nop\n nop\n nop\n nop\n ");
            __asm__("nop\n ");
        }
        digitalWrite(6, LOW); //>>>>>>>>remove
    }
}

//-----------------------------------------------------------------------------
// GetADCSamples
// read and Tx a buffer-full of samples
// prescaler
//   7 128
//   6 64
//   5 32
//   4 16
//   3 8
//   2 4
//   1 2
//   0 2
// period: sample period
//   0:  16 clocks
//   n:  n*SampPerA+SampPerB clocks
//-----------------------------------------------------------------------------

void GetADCSamples(void) {
    uint8_t d;
    uint8_t* p;
    const int hysteresis = 2;

    initADC();

    ADCSRA = 0x80 + (curPrescaler & 7); // ADC Control and Status Register A
    // 1   Bit 7 – ADEN: ADC Enable
    // 0   Bit 6 – ADSC: ADC Start Conversion
    // 0   Bit 5 – ADATE: ADC Auto Trigger Enable
    // 0   Bit 4 – ADIF: ADC Interrupt Flag
    // 0   Bit 3 – ADIE: ADC Interrupt Enable
    // nnn Bits 2:0 – ADPSn: ADC Prescaler Select [n = 2:0]


    //  StartTimer1(3906); // 0.25 sec for free run
    //  StartTimer1(0x8000); // 4 sec for free run
    //  StartTimer1(0x4000); // 2 sec for free run
    StartTimer1(0); // no timeout

    for (d = 0; d < 10; d++) { // make sure ADC is running
        bitSet(ADCSRA, ADSC); // start ADC conversion
        while (!getBit(ADCSRA, ADIF)); // wait for ADC
        bitSet(ADCSRA, ADIF); // clear the flag
    }

    if (curPeriod == 0) { // 1Msps
        while (TrigRising ? (ADCH >= 0x80 - hysteresis) : (ADCH < 0x80 + hysteresis)) {
            //    while (ADCH >= 0x80-hysteresis) {
            //    while (ADCH < 0x80+hysteresis) {
            d = TCNT1L; // to force read of TCNT1H
            if (TCNT1H > FreeRunTimeout) goto freeRunFast;
            bitSet(ADCSRA, ADSC);
        }

        while (TrigRising ? (ADCH < 0x80 + hysteresis) : (ADCH >= 0x80 - hysteresis)) {
            //    while (ADCH < 0x80+hysteresis) {
            //    while (ADCH >= 0x80-hysteresis) {
            d = TCNT1L; // to force read of TCNT1H
            if (TCNT1H > FreeRunTimeout) goto freeRunFast;
            bitSet(ADCSRA, ADSC);
        }

    freeRunFast:

        digitalWrite(6, HIGH);
        for (p = ADCBuffer; p < ADCBuffer + ADCBUFFERSIZE; p++) {
            *p = ADCH;
            __asm__("nop"); // pad it to 16 instructions
            __asm__("nop"); // pad it to 16 instructions
            bitSet(ADCSRA, ADSC);
        }
        digitalWrite(6, LOW);
    }
    else { // slower than 1Msps
        do { // wait for comparator low
            bitSet(ADCSRA, ADSC); // start ADC conversion
            for (d = 0; d < curPeriod; d++) __asm__("nop");
            d = TCNT1L; // to force read of TCNT1H
            if (TCNT1H > FreeRunTimeout) goto freeRunSlow;
        } while (TrigRising ? (ADCH >= 0x80 - hysteresis) : (ADCH < 0x80 + hysteresis));
        //    } while (ADCH >= 0x80-hysteresis) ;
        //    } while (ADCH < 0x80+hysteresis);

        do { // wait for comparator high
            bitSet(ADCSRA, ADSC); // start ADC conversion
            for (d = 0; d < curPeriod; d++) __asm__("nop");
            d = TCNT1L; // to force read of TCNT1H
            if (TCNT1H > FreeRunTimeout) goto freeRunSlow;
        } while (TrigRising ? (ADCH < 0x80 + hysteresis) : (ADCH >= 0x80 - hysteresis));
        //    } while (ADCH < 0x80+hysteresis) ;
        //    } while (ADCH >= 0x80-hysteresis);

    freeRunSlow:

        bitSet(ADCSRA, ADSC); // start ADC conversion

        digitalWrite(6, HIGH);
        for (p = ADCBuffer; p < ADCBuffer + ADCBUFFERSIZE; p++) {
            for (d = 0; d < curPeriod; d++) __asm__("nop");
            *p = ADCH;
            bitSet(ADCSRA, ADSC); // start ADC conversion
        }
        digitalWrite(6, LOW);
    }
}

//-----------------------------------------------------------------------------
// SendADC
//-----------------------------------------------------------------------------

void SendADC(void) {
    memset((void*)ADCBuffer, 0, sizeof(ADCBuffer));
    noInterrupts();

    if (curAdcPin == 4)
        GetLogicSamples();
    else
        GetADCSamples();

    interrupts();

    Serial.write((int)0xAA);
    Serial.write((int)0xBB);
    Serial.write((int)0xCC);
    Serial.write((uint8_t*)ADCBuffer, ADCBUFFERSIZE);
}

//-----------------------------------------------------------------------------
// setSweep
// set period and ADC prescaler then do a sweep
//-----------------------------------------------------------------------------
void setSweep(int Period, int Prescaler) {
    curPeriod = Period;
    curPrescaler = Prescaler;
    Serial.print(ack);
}

//-----------------------------------------------------------------------------
// setSweep
// set AdcPin and Vref then do a sweep
//-----------------------------------------------------------------------------
void setGain(int AdcPin, int Vref) {
    curAdcPin = AdcPin;
    curVref = Vref;
    Serial.print(ack);
}

//-----------------------------------------------------------------------------
// GetComInteger
// get an int from the serial input
//-----------------------------------------------------------------------------
uint8_t GetComInteger(void) {
    delay(COMMANDDELAY);
    fillBuffer(commandBuffer, COMBUFFERSIZE);
    return atoi(commandBuffer);
}

//-----------------------------------------------------------------------------
// Main routines
// The setup function
//-----------------------------------------------------------------------------
void setup(void) {    // Setup of the microcontroller
  // Open serial port with a baud rate of BAUDRATE b/s
    Serial.begin(BAUDRATE);

    // Clear buffers
    memset((void*)commandBuffer, 0, sizeof(commandBuffer));

    // Activate interrupts
    sei();

    setGain(0, 1);
    initADC();

    Serial.println("ArdOsc ready");
    analogWrite(testSignalPin, 128);

    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    pinMode(6, OUTPUT); //>>>>>>>>remove
}

//-----------------------------------------------------------------------------
// Main routines
// loop
//-----------------------------------------------------------------------------
void loop(void) {
    uint8_t i;

    //  if (TIFR1 != 0) {
    //    Serial.println("*");
    ////    StartTimer1(0x4000); // 2 sec
    ////    TCNT1H = 0; // must be written first
    ////    TCNT1L = 0; // clear the counter
    //    TIFR1 = 0xFF; // clear all flags
    //  }
    //          Serial.print(TCNT1L,HEX);
    //          Serial.print(" ");
    //          Serial.println(TCNT1H,HEX);

    if (Serial.available() > 0) {
        // Read the incoming byte
        char theChar = Serial.read();
        // Parse character
        switch (theChar) {
        case 'U':
            curPrescaler = GetComInteger();
            SendADC();
            break;

        case 'V':      // polling delay in uS
            curPeriod = GetComInteger();
            Serial.print("Setting curPeriod to: ");
            Serial.println(curPeriod);
            Serial.print(ack);
            break;

        case 'F':      // pwm freuency of pwm pin
            setPwmFrequency(testSignalPin, GetComInteger());
            break;

        case 'R':      // Vref
            curVref = GetComInteger();
            initADC();
            Serial.print(ack);
            break;

        case 'A':      // which ADC channel
            curAdcPin = GetComInteger();
            initADC();
            Serial.print(ack);
            break;

        case 'T':      // which trig channel (0 = ADC mux; 1 =  D7)
            TrigRising = GetComInteger() > 0;
            Serial.print(ack);
            break;

        case 'D':     // 'd' for display status
            printStatus();
            Serial.print(ack);
            break;

        case 'B':     // batter voltage
            Serial.print("Vbat: "); Serial.println(readBatt());
            Serial.print(ack);
            break;

        case 'a': setSweep(0, 2); break; // sweep speed 1mS
        case 'b': setSweep(4, 2); break; // sweep speed 2mS
        case 'c': setSweep(14, 3); break; // sweep speed 5mS
        case 'd': setSweep(30, 3); break; // sweep speed 10mS
        case 'e': setSweep(62, 4); break; // sweep speed 20mS
        case 'f': setSweep(158, 4); break; // sweep speed 50mS
        case 'g': setSweep(255, 5); break; // sweep speed 100mS

        case 'j': setGain(0, 1); break; // y-gain 5V
        case 'k': setGain(1, 3); break; // y-gain 0.5V
        case 'l': setGain(2, 3); break; // y-gain 0.1V
        case 'm': setGain(3, 3); break; // y-gain 200mV
        case 'n': setGain(4, 1); break; // Logic

        case 'p': TrigRising = false; Serial.print(ack); break; // trigger fall
        case 'q': TrigRising = true; Serial.print(ack); break; // trigger rise

        case 'r': setPwmFrequency(testSignalPin, 0); break; // test signal Off
        case 's': setPwmFrequency(testSignalPin, 1); break; // test signal 31250Hz 32uS
        case 't': setPwmFrequency(testSignalPin, 2); break; // test signal 3906Hz 256uS
        case 'u': setPwmFrequency(testSignalPin, 3); break; // test signal 976Hz 1024uS
        case 'v': setPwmFrequency(testSignalPin, 4); break; // test signal 488Hz 2048uS
        case 'w': setPwmFrequency(testSignalPin, 5); break; // test signal 244Hz 4096uS
        case 'x': setPwmFrequency(testSignalPin, 6); break; // test signal 122Hz 8192uS
        case 'y': setPwmFrequency(testSignalPin, 7); break; // test signal 30Hz 32768uS

        case 'z': SendADC(); break; // sweep

        default:
            // Display error message
            Serial.print("ERROR: Command not found, it was: ");
            Serial.println(theChar);
        }
    }
}


