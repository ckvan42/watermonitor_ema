//
// Created by Nicholas Johnston on 2022-04-26.
//

#include "sensor_convert.h"
#include "sensor.h"

Convert conversions [NUM_SENSORS] =
        {
                to_ph,
                to_turb,
                to_ec,
                to_tds,
                to_water_pressure,
                NULL,
                NULL
        };

float to_ec(void * this)
{
    Sensor sensor_ec;
    float temperature;
    float kValue = 1.0;

    sensor_ec = (Sensor) this;
    temperature = 25.0;         // TEMPORARY UNTIL CALIB IS FIGURED OUT

//    sensor_ec->value_output = (float) (
//            ( (1000) * (sensor_ec->value_adc) / ( EC_RES2 )  /* I have no idea what these magic numbers are. They were in the    */
//              / ( EC_REF ) ) * sensor_ec->_calib_k_value ); /* sensor manufacturer's source code. Same with the macro values... */

    sensor_ec->value_output = (float) (
            ( (1000) * (sensor_ec->value_adc) / ( EC_RES2 )  /* I have no idea what these magic numbers are. They were in the    */
              / ( EC_REF ) ) * kValue );   /* k-value set to 1.0 temporarily */

    sensor_ec->value_output = (float) (( temperature )
       ? EC_TEMP_APPLY(sensor_ec->value_output , temperature)
       : sensor_ec->value_output);

    return sensor_ec->value_output;
}


float to_ph(void * this)
{
    float value_adc;
    Sensor sensor_ph;


    sensor_ph = (Sensor) this;

    value_adc = sensor_ph->value_adc;

//    sensor_ph->value_output = (float) ( sensor_ph->_calib_slope
//                                    * (value_adc - PH_DFR_MNFCTR_VPH7)
//                                    / (PH_3 + sensor_ph->_calib_intercept) );

    // CODE BELOW IS TEMPORARY UNTIL CALIB PARAMS ARE FIGURED OUT
    sensor_ph->value_output = (float) ( 1.0                                 // setting slope to 1.0 //
                                    * (value_adc - PH_DFR_MNFCTR_VPH7)
                                    / (PH_3 + 0.0) );                       // setting intercept to 0.0 //

    return sensor_ph->value_output;
}


float to_tds(void * this)
{
    Sensor sensor_tds;
    float temperature;
    float value_adc;
    float tds;

    temperature = 25.0; // TEMPORARY UNTIL CALIB IS FIGURED OUT //
    sensor_tds = (Sensor) this;
    value_adc = sensor_tds->value_adc / (1000); // Scaling from milli-volts to volts


    tds = (float) ( ( 0.5 ) *
                    (TDS_POLY_T1 * value_adc * value_adc * value_adc
                     - TDS_POLY_T2 * value_adc * value_adc
                     + TDS_POLY_T3 * value_adc));

//    sensor_tds->value_output = (float) (( sensor_tds->temp )
//                                     ? TDS_TEMP_APPLY(tds, *sensor_tds->temp): tds);
    sensor_tds->value_output = (float) ( ( temperature )
        ? TDS_TEMP_APPLY(tds, temperature): tds);

    return sensor_tds->value_output;

}

float to_turb(void * this)
{
    float value_adc;
    Sensor sensor_turb;

    sensor_turb = (Sensor) this;
    value_adc = sensor_turb->value_adc;

    sensor_turb->value_output =  (float) (
              ( TURB_POLY_T1 * ( value_adc * value_adc ) )  //  -1120.4x2 //
            + ( TURB_POLY_T2 * value_adc )                  // + 5742.3x  //
            - ( TURB_POLY_T3 ));                            // – 4352.9   //

    return sensor_turb->value_output;
}

float to_water_pressure(void * this)
{
    Sensor sensor_wp;
    float value_adc;

    sensor_wp = (Sensor) this;

    value_adc = ( sensor_wp->value_adc ) / (1000);
//    value_adc -= ( sensor_wp->_offset );
    sensor_wp->value_output = ( value_adc ) * WP_CONSTANT400;

    return sensor_wp->value_output;

}

