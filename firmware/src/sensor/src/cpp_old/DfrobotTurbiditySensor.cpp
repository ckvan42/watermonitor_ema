//
// Created by User on 2022-03-14.
//

#include "../../include/cpp_old/DfrobotTurbiditySensor.hpp"
#include "Arduino.h"

void DfrobotTurbiditySensor::initializeSensor() {
}

float DfrobotTurbiditySensor::takeMeasurement() {
    /*
    int sensorValue = analogRead(this->_readingPin);// read the input on analog pin
    float voltage = (float)(sensorValue *
                    (5.0 / 1024.0)); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

    // Need reference chart for the mapping from the output voltage to the NTU according to different temperature.

    this->_value = voltage;
     */
    return this->_value;
}