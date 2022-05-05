//
// Created by Nicholas Johnston on 2022-04-26.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_CALIBRATE_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_CALIBRATE_H
#include "sensor.h"
#include "sensor_definitions.h"

/**
 * Apply calibration params to SensorPh object.
 *
 * Applies calibration parameters to SensorPh object, such
 * that all converted ADC values are scaled by the results.
 * If the calib params are NULL, Manufacturer DFRobot values
 * will be applied.
 *
 * @param sensor_ph         SensorPh object.
 * @param calib_config      Void star that accepts a struct containing calibration values
 */
void sensor_ph_calib(Sensor sensor_ph, void * calib_config);


/**
 * Apply calibration params to SensorTurb object.
 *
 * Applies calibration parameters to SensorTurb object, such
 * that all converted ADC values are scaled by the results.
 * If the calib params are NULL, Manufacturer DFRobot values
 * will be applied.
 *
 * @param sensor_turb         SensorTurb object.
 * @param calib_config        Void star that accepts a struct containing calibration values
 */
void sensor_turb_calib(Sensor sensor_turb, void * calib_config);

#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_CALIBRATE_H
