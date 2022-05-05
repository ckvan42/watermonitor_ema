//
// Created by jordan on 2022-03-25.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_EC_SENSOR_HPP
#define CAPSTONE_WATER_MONITOR_COMM_EC_SENSOR_HPP

#include "Sensor.hpp"

#include <string>

#define RES2 (7500.0/0.66)
#define ECREF 20.0


//this->_rawEC = 1000*voltage/RES2/ECREF;
//valueTemp = this->_rawEC * this->_kvalue;
////automatic shift process
////First Range:(0,2); Second Range:(2,20)
//if(valueTemp > 2.5){
//this->_kvalue = this->_kvalueHigh;
//}else if(valueTemp < 2.0){
//this->_kvalue = this->_kvalueLow;
//}
//
//value = this->_rawEC * this->_kvalue;             //calculate the EC value after automatic shift
//value = value / (1.0+0.0185*(temperature-25.0));  //temperature compensation
//this->_ecvalue = value;


using namespace std;

#define DEFAULT_TEMP 20

class EC_Sensor : public Sensor {
private:
    float _ecvalue;
    float _ecvalueRaw;
    float _kvalue;
    float _temperature;

public:
    EC_Sensor(int pin, string name);

    void initializeSensor() override;

    float convert(float voltage) override;

    float takeMeasurement() override;
};


#endif //CAPSTONE_WATER_MONITOR_COMM_EC_SENSOR_HPP
