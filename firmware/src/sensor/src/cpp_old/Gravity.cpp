//
// Created by fadi on 2022-03-12.
//

#include "../../include/cpp_old/Gravity.hpp"
#include "libs/DFRobot_EC10.h"
#include <libs/EEPROM.h>

#include <string>

using namespace std;

#define EC_PIN A1
float voltage, ecValue, temperature = 25;

Gravity::Gravity(int pin, string name, DFRobot_EC10 *ec) : Sensor(pin, name, "Gravity") {
    this->ec = ec;
}

void Gravity::initializeSensor() {
    ec->begin();
}

float Gravity::takeMeasurement() {
    /*
    static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U) {  //time interval: 1s
        timepoint = millis();
        voltage = analogRead(EC_PIN) / 1024.0 * 5000;  // read the voltage
//        Serial.print("voltage:");
//        Serial.print(voltage);
        //temperature = readTemperature();  // read your temperature sensor to execute temperature compensation
        ecValue = ec->readEC(voltage, temperature);  // convert voltage to EC with temperature compensation
//        Serial.print("  temperature:");
//        Serial.print(temperature, 1);
//        Serial.print("^C  EC:");
//        Serial.print(ecValue, 1);
//        Serial.println("ms/cm");
    }
    ec->calibration(voltage, temperature);  // calibration process by Serail CMD
     */
    return this->_value;
}

float readTemperature() {
    //add your code here to get the temperature from your temperature sensor
}