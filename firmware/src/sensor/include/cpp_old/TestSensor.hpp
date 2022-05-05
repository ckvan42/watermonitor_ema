//
// Created by User on 2022-03-14.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_TESTSENSOR_H
#define CAPSTONE_WATER_MONITOR_COMM_TESTSENSOR_H

#include "Sensor.hpp"
#include <string>

using namespace std;

class TestSensor : public Sensor {
public:
    TestSensor(int pin, string name) : Sensor(pin, name, "test") {};

    void initializeSensor() override;

    float takeMeasurement() override;
};


#endif //CAPSTONE_WATER_MONITOR_COMM_TESTSENSOR_H
