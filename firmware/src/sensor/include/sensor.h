//
// Created by jordan on 2022-03-30.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_H

#include <FreeRTOS.h>
#include <Arduino.h>

#include "sensor_types.h"
#include "sensor_convert.h"
//#include "sensor_pin_config.h"
#include "sensor_definitions.h"


/**
 * Sensor object.
 *
 * @property pin:           Analog input pin the sensor is connected to.
 * @property sensor_type    Sensor type (specified by enum sensor_type).
 * @property scale-factor   Value applied to the s_value for calibration.
 * @property e_value        Value returned from the ADC reading.
 * @property sensor_type    Converted value from ADC.
 */
typedef struct sensor * Sensor;
struct sensor
{
    int pin;
    float value_adc;
    unsigned int type;
    float value_output;

    Measure measure;
    Convert convert;
    Calibrate calibrate;
};


/**
 * Initialize Sensor object.
 *
 * Initializes sensor object, allocating necessary
 * memory and setting all other values to 0.
 *
 * If function fails to allocate memory,
 * NULL is returned.
 *
 * @param sensor_type   Sensor type specified by enum sensor_type
 * @param pin           Connected analog input pin.
 * @return Pointer to Sensor object.
 */
Sensor sensor_init(int pin, unsigned int sensor_type);


/**
 * Resets Sensor object
 *
 * Resets sensor object, zero'ing all values
 *
 * @param sensor
 */
void sensor_reset(Sensor sensor);


/**
 * Destroy Sensor object.
 *
 * Destroys a Sensor object, freeing
 * any allocated memory and setting all
 * remaining values to 0 or NULL.
 *
 * @param sensor
 */
void sensor_destroy(Sensor sensor);


/**
 * Take a measurement with a Sensor object.
 *
 * Takes a measure from an initialized sensor
 * at the analog pin specified by the sensor's
 * <pin> attribute.
 *
 * Stores the measured value from the ADC in the
 * Sensor object's <e_value> data member.
 *
 * @param sensor    A sensor object.
 * @return Measured value in volts.
 */
float measure(void * this);


/**
 * Check if sensor type is valid.
 *
 * Compare sensor type against min and max enum values
 * in sensor_types enum.
 *
 * @param sensor_type   A value representing the sensor type.
 * @return              1 or 0 (true or false).
 */
int is_valid_sensor(unsigned int sensor_type);


#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_H
