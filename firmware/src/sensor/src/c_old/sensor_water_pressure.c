
#include "sensor_water_pressure.h"

SensorWp sensor_wp_init(int pin, const float * offset)
{
    Sensor sensor;
    SensorWp sensor_wp;

    sensor = sensor_init(pin);
    if ( !sensor )
    {
        sensor_destroy(sensor);
        return NULL;
    }
    else
    {   /* inheritance from Sensor object. */
        sensor->type    = W_PRESSURE;
        sensor->convert = to_water_pressure;
        sensor_wp = pvPortMalloc(sizeof(struct sensor_water_pressure));

        if ( sensor_wp )
        {   /* inheritance from Sensor object. */
            sensor_wp->sensor   = sensor;
            sensor_wp->_offset = (float) (( offset ) ? *offset : WP_NOMINAL_OFFSET);
        }
    }

    return ( sensor_wp ) ? sensor_wp : NULL;
}


void sensor_wp_destroy(SensorWp sensor_wp)
{
    if ( sensor_wp )
    {
        if (sensor_wp->sensor)
        {
            sensor_destroy(sensor_wp->sensor);
            sensor_wp->sensor = NULL;
        }

        sensor_wp->value_wp = 0;
        sensor_wp->_offset = 0;
        vPortFree(sensor_wp); sensor_wp = NULL;
    }
}


void sensor_wp_reset(SensorWp sensor_wp)
{
    if ( sensor_wp )
    {
        if ( sensor_wp->sensor )
        {
            sensor_wp->sensor->value = 0;
            sensor_wp->sensor->value_adc = 0;
        }

        sensor_wp->value_wp = 0;
    }
}

float to_water_pressure(void * this)
{
    Sensor sensor;
    SensorWp sensor_wp;
    float value_adc;

    sensor_wp = (SensorWp) this;
    sensor = sensor_wp->sensor;

    value_adc = ( sensor->value_adc ) / (1000);
    value_adc -= ( sensor_wp->_offset );
    sensor_wp->value_wp = ( value_adc ) * WP_CONSTANT400;

    return sensor_wp->value_wp;

}
