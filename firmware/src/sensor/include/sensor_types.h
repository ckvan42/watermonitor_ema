//
// Created by jordan on 2022-03-30.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_TYPES_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_TYPES_H


/**
 * Generic function pointers.
 */
typedef float (* Measure) (void *);
typedef float (* Convert) (void *);
typedef void * (* Calibrate) (void *);


/**
 * Known types of sensors for the smart-device
 * as of Mar. 31, 2022.
 */
enum sensor_type
{
    PH,
    TURB,
    EC,
    TDS,
    W_PRESSURE,
    TEMP,
    DO
};

#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_TYPES_H
