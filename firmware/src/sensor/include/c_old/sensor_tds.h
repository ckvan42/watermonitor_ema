//
// Created by jordan on 2022-04-01.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_TDS_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_TDS_H

#include "sensor.h"


/**
 * Sensor object.
 *
 * @property sensor             Sensor parent object.
 * @property value_ph           Measured TDS value.
 * @property _calib_k_value     Corrective scale factor applied
 *                              to each measurement.
 */
typedef struct sensor_tds * SensorTds;
struct sensor_tds
{
    Sensor sensor;

    float * temp;
    float value_tds;
    float _calib_k_value;
};


/**
 * Initialize a SensorTds object.
 *
 * Creates a SensorTds object, allocating any necessary memory,
 * initializing all values, and setting any remaining pointer to NULL.
 *
 * <calib_k_value> may be optionally passed to be applied
 * to every measurement. If <calib_k_value> is NULL, the default value of
 * 1.0 will be assigned.
 *
 * @param pin             Connected analog input pin.
 * @param calib_k_value   Corrective scale factor applied to each measurement.
 * @return Pointer to SensorEc object.
 */
SensorTds sensor_tds_init(int pin, const float * calib_k_value);


/**
 * Reset all values back to zero.
 *
 * @param sensor_tds SensorTds object.
 */
void sensor_tds_reset(SensorTds sensor_tds);


/**
 * Destroy SensorTds object.
 *
 * Destroys a SensorTds object, freeing any allocated
 * memory and setting all remaining values to 0 or NULL.
 *
 * @param sensor_tds     SensorTds object.
 */
void sensor_tds_destroy(SensorTds sensor_tds);


/**
 * Convert 12-bit ADC value to EC value.
 *
 * @param sensor_tds SensorTds object.
 * @return TDS reading from sensor.
 */
float to_tds(void * sensor_tds);



#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_TDS_H
