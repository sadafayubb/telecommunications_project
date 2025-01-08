// Define pins for RGB LED
const int redPin = 8;    // Pin connected to the red channel
const int greenPin = 7;  // Pin connected to the green channel
const int bluePin = 6;   // Pin connected to the blue channel

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // Start serial communication

  // Set RGB pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

   if (Serial.available() > 0) {
    // Read and parse the three integers from the input string
    int redValue = Serial.parseInt();   // Parse the first integer
    int greenValue = Serial.parseInt(); // Parse the second integer
    int blueValue = Serial.parseInt();  // Parse the third integer

    // Constrain values to 0-255 to avoid invalid input
    redValue = constrain(redValue, 0, 255);
    greenValue = constrain(greenValue, 0, 255);
    blueValue = constrain(blueValue, 0, 255);

     // Write the values to the RGB LED
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);

     // Debugging output
    Serial.print("Red: ");
    Serial.print(redValue);
    Serial.print(", Green: ");
    Serial.print(greenValue);
    Serial.print(", Blue: ");
    Serial.println(blueValue);
  }

}
