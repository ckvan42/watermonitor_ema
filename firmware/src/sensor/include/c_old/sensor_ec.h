#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_EC_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_EC_H

#include "sensor.h"


/**
 * Sensor object.
 *
 * @property sensor             Sensor parent object.
 * @property value_ph           Measured pH value.
 * @property volts_calib_ph4    Baseline voltage measured against pH4 solution.
 * @property volts_calib_ph7    Baseline voltage measured against pH7 solution.
 */
typedef struct sensor_ec * SensorEc;
struct sensor_ec
{
    Sensor sensor;

    float * temp;
    float value_ec;
    float _calib_k_value;
};


/**
 * Initialize a SensorEc object.
 *
 * Creates a SensorEc object, allocating any necessary memory,
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
SensorEc sensor_ec_init(int pin, const float * calib_k_value);


/**
 * Reset all values back to zero.
 *
 * @param sensor_ec SensorEc object.
 */
void sensor_ec_reset(SensorEc sensor_ec);


/**
 * Destroy SensorEc object.
 *
 * Destroys a SensorEc object, freeing any allocated
 * memory and setting all remaining values to 0 or NULL.
 *
 * @param sensor_ec     SensorEc object.
 */
void sensor_ec_destroy(SensorEc sensor_ec);


/**
 * Convert 10-bit ADC value to EC value.
 *
 * @param sensor_ec SensorEc object.
 * @return EC reading from sensor.
 */
float to_ec(void * sensor_ec);







#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_EC_H
