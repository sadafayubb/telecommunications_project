
const uint8_t pinButton = 6;
const uint8_t pinLED = 7;


bool ON = false;
bool buttonDown = false;
bool pressed = false;

void setup() {
  Serial.begin(115200);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  if (!digitalRead(pinButton)) {
    pressed = true;
  }

  if (pressed && digitalRead(pinButton)) {
    if (ON) {
      ON = false;
      digitalWrite(pinLED, LOW);
    } else {
      ON = true;
      digitalWrite(pinLED, HIGH);
    }
    pressed = false;
    delay(5);  // To prevent button rebounce
  }


}
