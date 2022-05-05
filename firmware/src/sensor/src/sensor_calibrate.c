//
// Created by Nicholas Johnston on 2022-04-26.
//

#include "sensor_calibrate.h"



//void sensor_ph_calib(Sensor sensor_ph, void * calib_config)
//{   /* This is a big ugly function. I did what I could... */
//    PhCalib * ph_calib;
//    sensor_ph->_calib_ph4 = (float) ( /* Assign calib values if they exist */
//            ( calib_volts_ph4 ) ? *calib_volts_ph4 : PH_DFR_MNFCTR_VPH4);
//
//    sensor_ph->_calib_ph7 = (float) ( /* Assign calib values if they exist */
//            ( calib_volts_ph7 ) ? *calib_volts_ph7 : PH_DFR_MNFCTR_VPH7);
//
//    sensor_ph->_calib_slope = (float) (PH_3
//                                       / ( (sensor_ph->_calib_ph7 - PH_DFR_MNFCTR_VPH7) / PH_3 )
//                                       - ( ( sensor_ph->_calib_ph4 - PH_DFR_MNFCTR_VPH4) / PH_3 ) );
//
//    sensor_ph->_calib_intercept = (float) (PH_7
//                                           - ( sensor_ph->_calib_slope )
//                                             * ( sensor_ph->_calib_ph7 - PH_DFR_MNFCTR_VPH7 )
//                                             / ( PH_3 ) );
//}
