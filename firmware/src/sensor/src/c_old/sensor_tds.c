//
// Created by jordan on 2022-04-01.
//

#include "sensor_tds.h"

SensorTds sensor_tds_init(int pin, const float * calib_k_value)
{
    Sensor sensor;
    SensorTds sensor_tds;

    sensor = sensor_init(pin);
    if ( !sensor )
    {
        sensor_destroy(sensor);
        return NULL;
    }
    else
    {   /* inheritance from Sensor object. */
        sensor->type    = TDS;
        sensor->convert = to_tds;
        sensor_tds = pvPortMalloc(sizeof(struct sensor_tds));

        if ( sensor_tds )
        {   /* inheritance from Sensor object. */
            sensor_tds->sensor   = sensor;
            sensor_tds->temp     = NULL;
            sensor_tds->value_tds = 0;

            sensor_tds->_calib_k_value = (float) (( calib_k_value )
                                                 ? *calib_k_value : TDS_KVAL_DEFAULT);
        }
    }

    return ( sensor_tds ) ? sensor_tds : NULL;
}


void sensor_tds_destroy(SensorTds sensor_tds)
{
    if ( sensor_tds )
    {
        if (sensor_tds->sensor)
        {
            sensor_destroy(sensor_tds->sensor);
            sensor_tds->sensor = NULL;
        }

        (*sensor_tds->temp) = 0;
        sensor_tds->value_tds = 0;
        sensor_tds->_calib_k_value = 0;
        vPortFree(sensor_tds); sensor_tds = NULL;
    }
}


void sensor_tds_reset(SensorTds sensor_tds)
{
    if ( sensor_tds )
    {
        if ( sensor_tds->sensor )
        {
            sensor_tds->sensor->value = 0;
            sensor_tds->sensor->value_adc = 0;
        }

        (*sensor_tds->temp) = 0;
        sensor_tds->value_tds = 0;
    }
}


float to_tds(void * this)
{
    float tds;
    Sensor sensor;
    SensorTds sensor_tds;
    float value_adc;

    sensor_tds = (SensorTds) this;
    sensor = sensor_tds->sensor;
    value_adc = sensor->value_adc / (1000); //the tds calculation takes the 3.3V


    tds = (float) ( ( 0.5 ) *
            (TDS_POLY_T1 * value_adc * value_adc * value_adc
            - TDS_POLY_T2 * value_adc * value_adc
            + TDS_POLY_T3 * value_adc));

    sensor_tds->value_tds = (float) (( sensor_tds->temp )
            ? TDS_TEMP_APPLY(tds, *sensor_tds->temp): tds);
    return sensor_tds->value_tds;

}
