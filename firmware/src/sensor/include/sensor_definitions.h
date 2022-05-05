//
// Created by jordan on 2022-03-31.
//

#ifndef CAPSTONE_WATER_MONITOR_COMM_SENSOR_DEFINITIONS_H
#define CAPSTONE_WATER_MONITOR_COMM_SENSOR_DEFINITIONS_H



/* * * * * * * * * * * * */
/*  General definitions  */
/* * * * * * * * * * * * */
#define VREF_5 5
#define VREF_5000 5000.00
#define VREF_3300 3300.00
#define MAX_10_BIT 1023.0
#define MAX_12_BIT 4095.00 //TODO ask power team if the resolution of the analogue read is set.

#define VOLTS_5 5.0
#define VOLTS_3 3.0
#define VOLTS_4 4.0



/* * * * * * * * * * * * */
/* PH sensor definitions */
/* * * * * * * * * * * * */
#define PH_3 3.0
#define PH_7 7.0
#define PH_MIN 0.0
#define PH_MAX 14.0
#define PH_DFR_MNFCTR_VPH7 1500.0
#define PH_DFR_MNFCTR_VPH4 2032.44



/* * * * * * * * * * * * */
/* EC sensor definitions */
/* * * * * * * * * * * * */
#define EC_REF 200.00
#define EC_RES2 820.00
#define EC_KVAL_CALIB 0.339
#define EC_KVAL_DEFAULT 1.0
#define EC_TEMP_APPLY(ec, temp) ( (ec) / ((1.0) + (0.0185) * ( (temp) - (25.0) )) )



/* * * * * * * * * * * * * * *  */
/* Turbidity sensor definitions */
/* * * * * * * * * * * * * * *  */
#define TURB_POLY_T1 -1120.4
#define TURB_POLY_T2  5742.3
#define TURB_POLY_T3  4352.9
#define TURB_KVAL_DEFAULT 1.0


/* * * * * * * * * * * * * * *  */
/* TDS sensor definitions       */
/* * * * * * * * * * * * * * *  */
#define TDS_POLY_T1 133.42
#define TDS_POLY_T2 255.86
#define TDS_POLY_T3 857.39
#define TDS_KVAL_DEFAULT 1.0


/* * * * * * * * * * * * * * * * * * * * * */
/* Water pressure sensor definitions       */
/* * * * * * * * * * * * * * * * * * * * * */
#define WP_CONSTANT400 400
#define WP_NOMINAL_OFFSET 0.5



//float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
#define TDS_TEMP_APPLY(tds, temp) ( (tds) / ((1.0) + (0.0185) * ( (temp) - (25.0) )) )


/* TDS sensor definitions */
#define TDS_SCOUNT  30


#endif //CAPSTONE_WATER_MONITOR_COMM_SENSOR_DEFINITIONS_H
