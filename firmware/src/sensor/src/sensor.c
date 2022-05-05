//
// Created by jordan on 2022-03-30.
//

#include "sensor.h"

extern Convert conversions[NUM_SENSORS];

Sensor sensor_init(int pin, unsigned int sensor_type)
{
    Sensor sensor;

    if ( is_valid_sensor(sensor_type) )
    {
        sensor = pvPortMalloc(sizeof(struct sensor));
        if ( sensor )
        {
            sensor->type = 0;
            sensor->pin = pin;
            sensor->value_adc = 0;
            sensor->value_output = 0;
            sensor->measure = measure;
            sensor->convert = conversions[sensor_type];
        }
    } else { sensor = NULL; }

    return sensor;
}


void sensor_destroy(Sensor sensor)
{
    if (sensor)
    {
        sensor->pin = 0;
        sensor->value_adc = 0;
        sensor->type = 0;
        sensor->measure = NULL;
        // Free init sensor malloc
        vPortFree(sensor); sensor = NULL;
    }
}


void sensor_reset(Sensor sensor)
{
    if (sensor)
    {
        sensor->pin = 0;
        sensor->value_adc = 0;
        sensor->type = 0;
    }
}


float measure(void * this)
{
//    float voltage;
    Sensor sensor;

    sensor = (Sensor) this; // cast 'this' to Sensor object.

    sensor->value_adc = (float) ( analogRead(sensor->pin)  / MAX_12_BIT * VREF_3300 );

    return sensor->value_adc;
}


int is_valid_sensor(unsigned int sensor_type)
{
    int type_lower_bound;
    int type_upper_bound;

    type_lower_bound = sensor_type >= PH;
    type_upper_bound = sensor_type <= DO;

    return ( type_upper_bound && type_lower_bound );
}
