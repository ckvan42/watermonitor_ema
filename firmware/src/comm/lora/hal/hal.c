#include "hal/lora_spi.h"
#include "hal/lora_eic.h"

#include "lmic.h"
#include <sam.h>
#include <stdbool.h>

#include <FreeRTOS.h>
#include <task.h>

extern bool DIO0_Flag;

struct lmic_pinmap {
	// No members
};

const struct lmic_pinmap lmic_pins;

void hal_pin_rxtx (u1_t val)
	{ /* No rxtx pin */ }

void hal_init_ex(const void* pContext)
{
	spi_init();
	eic_init();

	// Set up reset pin
	PORT->Group[0].DIRSET.bit.DIRSET = (1<<7);
	PORT->Group[0].OUTSET.bit.OUTSET = (1<<7);
}

u4_t hal_ticks (void)
{
	return xTaskGetTickCount() * OSTICKS_PER_SEC / configTICK_RATE_HZ;
}

void hal_failed (const char *file, u2_t line)
{
	asm("BKPT");
}

void hal_disableIRQs (void)
{
	taskENTER_CRITICAL();
}

/*
 * enable CPU interrupts.
 */
void hal_enableIRQs (void)
{
	taskEXIT_CRITICAL();
}

void hal_processPendingIRQs(void)
{
	if(DIO0_Flag)
	{
		radio_irq_handler(0);
		DIO0_Flag = false;
	}
}

u1_t hal_checkTimer (u4_t targettime)
{
	targettime = targettime * configTICK_RATE_HZ / OSTICKS_PER_SEC;
	return targettime < xTaskGetTickCount();
}

void hal_sleep (void)
{
	// TODO: Low Power Mode
}

uint8_t hal_getTxPowerPolicy(
	u1_t inputPolicy,
	s1_t requestedPower,
	u4_t freq
	)
{
	// TODO: Tx Power Policy
	return 0;
}

void hal_pin_rst (u1_t val)
{
	switch(val)
	{
	case 0:
		PORT->Group[0].DIRSET.bit.DIRSET = (1<<7);
		PORT->Group[0].OUTCLR.bit.OUTCLR = (1<<7);
		break;
	case 1:
		PORT->Group[0].DIRSET.bit.DIRSET = (1<<7);
		PORT->Group[0].OUTSET.bit.OUTSET = (1<<7);
		break;
	case 2:
		PORT->Group[0].DIRCLR.bit.DIRCLR = (1<<7);
		break;
	}
}

ostime_t hal_setModuleActive (bit_t val)
{
	// No tx module to toggle
	return 0;
}

u4_t hal_waitUntil (u4_t time)
{
	time = time * configTICK_RATE_HZ / OSTICKS_PER_SEC;
	TickType_t xLastWakeTime = xTaskGetTickCount ();
	if((time - xLastWakeTime) > xLastWakeTime)
	{
		vTaskDelayUntil( &xLastWakeTime, time - xLastWakeTime );
	}
	return time;
}

bit_t hal_queryUsingTcxo(void)
{
	return 0;
}

s1_t hal_getRssiCal (void)
{
	return 0;
}
