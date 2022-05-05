//
// Created by User on 2022-03-11.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_PH_SENSOR_H
#define CAPSTONE_WATER_MONITOR_COMM_PH_SENSOR_H

#include <string>

using namespace std;

#define DEFAULT_TEMP 20


class PH_Sensor : public Sensor {
private:
    float _phValue;
    float _acidVoltage;
    float _neutralVoltage;
public:
    PH_Sensor(int pin, string name);

    void initializeSensor() override;

    float convert(float voltage) override;

    float takeMeasurement() override;
};

#endif //CAPSTONE_WATER_MONITOR_COMM_PH_SENSOR_H
