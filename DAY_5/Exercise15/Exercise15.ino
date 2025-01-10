#include "TemperatureSensor.h"

// Create a TemperatureSensor object
TemperatureSensor tempSensor("LM35", 5.0, A0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Start serial communication
  pinMode(A0, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  float temperature = tempSensor.convertToTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // Wait 1 second

}
