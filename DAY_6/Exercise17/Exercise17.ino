#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266mDNS.h>        // Include the mDNS library
#include <ThingSpeak.h>


ESP8266WiFiMulti wifiMulti;
// Create an instance of the server
ESP8266WebServer server_(80);


void handleRoot();  
void handleLED();  
void handleNotFound();


const uint8_t led = 4;
const uint8_t temperatureSensor = A0;
const char* ssid = "iPhone von Frederik"; // Replace with your Wi-Fi name
const char* pass = "abcdefg123456"; // Replace with your Wi-Fi password
WiFiClient client;

unsigned long channelID = 2808278; //your TS channal
const char * APIKey = "62K990TJS8H1POGA"; //your TS API
const char* server = "api.thingspeak.com";
const int postDelay = 20 * 1000; //post data every 20 seconds

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  
  pinMode(temperatureSensor, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led,1);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected to ");
  Serial.println(WiFi.SSID());
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  server_.on("/", HTTP_GET, handleRoot);
  server_.on("/LED", HTTP_POST, handleLED);
  server_.onNotFound(handleNotFound);
    
  // Start the server
  server_.begin();
  Serial.println("Server started"); 

}

float data; //measured data

void loop() {

  server_.handleClient();

  int sensorValue = analogRead(temperatureSensor);
  float voltage = sensorValue * (3.3 / 1023.0);
  float temperature = voltage * 100; // LM35 outputs 10 mV per °C dvs. T = V/0.001 

  Serial.print("Temperature: ");
  Serial.println(temperature);

  //data = 42.0;

  // Get RSSI (signal strength)
  int rssi = WiFi.RSSI();
  bool LED_on = digitalRead(led);


  ThingSpeak.begin(client);
  client.connect(server, 80); //connect(URL, Port)
  ThingSpeak.setField(1, rssi); //set rssi on the 1st field
  ThingSpeak.setField(2, LED_on); //set LED_on on the 2nd field
  ThingSpeak.setField(3, temperature); //set temperature on the 3rd field


  // Set RSSI to field 1
  // ThingSpeak.setField(1, rssi);
  
  ThingSpeak.writeFields(channelID, APIKey); //post everything to TS
  Serial.println(rssi);
  client.stop();

  Serial.print("RSSI: ");
  Serial.println(rssi);
  Serial.print("LED ON: ");
  Serial.println(LED_on);

  delay(postDelay); //wait and then post again
}



void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server_.send(200, "text/html", "<html><title>Internet of Things - Demonstration</title><meta charset=\"utf-8\" \/> \ 
      </head><body><h1>Velkommen til denne WebServer</h1> \ 
      <p>Internet of Things (IoT) er \"tingenes Internet\" - dagligdags ting kommer på nettet og får ny værdi. Det kan løse mange udfordringer.</p> \
      <p>Her kommunikerer du med en webserver på en lille microcontroller af typen Arduino, som i dette tilfælde styrer en digital udgang, som du så igen kan bruge til at styre en lampe, en ventilator, tænde for varmen eller hvad du lyster</p> \
      <p>Klik på nedenstående knap for at tænde eller slukke LED på port D2</p> \
      <form action=\"/LED\" method=\"POST\" ><input type=\"submit\" value=\"Skift tilstand på LED\" style=\"width:500px; height:100px; font-size:24px\"></form> \
      <p>Med en Arduino ESP8266 kan du lave et have a sjove projekter</p> \
      <p>Vil du vide mere: Kig på hjemmesiden for uddannelsen : <a href=\"www.dtu.dk/net\">Netværksteknologi og it</a></p> \
      </body></html>");
}

void handleLED() {                          // If a POST request is made to URI /LED
  digitalWrite(led,!digitalRead(led));      // Change the state of the LED
  server_.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server_.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound(){
  server_.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
  


