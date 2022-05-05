//
// Created by jordan on 2022-03-31.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_PH_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_PH_H

#include "sensor.h"


/**
 * Sensor object.
 *
 * @property sensor             Sensor parent object.
 * @property value_ph           Measured pH value.
 * @property volts_calib_ph4    Baseline voltage measured against pH4 solution.
 * @property volts_calib_ph7    Baseline voltage measured against pH7 solution.
 */
typedef struct sensor_ph * SensorPh;
struct sensor_ph
{
    Sensor sensor;
    float value_ph;
    float _calib_ph4;
    float _calib_ph7;
    float _calib_slope;
    float _calib_intercept;
};


/**
 * Initialize a SensorPh object.
 *
 * Creates a SensorPh object, allocating
 * any necessary memory, initializing all values
 * and setting any remaining pointer to NULL.
 *
 * Calibration params may be optionally passed t be applied
 * to every measurement. If <calib_volts_ph7> and <calib_volts_ph4>
 * are NULL, SensorPh object's calibrations parameters will be assigned
 * the default values provided by the manufacturer (At this time DFRobot).
 *
 * @param calib_volts_ph7   10-bit voltage reading tested against pH 7.0 solution.
 * @param calib_volts_ph4   10-bit voltage reading tested against pH 4.0 solution.
 * @return Pointer to SensorPh object.
 */
SensorPh sensor_ph_init(int pin, const float * calib_volts_ph7, const float * calib_volts_ph4);


/**
 * Destroy SensorPh object.
 *
 * Destroys a Sensor object, freeing any allocated
 * memory and setting all remaining values to 0 or NULL.
 *
 * @param sensor_ph     SensorPh object.
 */
void sensor_ph_destroy(SensorPh sensor_ph);


/**
 * Apply calibration params to SensorPh object.
 *
 * Applies calibration parameters to SensorPh object, such
 * that all converted ADC values are scaled by the results.
 * If the calib params are NULL, Manufacturer DFRobot values
 * will be applied.
 *
 * @param sensor_ph         SensorPh object.
 * @param calib_volts_ph7   10-bit voltage reading tested against pH 7.0 solution.
 * @param calib_volts_ph4   10-bit voltage reading tested against pH 4.0 solution.
 */
void sensor_ph_calib(SensorPh sensor_ph, const float * calib_volts_ph7, const float * calib_volts_ph4);


/**
 * Convert 10-bit ADC value to pH value.
 *
 * @param sensor_ph SensorPh object.
 * @return pH reading from sensor.
 */
float to_ph(void * sensor_ph);


#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_PH_H
