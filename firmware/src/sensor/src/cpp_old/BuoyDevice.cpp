//
// Created by User on 2022-03-11.
//

#include <string>
#include "../../include/cpp_old/BuoyDevice.hpp"

using namespace std;


BuoyDevice::BuoyDevice(ClockInterface *ptrClock, CommunicationInterface *ptrCommunicationDevice,
                       PowerManagementInterface *ptrPowerManagementSystem, int buoySpecificMaxNumberSensorCollections) {
    _buoySpecificMaxNumberSensorCollections = buoySpecificMaxNumberSensorCollections;
    _numberSensorCollections = 0;
    _ptrClock = ptrClock;
    _ptrCommunicationDevice = ptrCommunicationDevice;
    _ptrPowerManagementSystem = ptrPowerManagementSystem;
}

void BuoyDevice::addSensorCollection(SensorCollection *ptrSensorCollection) {
    if (_numberSensorCollections < _buoySpecificMaxNumberSensorCollections) {
        _sensorCollectionList[_numberSensorCollections] = ptrSensorCollection;
        _numberSensorCollections++;
    }
}

void BuoyDevice::initializeBuoy() {
    for (int sensorCollectionIndex = 0; sensorCollectionIndex < _numberSensorCollections; sensorCollectionIndex++) {
        _sensorCollectionList[sensorCollectionIndex]->initializeSensors();
    }
}

string BuoyDevice::takeSensorMeasurements() {
    string overallData = "";
    if (_numberSensorCollections != 0) {
        string collectionData = _sensorCollectionList[0]->takeSensorMeasurements();
        overallData = collectionData.substr(1, collectionData.length() - 1);
    }
    for (int sensorCollectionIndex = 1; sensorCollectionIndex < _numberSensorCollections; sensorCollectionIndex++) {
        string collectionData = _sensorCollectionList[sensorCollectionIndex]->takeSensorMeasurements();
        overallData = overallData + "," + collectionData.substr(1, collectionData.length() - 1);
    }
    overallData = string("{" + overallData + "}");
    return overallData;
}

void BuoyDevice::connectToAWS() {
    _ptrCommunicationDevice->connectToAWS();
}

void BuoyDevice::publishSensorData() {
    _ptrCommunicationDevice->publishMQTT();
}

void BuoyDevice::updateGlobalSettings() {
}

void BuoyDevice::disconnectFromAWS() {
    _ptrCommunicationDevice->disconnectFromAWS();
}

void BuoyDevice::sleep(int milliseconds) {
    _ptrPowerManagementSystem->sleep(milliseconds);
}
