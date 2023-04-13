// GPS modul NEO-6M

// připojení potřebných knihoven
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
// nastavení propojovacích pinů
#define TX 3
#define RX 2
// inicializace GPS a komunikace po softwarové sériové lince
TinyGPSPlus gps;
SoftwareSerial swSerial(RX, TX);

void setup() {
  // zahájení komunikace po sériové lince
  Serial.begin(9600);
  // zahájení komunikace s GPS modulem po softwarové sériové lince
  swSerial.begin(9600);

  delay(1000);  

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}

void loop() {
  GetGPS();
}

void GetGPS(){
  while (swSerial.available() > 0){
    char c = swSerial.read();
    // Serial.print(c);
    gps.encode(c);
  }

  // Serial.println(gps.satellites.value());

  if (gps.satellites.value() > 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("LAT="); Serial.print(gps.location.lat(), 6);
    Serial.print("LNG="); Serial.println(gps.location.lng(), 6);
  }
}