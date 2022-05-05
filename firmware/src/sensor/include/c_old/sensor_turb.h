//
// Created by jordan on 2022-03-31.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_TURB_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_TURB_H

#include "sensor_definitions.h"
#include "sensor_types.h"
#include "sensor.h"


/**
 * Sensor object.
 *
 * @property sensor             Sensor parent object.
 * @property value_ph           Measured pH value.
 * @property volts_calib_ph4    Baseline voltage measured against pH4 solution.
 * @property volts_calib_ph7    Baseline voltage measured against pH7 solution.
 */
typedef struct sensor_turb * SensorTurb;
struct sensor_turb
{
    Sensor sensor;
    float value_ntu;
    float _calib_k_value;
};


/**
 * Initialize a SensorTurb object.
 *
 * Creates a SensorTurb object, allocating
 * any necessary memory, initializing all values
 * and setting any remaining pointer to NULL.
 *
 * <calib_k_value> params may be optionally passed t0 be applied
 * to every measurement. If <calib_k_value> is NULL, SensorTurb object's
 * k_value will be set to 1.0 by default.
 *
 * @param calib_k_value   Corrective scale factor applied to each measurement
 * @return SensorTurb object.
 */
SensorTurb sensor_turb_init(int pin, const float * calib_k_value);


/**
 * Destroy SensorTurb object.
 *
 * Destroys a Sensor object, freeing any allocated
 * memory and setting all remaining values to 0 or NULL.
 *
 * @param sensor_turb     SensorTurb object.
 */
void sensor_turb_destroy(SensorTurb sensor_turb);


/**
 * Apply calibration params to SensorTurb object.
 *
 * Applies calibration parameters to SensorTurb object, such
 * that all converted ADC values are scaled by the results.
 * If the calib params are NULL, Manufacturer DFRobot values
 * will be applied.
 *
 * @param sensor_turb         SensorTurb object.
 * @param calib_volts_ph7   10-bit voltage reading tested against pH 7.0 solution.
 * @param calib_volts_ph4   10-bit voltage reading tested against pH 4.0 solution.
 */
void sensor_turb_calib(SensorTurb sensor_turb, const float * calib_k_value);


/**
 * Convert 10-bit ADC value to turbidity value.
 *
 * @param sensor_turb SensorTurb object.
 * @return pH reading from sensor.
 */
float to_ntu(void * sensor_turb);




#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_TURB_H
