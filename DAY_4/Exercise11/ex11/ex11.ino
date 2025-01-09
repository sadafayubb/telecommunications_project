#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define len(x) (sizeof(x) / sizeof(x[0]))
#define numMeasurements 10

float voltage;
float temperature;
int sensorValue;
int count = 0;
float displayTemperature;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int measurements[numMeasurements] = {0};

void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);

    // Display initialization
    lcd.init();       
    lcd.backlight();  
    lcd.clear();
}

void LCD_print_temperature(float temperature) {
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");
    lcd.setCursor(0, 1);
    lcd.print(temperature, 2);
    lcd.print(" C");
}

float mean(const int* measurements, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += measurements[i];
    }
    return sum / (float)size; // Cast to float for proper division
}

void loop() {

    sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1023.0);
    temperature = voltage * 100.0;

    measurements[count] = temperature; // Circular buffer
    count++;

    if (count >= numMeasurements) { 
        displayTemperature = mean(measurements, numMeasurements);
        LCD_print_temperature(displayTemperature);
        count = 0;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    delay(100); 
}
