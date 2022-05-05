#include "lora_eic.h"

#include <sam.h>
#include <stdbool.h>

#include "watermonitor.h"

bool DIO0_Flag;

//
//EIC Initialization:
//1. Enable CLK_EIC_APB
//2. If edge detection or filtering is required, GCLK_EIC must be enabled
//3. Write the EIC configuration registers (EVCTRL, WAKEUP, CONFIGy)
//4. Enable the EIC
//Enabling, Disabling and Resetting
//The EIC is enabled by writing a '1' the Enable bit in the Control register (CTRL.ENABLE).
//The EIC is disabled by writing CTRL.ENABLE to '0'.
//The EIC is reset by setting the Software Reset bit in the Control registern (CTRL.SWRST).
//All registers in the EIC will be reset to their initial state, and the EIC will be disabled.

void EIC_Handler             ( void )
{
	if(EIC->INTFLAG.bit.EXTINT14)
	{
		// Clear interrupt
		(EIC->INTFLAG.reg) |= 1 << 14;

		// Run Callback
		DIO0_Flag = true;
	}

	if(EIC->INTFLAG.bit.EXTINT4)
	{
		// Clear interrupt
		(EIC->INTFLAG.reg) |= 1 << 4;

		// Run Callback
		//DI1_Handler(NULL);
	}

	if(EIC->INTFLAG.bit.EXTINT5)
	{
		// Clear interrupt
		(EIC->INTFLAG.reg) |= 1 << 5;

		// Run Callback
		//DI2_Handler(NULL);
	}
}


//Reset:
//DI0 : PD2 = Port 3 Pin 2
//DI1 : PD
//
//
//
//
void GpioMcuSetInterrupts( void )
{
	//Disable the EIC
	EIC->CTRL.bit.ENABLE = 0;
	while(EIC->STATUS.bit.SYNCBUSY)
		{ continue; }

	// DI0
	//Set pinmux
	PORT->Group[0].PINCFG[14].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[7].bit.PMUXE = 0x00;

	// Enable continuous sampling
	PORT->Group[0].CTRL.bit.SAMPLING |= (1<<14);
	PORT->Group[0].PINCFG[14].bit.INEN = 1;

	// Enable EIC Trigger
	EIC->INTENSET.bit.EXTINT14 = 1;
	EIC->EVCTRL.bit.EXTINTEO14 = 1;
	EIC->WAKEUP.bit.WAKEUPEN14 = 1;

	// Disable Filter
	EIC->CONFIG[1].bit.FILTEN6 = 0;

	// Rising Edge
	EIC->CONFIG[1].bit.SENSE6  = 0x01;

//	// Set edge detect
//	switch(irqMode)
//	{
//	case IRQ_RISING_EDGE:
//		EIC->CONFIG[1].bit.SENSE6  = 0x01;
//		break;
//	case IRQ_FALLING_EDGE:
//		EIC->CONFIG[1].bit.SENSE6  = 0x02;
//		break;
//	case IRQ_RISING_FALLING_EDGE:
//		EIC->CONFIG[1].bit.SENSE6  = 0x03;
//		break;
//	case NO_IRQ: break;
//	}
//
//		DI0_Handler = irqHandler;
//
//		break;
//	case PB_4:
//		PORT->Group[0].PINCFG[20].bit.PMUXEN = 1;
//		PORT->Group[0].PMUX[10].bit.PMUXE = 0x00;
//
//		// Enable continuous sampling
//		PORT->Group[0].CTRL.bit.SAMPLING |= (1<<20);
//		PORT->Group[0].PINCFG[20].bit.INEN = 1;
//
//		// Enable EIC Trigger
//		EIC->INTENSET.bit.EXTINT4 = 1;
//		EIC->EVCTRL.bit.EXTINTEO4 = 1;
//		EIC->WAKEUP.bit.WAKEUPEN4 = 1;
//
//		// Disable Filter
//		EIC->CONFIG[0].bit.FILTEN4 = 0;
//
//		// Set edge detect
//		switch(irqMode)
//		{
//		case IRQ_RISING_EDGE:
//			EIC->CONFIG[0].bit.SENSE4  = 0x01;
//			break;
//		case IRQ_FALLING_EDGE:
//			EIC->CONFIG[0].bit.SENSE4  = 0x02;
//			break;
//		case IRQ_RISING_FALLING_EDGE:
//			EIC->CONFIG[0].bit.SENSE4  = 0x03;
//			break;
//		case NO_IRQ: break;
//		}
//
//		DI1_Handler = irqHandler;
//
//		break;
//	case PB_5:
//		PORT->Group[0].PINCFG[21].bit.PMUXEN = 1;
//		PORT->Group[0].PMUX[21].bit.PMUXE = 0x00;
//
//		// Enable continuous sampling
//		PORT->Group[0].CTRL.bit.SAMPLING |= (1<<21);
//		PORT->Group[0].PINCFG[21].bit.INEN = 1;
//
//		// Enable EIC Trigger
//		EIC->INTENSET.bit.EXTINT5 = 1;
//		EIC->EVCTRL.bit.EXTINTEO5 = 1;
//		EIC->WAKEUP.bit.WAKEUPEN5 = 1;
//
//		// Disable Filter
//		EIC->CONFIG[0].bit.FILTEN5 = 0;
//
//		// Set edge detect
//		switch(irqMode)
//		{
//		case IRQ_RISING_EDGE:
//			EIC->CONFIG[0].bit.SENSE5  = 0x01;
//			break;
//		case IRQ_FALLING_EDGE:
//			EIC->CONFIG[0].bit.SENSE5  = 0x02;
//			break;
//		case IRQ_RISING_FALLING_EDGE:
//			EIC->CONFIG[0].bit.SENSE5  = 0x03;
//			break;
//		case NO_IRQ: break;
//		}
//
//		DI2_Handler = irqHandler;
//
//		break;
//	default: break;
	//}

	//Enable the EIC
	EIC->CTRL.bit.ENABLE = 1;
	while(EIC->STATUS.bit.SYNCBUSY)
		{ continue; }
}

void eic_init()
{
	// Enable EIC Interrupts
	NVIC_SetPriority(EIC_IRQn, 3);
	NVIC_EnableIRQ(EIC_IRQn);

	DIO0_Flag = false;

	// Enable EIC Clock
	PM->APBAMASK.bit.EIC_ = 1;

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_EIC | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

	EIC->CTRL.bit.SWRST = 1;

	GpioMcuSetInterrupts();
}

