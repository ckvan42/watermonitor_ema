//
// Created by fadi on 2022-03-12.
//

#include "../../include/cpp_old/water_Pressure.hpp"
#include "Arduino.h"

Water_Pressure_Sensor::Water_Pressure_Sensor(int pin, string name) : Sensor(pin, name, "Water_pressure") {
}

void Water_Pressure_Sensor::initializeSensor() {
}

float Water_Pressure_Sensor::takeMeasurement() {
    /*
    //Connect sensor to Analog 0
    V = analogRead(0) * 5.00 / 1024;     //Sensor output voltage
    P = (V - OffSet) * 400;             //Calculate water pressure

    Serial.print("Voltage:");
    Serial.print(V, 3);
    Serial.println("V");

    Serial.print(" Pressure:");
    Serial.print(P, 1);
    Serial.println(" KPa");
    Serial.println();

    this->_value = P;
    delay(500);
    */
    return this->_value;
}