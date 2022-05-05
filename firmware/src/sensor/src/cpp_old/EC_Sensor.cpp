//
// Created by jordan on 2022-03-25.
//

#include "EC_Sensor.hpp"
#include "Arduino.h"

using namespace std;

EC_Sensor::EC_Sensor(int pin, string name) : Sensor(pin, name, "ec") {

    this->_ecvalue = 0.0;
    this->_kvalue = 1.0;
}

void EC_Sensor::initializeSensor() {


}

float EC_Sensor::takeMeasurement() {
    float voltage;
    voltage = analogRead(this->_readingPin) / 1023.0 * 5000;   // read the voltage
    this->_value = this->convert(voltage);  // convert voltage to pH with temperature compensation

    return this->_value;
}

float EC_Sensor::convert(float voltage)
{
    this->_ecvalueRaw = 1000*voltage/RES2/ECREF*this->_kvalue*10.0;
    this->_ecvalue = this->_ecvalueRaw / (1.0+0.0185*(_temperature-25.0));  //temperature compensation
    return this->_ecvalue;
}


