//
// Created by User on 2022-03-14.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_DFROBOTTURBIDITYSENSOR_H
#define CAPSTONE_WATER_MONITOR_COMM_DFROBOTTURBIDITYSENSOR_H


#include "Sensor.hpp"
//#include "Arduino.h"

#include <string>

using namespace std;

#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution
//Single-point calibration Mode=0
//Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0
#define READ_TEMP (25) //Current water temperature ℃, Or temperature sensor function
//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //mv
#define CAL1_T (25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

/*********Beginning of calibration code ************/
// uint32_t raw;

// void setup()
// {
//     Serial.begin(115200);
// }

// void loop()
// {
//     raw=analogRead(A1);
//     Serial.println("raw:\t"+String(raw)+"\tVoltage(mv)"+String(raw*VREF/ADC_RES));
//     delay(1000);
// }
/*********End of calibration code ************/

class DfrobotTurbiditySensor : public Sensor {
public:
    DfrobotTurbiditySensor(int pin, string name) : Sensor(pin, name, "turbidity") {}

    void initializeSensor() override;

    float takeMeasurement() override;
};


#endif //CAPSTONE_WATER_MONITOR_COMM_DFROBOTTURBIDITYSENSOR_H
