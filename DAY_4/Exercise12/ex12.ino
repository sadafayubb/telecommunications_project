#include <LiquidCrystal.h>

#define LEN(x) (sizeof(x) / sizeof((x)[0]))

const uint8_t pinButton = 13;
const uint8_t pins[5] = {6, 7, 8, 9, 10};
bool pressed = false;
int count = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long flashingSpeed = 500;
int wins = 0;

// Initialize the LiquidCrystal object.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void win() {
  int speed = 100;
  wins += 1;
  flashingSpeed = (flashingSpeed * 4.0) / 5.0;
  for (int i = 0; i < LEN(pins); i++) {
    digitalWrite(pins[i], HIGH);
    delay(speed);
    digitalWrite(pins[i], LOW);
  }
  for (int i = 4; i >= 0; i--) {
    digitalWrite(pins[i], HIGH);
    delay(speed);
    digitalWrite(pins[i], LOW);
  }
  LCD_print_wins();
}

void lose() {
  allLEDsOff();
  delay(1000);
  LCD_print_wins();
}

void allLEDsOff() {
  for (int i = 0; i < LEN(pins); i++) {
    digitalWrite(pins[i], LOW);
  }
}

void LCD_print_pin(int pin) {
  lcd.setCursor(0, 0);
  lcd.print("Light number:   "); // Clear the rest of the line
  lcd.setCursor(0, 0);
  lcd.print("Light number: ");
  lcd.setCursor(0, 1);
  lcd.print(pin);
  lcd.print("   "); // Clear any residual characters
}

void LCD_print_wins() {
  lcd.setCursor(0, 0);
  lcd.print("Wins:          "); // Clear the rest of the line
  lcd.setCursor(0, 0);
  lcd.print("Wins: ");
  lcd.setCursor(0, 1);
  lcd.print(wins);
  lcd.print("   "); // Clear any residual characters
}

void setup() {
  Serial.begin(115200);
  pinMode(pinButton, INPUT_PULLUP);

  // Initialize all LEDs in a little for loop
  for (int i = 0; i < LEN(pins); i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  lcd.begin(16, 2);
  lcd.clear();

  LCD_print_wins();

  // Set the random seed using the analog signal from A0
  randomSeed(analogRead(A0));
}

void loop() {
  // We can use millis() to create a delay that does not interfere with the outer loop.
  // This ensure that we can still check the button press.
  currentMillis = millis();

  // Then we can create the delay 'flashingSpeed' by keeping track of how much time has elapsed
  if (currentMillis - previousMillis >= flashingSpeed) {
    previousMillis = currentMillis; // Update the previous elapsed time

    if (wins >= 8) { // If the player has more than eight wins, use random counts (LED pins)
      count = random(1, LEN(pins) + 1);
      flashingSpeed = 350;  // And we also make the speed slower because the randomness is hard enough
    } else {
      count++;
      if (count > LEN(pins)) {  // Reset the count if we have visited all LEDS
        count = 1;
      }
    }

    // Turn onn the correct LED and turn the others off
    allLEDsOff();
    digitalWrite(pins[count - 1], HIGH);
  }


  // This logic is partly taken from the previous button exercise
  if (!digitalRead(pinButton)) {
    pressed = true;
  }
  if (pressed && digitalRead(pinButton)) {
    // Button press logic (happens at button press)
    LCD_print_pin(count);  // Prints which led was lid when button was pressed
    if (count == 3) {
      win();
      if (wins >= 10) {  // If we reach 10 wins the game is reset
        wins = 0;
        flashingSpeed = 500;
        LCD_print_wins();  // And we update the wins
      }
    } else {
      lose();
    }
    pressed = false;
    delay(50);
  }
}
