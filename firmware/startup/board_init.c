/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <sam.h>
#include <stdbool.h>
#include "board_definitions.h"

#include <Arduino.h>
#include "nbiot-uart.h"

#define SYSCTRL_FUSES_OSC32K_CAL_ADDR   (NVMCTRL_OTP4 + 4)
#define SYSCTRL_FUSES_OSC32K_CAL_Pos   6
#define   SYSCTRL_FUSES_OSC32K_ADDR   SYSCTRL_FUSES_OSC32K_CAL_ADDR
#define   SYSCTRL_FUSES_OSC32K_Pos   SYSCTRL_FUSES_OSC32K_CAL_Pos
#define   SYSCTRL_FUSES_OSC32K_Msk   (0x7Fu << SYSCTRL_FUSES_OSC32K_Pos)

volatile bool g_interrupt_enabled = true;

static void gclk_sync(void) {
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY)
        ;
}

static void dfll_sync(void) {
    while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0)
        ;
}

//extern void initialise_monitor_handles();


//volatile uint32_t debug_systick = 2;
void board_init(void) {

	NVMCTRL->CTRLB.bit.RWS = 1;
	//initialise_monitor_handles();

	// Use crystal
    SYSCTRL->XOSC32K.reg =
        SYSCTRL_XOSC32K_STARTUP(6) | SYSCTRL_XOSC32K_XTALEN | SYSCTRL_XOSC32K_EN32K;
    SYSCTRL->XOSC32K.bit.ENABLE = 1;
    while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_XOSC32KRDY) == 0)
        ;

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(1);
    gclk_sync();

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(1) | GCLK_GENCTRL_SRC_XOSC32K | GCLK_GENCTRL_GENEN;
    gclk_sync();

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(0) | GCLK_CLKCTRL_GEN_GCLK1 | GCLK_CLKCTRL_CLKEN;
    gclk_sync();

    SYSCTRL->DFLLCTRL.bit.ONDEMAND = 0;
    dfll_sync();

    SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_CSTEP(31) | SYSCTRL_DFLLMUL_FSTEP(511) |
                           SYSCTRL_DFLLMUL_MUL((MAIN_FREQUENCY / (32 * 1024)));
    dfll_sync();

    SYSCTRL->DFLLCTRL.reg |=
        SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_WAITLOCK | SYSCTRL_DFLLCTRL_QLDIS;
    dfll_sync();

    SYSCTRL->DFLLCTRL.reg |= SYSCTRL_DFLLCTRL_ENABLE;

    while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLLCKC) == 0 ||
           (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLLCKF) == 0)
        ;
    dfll_sync();

    // Configure DFLL48M as source for GCLK_GEN 0
    GCLK->GENDIV.reg = GCLK_GENDIV_ID(0);
    gclk_sync();

    GCLK->GENCTRL.reg =
        GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    gclk_sync();

    PM->CPUSEL.reg = PM_CPUSEL_CPUDIV_DIV1;
    SysTick_Config(SystemCoreClock / 1000);

    // Initialize analog Reads
    analogInit();
    ph_uart_init();
    conductivity_uart_init();

    PM->SLEEP.bit.IDLE = 0x02;

    // Uncomment these two lines to output GCLK0 on the SWCLK pin.
    // PORT->Group[0].PINCFG[30].bit.PMUXEN = 1;
    // Set the port mux mask for odd processor pin numbers, PA30 = 30 is even number, PMUXE = PMUX Even
    // PORT->Group[0].PMUX[30 / 2].reg |= PORT_PMUX_PMUXE_H;

}
