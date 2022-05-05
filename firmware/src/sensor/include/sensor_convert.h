//
// Created by Nicholas Johnston on 2022-04-26.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_CONVERT_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_CONVERT_H

#include "sensor_definitions.h"
#include "sensor_types.h"
#define NUM_SENSORS 7


/**
 * Convert 10-bit ADC value to EC value.
 *
 * @param sensor_ec SensorEc object.
 * @return EC reading from sensor.
 */
float to_ec(void * sensor_ec);

/**
 * Convert 10-bit ADC value to Dissolve Oxygen value.
 *
 * @param sensor_ph SensorDO object.
 * @return DO reading from sensor.
 */
float to_disox(void * sensor_do);

/**
 * Convert 10-bit ADC value to pH value.
 *
 * @param sensor_ph SensorPh object.
 * @return pH reading from sensor.
 */
float to_ph(void * sensor_ph);

/**
 * Convert 12-bit ADC value to EC value.
 *
 * @param sensor_tds SensorTds object.
 * @return TDS reading from sensor.
 */
float to_tds(void * sensor_tds);

/**
 * Convert 10-bit ADC value to turbidity value.
 *
 * @param sensor_turb SensorTurb object.
 * @return pH reading from sensor.
 */
float to_turb(void * sensor_turb);

/**
 * Convert the voltage to water pressure.
 *
 * @param sensor_wp SensorWp object.
 * @return TDS reading from sensor.
 */
float to_water_pressure(void * sensor_wp);


#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_CONVERT_H
