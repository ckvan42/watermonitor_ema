//
// Created by User on 2022-03-11.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_BUOYDEVICE_H
#define CAPSTONE_WATER_MONITOR_COMM_BUOYDEVICE_H

#include <string.h>

using namespace std;

#include "SensorCollection.hpp"
#include "../../../comm/CommunicationInterface.hpp"
#include "../../../clock/ClockInterface.hpp"
#include "../../../power/PowerManagementInterface.hpp"

class BuoyDevice {
public:
    static const int MAX_NUMBER_SENSOR_COLLECTIONS = 13;
    BuoyDevice(ClockInterface* ptrClock, CommunicationInterface* ptrCommunicationDevice, PowerManagementInterface* ptrPowerManagementSystem, int buoySpecificMaxNumberSensorCollections);
    void addSensorCollection(SensorCollection* ptrSensorCollection);
    void initializeBuoy();
    string takeSensorMeasurements();
    void connectToAWS();
    void publishSensorData();
    void updateGlobalSettings();
    void disconnectFromAWS();
    void sleep(int milliseconds);
private:
    CommunicationInterface* _ptrCommunicationDevice;
    ClockInterface* _ptrClock;
    PowerManagementInterface* _ptrPowerManagementSystem;
    int _buoySpecificMaxNumberSensorCollections;
    int _numberSensorCollections;
    SensorCollection* _sensorCollectionList[MAX_NUMBER_SENSOR_COLLECTIONS];
};


#endif //CAPSTONE_WATER_MONITOR_COMM_BUOYDEVICE_H
