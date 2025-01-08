/* Define pin numbers for LEDs
const int greenPin = 5;
const int yellowPin = 6;
const int redPin = 7;
*/

// Define pin numbers for the 3 LEDs
const int ledPins[] = {5, 6, 7}; // Pins 2, 3, and 4 for LEDs

int counter = 0;  // Counter variable

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  /*  // Initialize LED pins as output
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  */

  // Initialize LED pins as output
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  //Serial.println("This is my first Arduino program!"); 
}

/*
// Function to handle Green light ON
void GreenLightOn() {
  digitalWrite(greenPin, HIGH);  // Turn on green light
  digitalWrite(yellowPin, LOW);  // Turn off yellow light
  digitalWrite(redPin, LOW);     // Turn off red light
  Serial.println("GO!");         // Send instruction for drivers
}

// Function to handle Yellow light ON
void YellowLightOn() {
  digitalWrite(greenPin, LOW);   // Turn off green light
  digitalWrite(yellowPin, HIGH); // Turn on yellow light
  digitalWrite(redPin, LOW);     // Turn off red light
  Serial.println("SLOW DOWN!");  // Send instruction for drivers
}

// Function to handle Red light ON
void RedLightOn() {
  digitalWrite(greenPin, LOW);   // Turn off green light
  digitalWrite(yellowPin, LOW);  // Turn off yellow light
  digitalWrite(redPin, HIGH);    // Turn on red light
  Serial.println("STOP!");       // Send instruction for drivers
}
*/

void loop() {
  // put your main code here, to run repeatedly:
  // Loop through each LED pin
  for (int i = 0; i < 3; i++) {
    // Set LED state according to the current binary counter value
    digitalWrite(ledPins[i], (counter >> i) & 1); // shifts the counter to the right by i positions, effectively isolating the bit at position i
  }

  // Print the current counter value to the serial monitor
  Serial.print("Counter: ");
  Serial.println(counter, BIN);  // Print in binary format

  delay(1000);  // Wait for 1 second
  
  // Increment counter and reset to 0 after reaching 7
  counter = (counter + 1) % 8;  // 8 is the modulus to reset at 8 (binary 1000)
  
}
