//
// Created by User on 2022-03-14.
//

#include "../../include/cpp_old/TestSensor.hpp"
#include "Arduino.h"


    void TestSensor::initializeSensor() {
    }

    float TestSensor::takeMeasurement() {
        this->_value = analogRead(this->_readingPin);

        return this->_value;
    }

