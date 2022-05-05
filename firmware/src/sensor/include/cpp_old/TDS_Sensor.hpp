//
// Created by fadi on 2022-03-11.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_TDS_H
#define CAPSTONE_WATER_MONITOR_COMM_TDS_H

#include "Sensor.hpp"

#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point

class TDS_Sensor : public Sensor {
private:

    int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
    int analogBufferTemp[SCOUNT];
    int analogBufferIndex = 0;
    int copyIndex = 0;
    float averageVoltage = 0;
    float tdsValue = 0;
    float temperature = 25;

    int getMedianNum(int bArray[], int iFilterLen);

public:
    TDS_Sensor(int pin, string name);

    void initializeSensor() override;

    float takeMeasurement() override;
};

#endif //CAPSTONE_WATER_MONITOR_COMM_TDS_H
