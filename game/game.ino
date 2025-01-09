#include <LiquidCrystal.h>

#define LEN(x) (sizeof(x) / sizeof((x)[0]))

const uint8_t pinButton = 13;
const uint8_t pins[5] = {6, 7, 8, 9, 10};
bool pressed = false;
int count = 0;
unsigned long previousMillis = 0;
unsigned long flashingSpeed = 500;
int wins = 0;

// Initialize the library with the numbers of the interface pins
// RS, E, D4, D5, D6, D7
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
  for (int i = 4; i >=0; i--) {
    digitalWrite(pins[i], HIGH);
    delay(speed);
    digitalWrite(pins[i], LOW);
  }
}

void lose() {
  allLEDsOff();
  delay(1000);
}

void allLEDsOff() {
  for (int i = 0; i < LEN(pins); i++) {
    digitalWrite(pins[i], LOW);
  }
}

void LCD_print_pin(int pin) {
  lcd.setCursor(0, 0);
  lcd.print("Light number: ");
  lcd.setCursor(0, 1);
  lcd.print(pin);
}

void setup() {
  Serial.begin(115200);
  pinMode(pinButton, INPUT_PULLUP);
  for (int i = 0; i < LEN(pins); i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  lcd.begin(16, 2);
  lcd.clear();
  randomSeed(analogRead(A0));
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= flashingSpeed) {
    previousMillis = currentMillis;

    if (wins > 8) {
      count = random(1, LEN(pins) +1);
      flashingSpeed=500;
    } else {
      count++;
      if (count > LEN(pins)) {
        count = 1;
      }
    }

    allLEDsOff();
    digitalWrite(pins[count - 1], HIGH);
  }

  if (!digitalRead(pinButton)) {
    pressed = true;
  }
  if (pressed && digitalRead(pinButton)) {
    // Button press logic
    
    LCD_print_pin(count);
    if (count == 3) {
      win();
      if (wins >= 10) {
        wins = 0;
        flashingSpeed = 500;
      }
    } else {
      lose();
    }
    pressed = false;
    delay(50);
  }
}
