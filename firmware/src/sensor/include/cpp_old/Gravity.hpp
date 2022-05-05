//
// Created by fadi on 2022-03-12.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_GRAVITY_H
#define CAPSTONE_WATER_MONITOR_COMM_GRAVITY_H

#include "Sensor.hpp"
#include "libs/DFRobot_EC10.h"
#include <string>

using namespace std;
#define DEFAULT_TEMP 20

class Gravity : public Sensor {
private:
    DFRobot_EC10 *ec;
public:
    Gravity(int pin, string name, DFRobot_EC10 *ec);

    void initializeSensor() override;

    float takeMeasurement() override;
};

#endif //CAPSTONE_WATER_MONITOR_COMM_GRAVITY_H
