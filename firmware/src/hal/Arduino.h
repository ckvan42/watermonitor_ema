/*
 * arduino_func.h
 *
 *  Created on: Mar 15, 2022
 *      Author: kwu96
 */

#ifndef NB_IOT_ARDUINO_FUNC_H_
#define NB_IOT_ARDUINO_FUNC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

//Takes in the pin 0 to 13 (corresponding to D0 to D13 and sets it high or low
//
void digitalWrite( uint32_t pin, int val );

void analogInit(void);
int analogRead(int pin_num);

void delay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* NB_IOT_ARDUINO_FUNC_H_ */
