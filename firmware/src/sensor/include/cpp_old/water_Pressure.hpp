
//
// Created by fadi on 2022-03-12.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_WATER_PRESSURE_H
#define CAPSTONE_WATER_MONITOR_COMM_WATER_PRESSURE_H

#include "Sensor.hpp"

class Water_Pressure_Sensor : public Sensor {
private:
    const float OffSet = 0.483;

    float V, P;
public:
    Water_Pressure_Sensor(int pin, string name);

    void initializeSensor() override;

    float takeMeasurement() override;
};


#endif //CAPSTONE_WATER_MONITOR_COMM_WATER_PRESSURE_H
