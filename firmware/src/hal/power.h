/*
 * power.h
 *
 *  Created on: Mar 14, 2022
 *      Author: kwu96
 */

#ifndef NB_IOT_POWER_H_
#define NB_IOT_POWER_H_

#include <portmacro.h>

TickType_t hal_preSleep(TickType_t ticks);
TickType_t hal_postSleep(TickType_t ticks);

#endif /* NB_IOT_POWER_H_ */
