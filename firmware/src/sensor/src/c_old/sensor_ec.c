//
// Created by jordan on 2022-03-31.
//

#include "sensor_ec.h"


SensorEc sensor_ec_init(int pin, const float * calib_k_value)
{
    Sensor sensor;
    SensorEc sensor_ec;

    sensor = sensor_init(pin);
    if ( !sensor )
    {
        sensor_destroy(sensor);
        return NULL;
    }
    else
    {   /* inheritance from Sensor object. */
        sensor->type    = EC;
        sensor->convert = to_ec;
        sensor_ec = pvPortMalloc(sizeof(struct sensor_ec));

        if ( sensor_ec )
        {   /* inheritance from Sensor object. */
            sensor_ec->sensor   = sensor;
            sensor_ec->temp     = NULL;
            sensor_ec->value_ec = 0;

            sensor_ec->_calib_k_value = (float) (( calib_k_value )
                ? *calib_k_value : EC_KVAL_DEFAULT);
        }
    }

    return ( sensor_ec ) ? sensor_ec : NULL;
}


void sensor_ec_destroy(SensorEc sensor_ec)
{
    if ( sensor_ec )
    {
        if (sensor_ec->sensor)
        {
            sensor_destroy(sensor_ec->sensor);
            sensor_ec->sensor = NULL;
        }

        (*sensor_ec->temp) = 0;
        sensor_ec->value_ec = 0;
        sensor_ec->_calib_k_value = 0;
        vPortFree(sensor_ec); sensor_ec = NULL;
    }
}


void sensor_ec_reset(SensorEc sensor_ec)
{
    if ( sensor_ec )
    {
        if ( sensor_ec->sensor )
        {
            sensor_ec->sensor->value = 0;
            sensor_ec->sensor->value_adc = 0;
        }

        (*sensor_ec->temp) = 0;
        sensor_ec->value_ec = 0;
    }
}


float to_ec(void * this)
{
    SensorEc sensor_ec;

    sensor_ec = (SensorEc) this;

    sensor_ec->value_ec = (float) (
            ( (1000) * (sensor_ec->sensor->value_adc) / ( EC_RES2 )  /* I have no idea what these magic numbers are. They were in the    */
            / ( EC_REF ) ) * sensor_ec->_calib_k_value ); /* sensor manufacturer's source code. Same with the macro values... */

    sensor_ec->value_ec = (float) (( sensor_ec->temp )
        ? EC_TEMP_APPLY(sensor_ec->value_ec , *(sensor_ec->temp))
        : sensor_ec->value_ec);

    return sensor_ec->value_ec;
}
