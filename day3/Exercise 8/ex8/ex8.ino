
const uint8_t PIN_RED = 9;
const uint8_t PIN_GREEN = 5; 
const uint8_t PIN_BLUE = 6;

int intensity = 30;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  pinMode(A0, INPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  analogWrite(PIN_RED, intensity);
  analogWrite(PIN_GREEN, 0);
}

int blueValue(float volt) {
  return (int)(intensity*(1.0-volt/3.3));
}


void loop() {
  // put your main code here, to run repeatedly:

  // We read the value from the A0 pin
  int A0Value = analogRead(A0);

  // The total range of 3.3V is represented as integer values in the range 0,...,1023 (10 bit)
  // Therefore to convert the input value to volts we have to multiply by 3.3/1023
  // The maximum value read at A0 is 671

  float voltage = (float)A0Value * (3.3 / 671.0);

  Serial.print("Voltage: ");
  Serial.print(voltage, 3);
  Serial.println("V");


  analogWrite(PIN_BLUE, blueValue(voltage));

}
