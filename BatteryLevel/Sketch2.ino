const int FETpin = 3;
const int interruptPin = 2;
int value = 0;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(FETpin, OUTPUT);
    analogWrite(FETpin, 0);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), raise, FALLING);
    Serial.println(readVcc());
}

void loop() {
    // put your main code here, to run repeatedly:
    
}

void raise() {
    value += 50;
    if (value > 250) value = 0;
    Serial.println(value);
    analogWrite(FETpin, value);
}

//read internal voltage
long readVcc() {
    long result;
    // Read 1.1V reference against AVcc
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(2); // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC));
    result = ADCL;
    result |= ADCH << 8;
    result = 1126400L / result; // Back-calculate AVcc in mV
    return result;
}
