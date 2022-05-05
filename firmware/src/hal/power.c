/*
 * power.c
 *
 *  Created on: Mar 14, 2022
 *      Author: kwu96
 */


#include <sam.h>
#include <power.h>

TickType_t hal_preSleep(TickType_t ticks)
{
	return ticks;
}

TickType_t hal_postSleep(TickType_t ticks)
{
	return ticks;
}
