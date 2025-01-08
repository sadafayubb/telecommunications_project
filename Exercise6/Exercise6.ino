// Define pin numbers for the 5 LEDs
const int ledPins[] = {5, 6, 7, 8, 9}; // Pins 2, 3, and 4 for LEDs
char incomingChar;
int ledIndex;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); 

  
  // Initialize LED pins as output
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Turn off all LEDs initially
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

   // Check if data is available on the serial input
  if (Serial.available() > 0) {

    incomingChar = Serial.read();

    // Convert to lowercase for case-insensitivity
    incomingChar = tolower(incomingChar);

    // Light the corresponding LED if the character is a, b, c, d, or e
    if (incomingChar >= 'a' && incomingChar <= 'e') {
      int ledIndex = incomingChar - 'a'; // Calculate the index (0-4)
      digitalWrite(ledPins[ledIndex], HIGH);
    } else {
      // Turn off all LEDs if unknown character
      for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], LOW);
      }
    }

  }

}
