#include "TemperatureSensor.h"

// Function to read analog input and convert to voltage
float TemperatureSensor::readVoltage() {
    int sensorValue = analogRead(pin);            // Read analog input
    return (inputVoltage / 1023.0) * sensorValue; // Convert to voltage
}

// Function to convert voltage to temperature
float TemperatureSensor::convertToTemperature() {
    float voltage = readVoltage();
    if (sensorType == "TMP36") {
        // TMP36: Temp (°C) = (Vout - 500mV) / 10mV
        return (voltage - 0.5) * 100.0;
    } else if (sensorType == "LM35") {
        // LM35: Temp (°C) = Vout / 10mV
        return voltage * 100.0;
    } else {
        // Unknown sensor type
        return -999.0; // Error value
    }
}
