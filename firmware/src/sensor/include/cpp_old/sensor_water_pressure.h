//
// Created by jordan on 2022-04-01.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_WATER_PRESSURE_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_WATER_PRESSURE_H

#include "sensor.h"


/**
 * Sensor object.
 *
 * @property sensor             Sensor parent object.
 * @property value_wp           Measured water pressure value.
 * @property _offset            Baseline no-load voltage.
 */
typedef struct sensor_water_pressure * SensorWp;
struct sensor_water_pressure
{
    Sensor sensor;

    float value_wp;
    float _offset;
};


/**
 * Initialize a SensorWp object.
 *
 * Creates a SensorWp object, allocating any necessary memory,
 * initializing all values, and setting any remaining pointer to NULL.
 *
 * <_offset> the voltage offset of the sensor is 0.5V (norminal).
 * The offset may not be exactly 0.5V. Calibration can be done as follows:
 * The LOWEST voltage reading of no-load output voltage
 * can be used as offset value.
 *
 * @param pin       Connected analog input pin.
 * @param _offset   output voltage offset.
 * @return Pointer to SensorWp object.
 */
SensorWp sensor_wp_init(int pin, const float * offset);


/**
 * Reset all values back to zero.
 *
 * @param sensor_wp SensorWp object.
 */
void sensor_wp_reset(SensorWp sensor_wp);


/**
 * Destroy SensorWp object.
 *
 * Destroys a SensorWp object, freeing any allocated
 * memory and setting all remaining values to 0 or NULL.
 *
 * @param sensor_wp     SensorWc object.
 */
void sensor_wp_destroy(SensorWp sensor_wp);

/**
 * Convert the voltage to water pressure.
 *
 * @param sensor_wp SensorWp object.
 * @return TDS reading from sensor.
 */
float to_water_pressure(void * sensor_wp);

#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_WATER_PRESSURE_H
