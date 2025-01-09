float lowToMediumBoundary = 10.0;
float mediumToHighBoundary = 28.5;
float voltage;
float temperature;
int sensorValue;

enum temperatureState {Low = 0, Medium = 1, High = 2};
const uint8_t PIN_GREEN = 5;
const uint8_t PIN_YELLOW = 6;
const uint8_t PIN_RED = 7;

enum temperatureState state = Low;
enum temperatureState stateCache = Low;
bool stateChanged = false;

enum temperatureState getTemperatureState(float degrees) {
    if (degrees < lowToMediumBoundary)
        return Low;
    else if (degrees < mediumToHighBoundary)
        return Medium;
    else
        return High;
}

void allLEDsOff() {
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_YELLOW, LOW);
    digitalWrite(PIN_RED, LOW);
}

void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_YELLOW, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    allLEDsOff();
}

void loop() {
    sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1023.0);
    temperature = voltage * 100.0; // LM35 outputs 10 mV per °C

    state = getTemperatureState(temperature);

    if (stateCache != state) {
        stateChanged = true;
    }

    stateCache = state;

    if (stateChanged) {
        allLEDsOff();
        if (state == Low) digitalWrite(PIN_GREEN, HIGH);
        if (state == Medium) digitalWrite(PIN_YELLOW, HIGH);
        if (state == High) digitalWrite(PIN_RED, HIGH);
    }

    stateChanged = false;

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C"); // This works if your code editor saves the file in UTF-8 encoding

    delay(500);
}
