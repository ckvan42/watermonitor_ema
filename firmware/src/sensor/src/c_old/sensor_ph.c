//
// Created by jordan on 2022-03-31.
//

#include "sensor_ph.h"


SensorPh sensor_ph_init(int pin, const float * calib_volts_ph7, const float * calib_volts_ph4)
{
    Sensor sensor;
    SensorPh sensor_ph;

    sensor = sensor_init(pin);
    if ( !sensor )
    {
        sensor_destroy(sensor);
        return NULL;
    }
    else
    {   /* inheritance from Sensor object. */
        sensor->type    = PH;
        sensor->convert = to_ph;
        sensor_ph = pvPortMalloc(sizeof(struct sensor_ph));
        if ( sensor_ph )
        {   /* inheritance from Sensor object. */
            sensor_ph->sensor = sensor;
            sensor_ph->value_ph = 0;
            sensor_ph_calib(sensor_ph, /* compute calibration constants */
                calib_volts_ph7, calib_volts_ph4);
        }
    }

    return ( sensor_ph ) ? sensor_ph : NULL;
}


void sensor_ph_destroy(SensorPh sensor_ph)
{
    if ( sensor_ph )
    {
        if (sensor_ph->sensor)
        {
            sensor_destroy(sensor_ph->sensor);
            sensor_ph->sensor = NULL;
        }

        sensor_ph->_calib_ph7 = 0;
        sensor_ph->_calib_ph4 = 0;
        sensor_ph->_calib_slope = 0;
        sensor_ph->_calib_intercept = 0;
        vPortFree(sensor_ph); sensor_ph = NULL;
    }
}



float to_ph(void * this)
{
    Sensor sensor;
    float value_adc;
    SensorPh sensor_ph;


    sensor_ph = (SensorPh) this;

    sensor = sensor_ph->sensor;
    value_adc = sensor->value_adc;

    sensor_ph->value_ph = (float) ( sensor_ph->_calib_slope
                                    * (value_adc - PH_DFR_MNFCTR_VPH7)
                                    / (PH_3 + sensor_ph->_calib_intercept) );

    return sensor_ph->value_ph;
}


void sensor_ph_calib(SensorPh sensor_ph, const float * calib_volts_ph7, const float * calib_volts_ph4)
{   /* This is a big ugly function. I did what I could... */

    sensor_ph->_calib_ph4 = (float) ( /* Assign calib values if they exist */
            ( calib_volts_ph4 ) ? *calib_volts_ph4 : PH_DFR_MNFCTR_VPH4);

    sensor_ph->_calib_ph7 = (float) ( /* Assign calib values if they exist */
            ( calib_volts_ph7 ) ? *calib_volts_ph7 : PH_DFR_MNFCTR_VPH7);

    sensor_ph->_calib_slope = (float) (PH_3
       / ( (sensor_ph->_calib_ph7 - PH_DFR_MNFCTR_VPH7) / PH_3 )
       - ( ( sensor_ph->_calib_ph4 - PH_DFR_MNFCTR_VPH4) / PH_3 ) );

    sensor_ph->_calib_intercept = (float) (PH_7
       - ( sensor_ph->_calib_slope )
       * ( sensor_ph->_calib_ph7 - PH_DFR_MNFCTR_VPH7 )
       / ( PH_3 ) );
}
