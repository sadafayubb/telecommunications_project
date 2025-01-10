// ExampleHeader.h
// This is known as a header guard, in short, it ensure that no file is included more than once
// as this would cause issues with "multiple definitions" of the same class/ function

#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

#include <Arduino.h>

// TemperatureSensor class definition
class TemperatureSensor {
private:
    String sensorType;   // Type of sensor, e.g., TMP36 or LM35
    float inputVoltage;  // Input voltage (e.g., 5.0V or 3.3V)
    int pin;             // Analog pin the sensor is connected to

public:
    // Constructor
    TemperatureSensor(String type, float voltage, int analogPin)
        : sensorType{type}, inputVoltage{voltage}, pin{analogPin} {}

    // initializes the private members (inputVoltage, pin) with values passed to the constructor.    

    // Function to read analog input and convert to voltage
    float readVoltage();

    // Function to convert voltage to temperature
    float convertToTemperature();
};

#endif // TEMPERATURESENSOR_H_