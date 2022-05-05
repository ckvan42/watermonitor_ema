//
// Created by jordan on 2022-03-31.
//

#include "sensor_turb.h"


SensorTurb sensor_turb_init(int pin, const float * calib_k_value)
{
    Sensor sensor;
    SensorTurb sensor_turb;

    sensor = sensor_init(pin);
    if ( !sensor )
    {
        sensor_destroy(sensor);
        return NULL;
    }
    else
    {   /* inheritance from Sensor object. */
        sensor->type    = TURB;
        sensor->convert = to_ntu;
        sensor_turb = pvPortMalloc(sizeof(struct sensor_turb));
        if ( sensor_turb )
        {   /* inheritance from Sensor object. */
            sensor_turb->sensor = sensor;
            sensor_turb->value_ntu = 0;

            sensor_turb->_calib_k_value = (float) (( calib_k_value )
                ? *calib_k_value : TURB_KVAL_DEFAULT);
        }
    }

    return ( sensor_turb ) ? sensor_turb : NULL;
}


void sensor_turb_destroy(SensorTurb sensor_turb)
{
    if ( sensor_turb )
    {
        if (sensor_turb->sensor)
        {
            sensor_destroy(sensor_turb->sensor);
            sensor_turb->sensor = NULL;
        }

        sensor_turb->value_ntu = 0;
        sensor_turb->_calib_k_value = 0;
        vPortFree(sensor_turb); sensor_turb = NULL;
    }
}



float to_ntu(void * this)
{
    Sensor sensor;
    SensorTurb sensor_turb;
    float value_adc;

    sensor_turb = (SensorTurb) this;

    sensor = sensor_turb->sensor;
    value_adc = sensor->value_adc;

    sensor_turb->value_ntu =  (float) (
              ( TURB_POLY_T1 * ( value_adc * value_adc ) )  /*  -1120.4x2 */
            + ( TURB_POLY_T2 * value_adc )                  /* + 5742.3x  */
            - ( TURB_POLY_T3 ));                            /* – 4352.9   */

    return sensor_turb->value_ntu;
}
