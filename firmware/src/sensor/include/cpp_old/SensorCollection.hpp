//
// Created by User on 2022-03-11.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSORCOLLECTION_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSORCOLLECTION_H

#include "Sensor.hpp"


class SensorCollection {
public:
    static const int MAX_NUMBER_SENSORS = 6;

    SensorCollection(int powerPin);

    void addSensor(Sensor *sensor);

    void initializeSensors();

    string takeSensorMeasurements();

    bool isFull() { return _numberSensors == MAX_NUMBER_SENSORS; }

    bool isEmpty() { return _numberSensors == 0; }

private:
    int _powerPin;
    int _numberSensors;
    Sensor *_sensorList[MAX_NUMBER_SENSORS];
};


#endif //CAPSTONE_WATER_MONITOR_COMM_SENSORCOLLECTION_H
