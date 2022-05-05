/*
 * arduino_func.c
 *
 *  Created on: Mar 15, 2022
 *      Author: kwu96
 */


#include <sam.h>
#include "Arduino.h"

//enum pin{D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13};
//We want the mapping:
//0 -> PA11
//1 -> PA10
//2 -> PA14
//3 -> PA09 reserved
//4 -> PA08 reserved
//5 -> PA15
//6 -> PA20
//7 -> PA21
//8 -> PA06 reserved
//9 -> PA07 reserved
//10-> PA18 reserved
//11-> PA16 reserved
//12-> PA19
//13-> PA17
//All are in group A (port 0)


//Input:
//pin:	integers 0 to 13 for corresponding digital output pins.
//val:	0 or 1 for low or high output respectively.
//Do not use pin 10 (Tx) or 11 (Rx), as they are reserved for the NB-IoT hat
void digitalWrite( uint32_t pin, int val )
{
	uint32_t _pin = 0;

	if (pin < 0 || pin > 13)
		return; //invalid digital pin, do nothing

	switch (pin)
	{
	case 0:
		_pin = 11;
		break;
	case 1:
		_pin = 10;
		break;
	case 2:
		_pin = 14;
		break;
	case 3:
		return;//_pin = 9;
		break;
	case 4:
		return;//_pin = 8;
		break;
	case 5:
		_pin = 15;
		break;
	case 6:
		_pin = 20;
		break;
	case 7:
		_pin = 21;
		break;
	case 8: //reserved
		return;//_pin = 6;
		break;
	case 9: //reserved
		return;//_pin = 7;
		break;
	case 10:
		return;
	case 11:
		return;
	case 12://reserved
		_pin = 19;
		break;
	case 13://reserved
		_pin = 17;
		break;
	default: //this shouldn't happen
		break;
	}

	uint32_t pinMask = (1 << _pin);

	//If pin not configured as output:
	//disable pull-up if outputting low, else enable pull-up
	//This lets us set the value of the pin without setting it up as output, if no input
	if( (PORT->Group[0].DIRSET.reg & pinMask) == 0)
		PORT->Group[0].PINCFG[_pin].bit.PULLEN = ((val == 0 ) ? 0 : 1);
//	{
//		if (val == 0)
//		{
//			PORT->Group[0].PINCFG[_pin].bit.PULLEN = 0;
//		}
//		else
//		{
//			PORT->Group[0].PINCFG[_pin].bit.PULLEN = 1;
//		}
//	}

	switch (val)
	{
		case 0:
			PORT->Group[0].OUTCLR.reg = pinMask;
			break;
		default:
			PORT->Group[0].OUTSET.reg = pinMask;
			break;
	}

	return;
}

void analogInit(void)
{
	//Port A
	//Pins 2 4 and 5
	//Port B
	//Pins 8 9 and 2
	PORT->Group[0].PINCFG[2].bit.PMUXEN = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PINCFG[2].bit.INEN = 1;
	PORT->Group[0].PMUX[1].bit.PMUXE = MUX_PA02B_ADC_AIN0;
	PORT->Group[0].PINCFG[4].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[4].bit.INEN = 1;
	PORT->Group[0].PMUX[2].bit.PMUXE = MUX_PA04B_ADC_AIN4;
	PORT->Group[0].PINCFG[5].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[5].bit.INEN = 1;
	PORT->Group[0].PMUX[2].bit.PMUXO = MUX_PA05B_ADC_AIN5;

	PORT->Group[1].PINCFG[8].bit.PMUXEN = 1;
	PORT->Group[1].PINCFG[8].bit.INEN = 1;
	PORT->Group[1].PMUX[4].bit.PMUXE = MUX_PB08B_ADC_AIN2;
	PORT->Group[1].PINCFG[9].bit.PMUXEN = 1;
	PORT->Group[1].PINCFG[9].bit.INEN = 1;
	PORT->Group[1].PMUX[4].bit.PMUXO = MUX_PB09B_ADC_AIN3;
	PORT->Group[1].PINCFG[2].bit.PMUXEN = 1;
	PORT->Group[1].PINCFG[2].bit.INEN = 1;
	PORT->Group[1].PMUX[1].bit.PMUXE = MUX_PB02B_ADC_AIN10;


//	PORT->Group[0].DIRCLR.reg |= 2;

//    PORT->Group[0].PINCFG[2].bit.PMUXEN = 1;
//    PORT->Group[0].PINCFG[4].bit.PMUXEN = 1;
//    PORT->Group[0].PINCFG[5].bit.PMUXEN = 1;
//    PORT->Group[0].PMUX[8].bit.PMUXE = 0x02;
//    PORT->Group[0].PMUX[9].bit.PMUXE = 0x02;

    GCLK->CLKCTRL.bit.GEN = 0;
	GCLK->CLKCTRL.bit.ID |= GCLK_CLKCTRL_ID_ADC;  //Select ADC Clock
    GCLK->CLKCTRL.bit.CLKEN = 1;

	while (GCLK->STATUS.bit.SYNCBUSY) {};

	PM->APBCMASK.reg |= PM_APBCMASK_ADC;

	while (ADC->STATUS.bit.SYNCBUSY) {};
	//Everything is set to 0

	ADC->CTRLB.bit.RESSEL = 0; //12 bit
	ADC->CTRLB.bit.DIFFMODE = 0x00;	//Enable single conversion
	while (ADC->STATUS.bit.SYNCBUSY) {};
	ADC->CTRLB.bit.PRESCALER = 0x05;	//Div 128
	while (ADC->STATUS.bit.SYNCBUSY) {};
	ADC->INPUTCTRL.bit.MUXNEG = 0x19;	//Set internal gnd	//Locking up here. Probably not necessary because single ended mode.
	while (ADC->STATUS.bit.SYNCBUSY) {};
	ADC->INPUTCTRL.bit.GAIN = 0x0F;
	while (ADC->STATUS.bit.SYNCBUSY) {};
	ADC->REFCTRL.bit.REFSEL = 0x02;		//Set internal reference voltage
	while (ADC->STATUS.bit.SYNCBUSY) {};


	//Calibration
	uint32_t bias = (*((uint32_t *) ADC_FUSES_BIASCAL_ADDR) & ADC_FUSES_BIASCAL_Msk) >> ADC_FUSES_BIASCAL_Pos;
	uint32_t linearity = (*((uint32_t *) ADC_FUSES_LINEARITY_0_ADDR) & ADC_FUSES_LINEARITY_0_Msk) >> ADC_FUSES_LINEARITY_0_Pos;
	linearity |= ((*((uint32_t *) ADC_FUSES_LINEARITY_1_ADDR) & ADC_FUSES_LINEARITY_1_Msk) >> ADC_FUSES_LINEARITY_1_Pos) << 5;

	/* Wait for bus synchronization. */
	while (ADC->STATUS.bit.SYNCBUSY) {};

	/* Write the calibration data. */
	ADC->CALIB.reg = ADC_CALIB_BIAS_CAL(bias) | ADC_CALIB_LINEARITY_CAL(linearity);
}


/*Ports:
 * 0 -> A 2
 * 1 -> B 8
 * 2 -> B 9
 * 3 -> A 4
 * 4 -> A 5
 * 5 -> B 2
 */
int analogRead(int pin_num) __attribute__((unused));
int analogRead(int pin_num)
{
	int temp;
//	uint_32_t _port = 0;
//	uint_32_t _pin = 0;
	ADC->CTRLA.bit.ENABLE = 0x01;	//Enable ADC
	while (ADC->STATUS.bit.SYNCBUSY) {};

	switch(pin_num)
	{
	case 0:
//		_port = 0;
//		_pin = 2;
		ADC->INPUTCTRL.bit.MUXPOS = 0x00;	//Set ADC pin
		break;
	case 1:
//		_port = 1;
//		_pin = 8;
		ADC->INPUTCTRL.bit.MUXPOS = 0x01;	//Set ADC pin
		break;
	case 2:
//		_port = 1;
//		_pin = 9;
		ADC->INPUTCTRL.bit.MUXPOS = 0x02;	//Set ADC pin
		break;
	case 3:
//		_port = 0;
//		_pin = 4;
		ADC->INPUTCTRL.bit.MUXPOS = 0x03;	//Set ADC pin
		break;
	case 4:
//		_port = 0;
//		_pin = 5;
		ADC->INPUTCTRL.bit.MUXPOS = 0x04;	//Set ADC pin
		break;
	case 5:
//		_port = 1;
//		_pin = 2;
		ADC->INPUTCTRL.bit.MUXPOS = 0x05;	//Set ADC pin
		break;
	default: //Ain 0
//		_port = 0;
//		_pin = 2;
		ADC->INPUTCTRL.bit.MUXPOS = 0x00;	//Set ADC pin
		break;
	}

	ADC->SWTRIG.bit.START = 0x01;	//Start ADC conversion
	while (ADC->INTFLAG.bit.RESRDY == 0)	//Wait for conversion to complete
		;
	ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY; //Clear the data ready flag

	temp = ADC->RESULT.reg;		//Store ADC value
	ADC->CTRLA.bit.ENABLE = 0x00;	//Disable ADC

	return temp;
}

