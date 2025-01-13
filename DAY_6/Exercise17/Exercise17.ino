#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "iPhone Sadaf"; // Replace with your Wi-Fi name
const char* pass = "daddy1234"; // Replace with your Wi-Fi password
WiFiClient client;

unsigned long channelID = 2808278; //your TS channal
const char * APIKey = "62K990TJS8H1POGA"; //your TS API
const char* server = "api.thingspeak.com";
const int postDelay = 20 * 1000; //post data every 20 seconds

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  
  delay(3000);
  
  Serial.println("");
  Serial.println("WiFi connected to ");
  Serial.println(WiFi.SSID());
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

float data; //measured data

void loop() {
  data = 42.0;
  
  // Get RSSI (signal strength)
  //int rssi = WiFi.RSSI();


  ThingSpeak.begin(client);
  client.connect(server, 80); //connect(URL, Port)
  ThingSpeak.setField(1, data); //set data on the X graph
  // Set RSSI to field 1
  // ThingSpeak.setField(1, rssi);
  
  ThingSpeak.writeFields(channelID, APIKey); //post everything to TS
  Serial.println(data);
  client.stop();
  delay(postDelay); //wait and then post again
}

