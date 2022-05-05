//
// Created by User on 2022-03-11.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_H
//#include "string"

#include <string>
using namespace std;

    class Sensor {
    protected:
        int _readingPin;
        string _name;
        string _dataType;
        float _value;
        float _scaleFactor;
    public:
        Sensor(int pin, string name, string dataType);
        string getDataType() { return _dataType; }
        float getValue() { return _value; }
        virtual ~Sensor() {}
        virtual void initializeSensor() = 0;
        virtual float convert(float voltage) = 0;
        virtual float takeMeasurement() = 0;
    };


#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_H
