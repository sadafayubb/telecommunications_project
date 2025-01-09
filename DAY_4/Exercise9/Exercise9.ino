void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // Start serial communication
  pinMode(A0, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

int sensorValue = analogRead(A0);
float voltage = sensorValue * (5.0 / 1023.0);
float temperature = voltage * 100; // LM35 outputs 10 mV per °C dvs. T = V/0.001 


Serial.print("Temperature: ");
Serial.print(temperature);
Serial.println("°C"); // This works if your code editor saves the file in UTF-8 encoding


}
