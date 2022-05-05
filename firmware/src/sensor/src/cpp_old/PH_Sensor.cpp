//
// Created by User on 2022-03-11.
//

#include "PH_Sensor.hpp"
#include "Arduino.h"

#include <string>

using namespace std;

PH_Sensor::PH_Sensor(int pin, string name) : Sensor(pin, name, "ph") {
    this->_phValue        = 7.0;
    this->_acidVoltage    = 2032.44;
    this->_neutralVoltage = 1500.0;
}

void PH_Sensor::initializeSensor() {
//    ph->begin();
}

float PH_Sensor::takeMeasurement() {
    float voltage;
    voltage = analogRead(this->_readingPin) / 1023.0 * 5000;   // read the voltage
    this->_value = this->convert(voltage);  // convert voltage to pH with temperature compensation

    return this->_value;
}

float PH_Sensor::convert(float voltage)
{
    float slope = (7.0 - 4.0) / ((this->_neutralVoltage-1500.0) / 3.0 - (this->_acidVoltage-1500.0)/3.0);  // two point: (_neutralVoltage,7.0),(_acidVoltage,4.0)
    float intercept =  7.0 - slope*(this->_neutralVoltage-1500.0)/3.0;
    this->_phValue = slope * (voltage-1500.0) / (3.0 + intercept);  //y = k*x + b
    return _phValue;
}
