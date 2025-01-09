/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/


const uint8_t ledPin = 6; //e.g. D6
const int timeUnit = 500; //e.g. 500
int shortTime = timeUnit / 4;
const int letterGap = 800; // Gap between letters (ms)

// Morse code dictionary (A-9)
const char* morseCode[] = {
    ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",   // A-I
    ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.", // J-R
    "...",  "-",    "..-",  "...-", ".--",  "-..-", "-.--", "--.."  // S-Z
    ".----", "..---", "...--", "....-", "....", "-....", "--...", "---..", "----.", "-----" // 0-11
};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
}

void dot() {
    digitalWrite(ledPin, HIGH);
    delay(shortTime); // Short blink for dot
    digitalWrite(ledPin, LOW);
    delay(shortTime); // Gap between blinks
}

void dash() {
    digitalWrite(ledPin, HIGH);
    delay(timeUnit); // Long blink for dash
    digitalWrite(ledPin, LOW);
    delay(shortTime); // Gap between blinks
}


// Function to convert character to Morse
const char* charToMorse(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        // Convert uppercase letters to indices (0-25)
        return morseCode[letter - 'A'];
    } else if (letter >= 'a' && letter <= 'z') {
        // Convert lowercase letters to uppercase and then to indices (0-25)
        return morseCode[letter - 'a'];
    } else if (letter >= '0' && letter <= '9') {
        // Convert numbers to indices (26-35)
        return morseCode[letter - '0' + 26];
    } else {
        // Unsupported characters
        return ""; // Return empty string for unsupported characters (e.g., spaces)
    }
}


// Function to output Morse code for a single letter
void morseLetter(const char* code) {
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '.') {
            dot();
        } else if (code[i] == '-') {
            dash();
        }
    }
    delay(letterGap); // Gap between letters
}

// the loop function runs over and over again forever
void loop() {
  // Word to Morse
  const char* word = "SOS"; // Replace with your name

  for (int i = 0; word[i] != '\0'; i++) {
      char letter = word[i];
      const char* morse = charToMorse(letter); // Convert to Morse code
      if (morse[0] != '\0') {                  // Only process valid characters
          morseLetter(morse);
      }
  }

  delay(5000); // Pause before repeating
}
