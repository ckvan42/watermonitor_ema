//
// Created by User on 2022-03-11.
//

#include "../../include/cpp_old/SensorCollection.hpp"
//#include "ArduinoJson.h"

#include <string.h>

using namespace std;

SensorCollection::SensorCollection(int powerPin) {
    _numberSensors = 0;
    _powerPin = powerPin;
}

void SensorCollection::addSensor(Sensor *sensor) {
    if (_numberSensors < MAX_NUMBER_SENSORS) {
        _sensorList[_numberSensors] = sensor;
        _numberSensors++;
    }
}

//void SensorCollection::initializeSensors() {
//    pinMode(_powerPin, OUTPUT);
//    digitalWrite(_powerPin, LOW);
//    for (int sensorIndex = 0; sensorIndex < _numberSensors; sensorIndex++) {
//        _sensorList[sensorIndex]->initializeSensor();
//    }
//}
//
//string SensorCollection::takeSensorMeasurements() {
//    digitalWrite(_powerPin, HIGH);
//    delay(100);
//    StaticJsonDocument<256> doc;
//    for (int sensorIndex = 0; sensorIndex < _numberSensors; sensorIndex++) {
//        doc[_sensorList[sensorIndex]->getDataType()] = _sensorList[sensorIndex]->takeMeasurement();
//    }
//    string data;
//    serializeJson(doc, data);
//    return data;
//}
