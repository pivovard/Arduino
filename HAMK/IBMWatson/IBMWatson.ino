/*
MKR1000 connecting to IBM Watson IoT Platform
Based on documentation and "recipes" on IBM Bluemix
https://www.ibm.com/cloud-computing/bluemix/watson
Timo Karppinen 19.2.2017
Modified for testing SPI microphone board Digilent PmodMIC3
Please connect
MKR1000 - PmodMIC3
GND - 5 GND
Vcc - 6 Vcc
9 SCK - 4 SCK
10 MISO - 3 MISO
1 - 1 SS
a sound indicator LED
6 - 220 ohm - LED or the onboard LED
Timo Karppinen 13.9.2017
Added calculated sensor data
Loop timing redone
14.11.2017
*/
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <MQTTClient.h> // The Gaehwiler mqtt library

// WLAN
//char ssid[] = "HAMKvisitor"; // your network SSID (name)
//char pass[] = "hamkvisitor"; // your network password (use for WPA)

char ssid[] = "TW-EAV510-BREAAA"; // your network SSID (name)
char pass[] = "56410098"; // your network password (use for WPA)

// IBM Watson
// Your organization and device needs to be registered in IBM Watson IoT Platform.
// Instruction for registering on page
// https://internetofthings.ibmcloud.com/#

//char *client_id = "d:<your Organization ID>:<your Device Type>:<your Device ID>";
char *client_id = "d:t434r5:A_MKR1000:ard666";
char *user_id = "use-token-auth"; // telling that authentication will be done with token
char *authToken = "TgTYeuTJdj3(+XDUsG"; // Your IBM Watson Authentication Token

//char *ibm_hostname = “<your-org-id.messaging.internetofthings.ibmcloud.com>”;
char *ibm_hostname = "t434r5.messaging.internetofthings.ibmcloud.com";

// sensors and LEDS
const int ainputPin = A0;
const int soundLEDPin = 6; // must be a pin that supports PWM. 0...8 on MKR1000
// PModMIC3
const int mic3CS = 1; // chip select for MIC3 SPI communication
int sound12bit = 0; // 12 bit sound level value [ 0000 nnnn nnnn nnnn ] nnn.. = two's complement!
int soundByte1 = 0; // 8 bit data from mic board
int soundByte2 = 0; // 8 bit data from mic board
int sound32bit = 0; // in MKR1000 board SAMD21 processor the int is 32 bit two's complement
int sound8bit = 0;
const int numSamples = 100;
int sound8bitA[numSamples];
int sampleIndex = 0;
int soundSum = 0;
int soundLevel = 0; // 8 bit positive number from 0 to 255
int blinkState = 0;
/*use this class if you connect using SSL
* WiFiSSLClient net;
*/
WiFiClient net;
MQTTClient MQTTc;
unsigned long lastSampleMillis = 0;
unsigned long previousWiFiBeginMillis = 0;
unsigned long lastWatsonMillis = 0;
unsigned long lastPrintMillis = 0;
void setup()
{
 pinMode(mic3CS, OUTPUT);
 digitalWrite(mic3CS, HIGH); // for not communicating with MIC3 at the moment
 Serial.begin(9600);
 delay(2000); // Wait for wifi unit to power up
 WiFi.begin(ssid, pass);
 delay(5000); // Wait for WiFi to connect
 Serial.println("Connected to WLAN");
 printWiFiStatus();

 /*
 client.begin("<Address Watson IOT>", 1883, net);
 Address Watson IOT: <WatsonIOTOrganizationID>.messaging.internetofthings.ibmcloud.com
 Example:
 client.begin("iqwckl.messaging.internetofthings.ibmcloud.com", 1883, net);
 */
 MQTTc.begin(ibm_hostname, 1883, net); // Cut for testing without Watson
 connect();
 SPI.begin();
 // Set up the I/O pins
 pinMode(mic3CS, OUTPUT);
 pinMode(soundLEDPin, OUTPUT);
// Initializing the sound sample array to zero.
for(int i = 0; i < numSamples; i++)
{
 sound8bitA[i] = 0;
}
}

void loop() {
 MQTTc.loop(); // Cut for testing without Watson
 MQTTc.publish("iot-2/evt/SoundTwo/fmt/json", "{\"Sound level sensors\":\"Sounds from field, too\",\"SoundMean\":\"" + String(soundLevel)+"\", \"SoundStreight\": \"" + String(sound8bit)+"\"}");
 delay(500);
 return;
 
 // opening and closing SPI communication for reading MIC3
 if(millis() - lastSampleMillis > 1000/numSamples)
 {
 lastSampleMillis = millis();
 SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
 digitalWrite(mic3CS, LOW);

 soundByte1 = SPI.transfer(0x00);
 soundByte2 = SPI.transfer(0x00);

 digitalWrite(mic3CS, HIGH);
 SPI.endTransaction();
 soundByte1 = soundByte1 << 8;
 sound12bit = soundByte1 | soundByte2;
 sound32bit = sound12bit << 22; // 22 bits to the left to create 32 bit two's complement
 sound8bit = sound32bit / 16777216; // 2 exp24 = 16 7777 216 means shifting 24 bits left without shifting the sign!
 soundSum = soundSum - sound8bitA[sampleIndex]; // subtract the oldest sample
 sound8bitA[sampleIndex] = sqrt(sound8bit * sound8bit); // reading the | latest sample |
 soundSum = soundSum + sound8bitA[sampleIndex]; //add the latest sample
 analogWrite(soundLEDPin, sound8bitA[sampleIndex]); // blink the LED with intensity = | sound sample |
 sampleIndex = sampleIndex + 1;
 if(sampleIndex >= numSamples)
 {
 sampleIndex = 0;
 }
 soundLevel = soundSum / numSamples;
 }
 // Print on serial monitor once in 1000 millisecond
 if(millis() - lastPrintMillis > 1000)
 {
 Serial.print("Sound32bit ");
 Serial.print(sound32bit);
 Serial.print(" Sound8bit ");
 Serial.print(sound8bit);
 Serial.print(" SoundLevel ");
 Serial.println(soundLevel);
 lastPrintMillis = millis();
 }


 // publish a message every 30 second.
 if(millis() - lastWatsonMillis > 30000)
 {
 Serial.println("Publishing to Watson...");
 if(!MQTTc.connected()) { // Cut for testing without Watson
 connect(); // Cut for testing without Watson
 } // Cut for testing without Watson
 lastWatsonMillis = millis();
 //Cut for testing without Watson
 MQTTc.publish("iot-2/evt/SoundTwo/fmt/json", "{\"Sound level sensors\":\"Sounds from field, too\",\"SoundMean\":\"" + String(soundLevel)+"\", \"SoundStreight\": \"" + String(sound8bit)+"\"}");

 }

 delay(1);

// end of loop
}

void connect()
{
 Serial.print("checking WLAN...");
 while (WiFi.status() != WL_CONNECTED)
 {
 Serial.print("."); // printing a dot every half second
 if ( millis() - previousWiFiBeginMillis > 5000) // reconnecting
 {
 previousWiFiBeginMillis = millis();
 WiFi.begin(ssid, pass);
 delay(5000); // Wait for WiFi to connect
 Serial.println("Connected to WLAN");
 printWiFiStatus();
 }
 delay(500);

 }
 /*
 Example:
 MQTTc.connect("d:iqwckl:arduino:oxigenarbpm","use-token-auth","90wT2?a*1WAMVJStb1")

 Documentation:
 https://console.ng.bluemix.net/docs/services/IoT/iotplatform_task.html#iotplatform_task
 */

 Serial.print("\nconnecting Watson with MQTT....");
 // Cut for testing without Watson
 while (MQTTc.connect(client_id,user_id,authToken))
 {
 Serial.print(".");
 delay(3000);
 break;
 }
 Serial.println("\nconnected!");
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
 Serial.print("incoming: ");
 Serial.print(topic);
 Serial.print(" - ");
 Serial.print(payload);
 Serial.println();
}

void printWiFiStatus() {
 // print the SSID of the network you're attached to:
 Serial.print("SSID: ");
 Serial.println(WiFi.SSID());
 // print your WiFi shield's IP address:
 IPAddress ip = WiFi.localIP();
 Serial.print("IP Address: ");
 Serial.println(ip);
 // print the received signal strength:
 long rssi = WiFi.RSSI();
 Serial.print("signal strength (RSSI):");
 Serial.print(rssi);
 Serial.println(" dBm");
}
