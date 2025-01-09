#include <LiquidCrystal_I2C.h>
#define len(x) = sizeof(x) / sizeof(x[0])
#define numMeasurements 10

float voltage;
float temperature;
int sensorValue;
int count = 0;

int measurements[numMeasurements];

void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
}


float mean(const int[] measurements) {
  int sum = 0;
  int n = len(measurements);
  for (int i=0; i < n; i++) {
    sum += measurements[i];
  }
  return sum / n;



}


void loop() {

    count++

    sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1023.0);
    temperature = voltage * 100.0; // LM35 outputs 10 mV per °C

    measurements[count-1] = temperature;



    if (count == numMeasurements) { 
      count = 0;

    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C"); // This works if your code editor saves the file in UTF-8 encoding

    delay(100);



}
