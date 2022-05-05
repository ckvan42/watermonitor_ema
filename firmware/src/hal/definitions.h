/*
 * TEST
 *
 * File:   definitions.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file contains hardware definitions for SAMD21G18A
 * Hardware Description: An LED is connected via a 1k resistor to PIN PA17
 *                       The internal clock is output on PIN PA28
 *
 * Modified From: _00_LED_ON
 *
 * Change History:
 *
 * Author                 Rev     Date          Description
 * Armstrong Subero       1.1     26/05/2020    Added Support for SAMD21G18A
 * Microchip Technology   1.0     30/05/2018    Initial Release.
 * Copyright: Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
 * Updated on May 25, 2020, 11:18 AM
 */

#ifndef CAPSTONE_WATER_MONITOR_COMM_DEFINITIONS_H
#define CAPSTONE_WATER_MONITOR_COMM_DEFINITIONS_H

// I/O Ports definitions
#define PORTA     (0ul)
#define PORTB     (1ul)

// IO Pin definition
#define DIGITAL_PIN_13_PORT       PORT_PA17
#define DIGITAL_PIN_13_NUMBER     PIN_PA17
#define DIGITAL_PIN_12_PORT       PORT_PA19
#define DIGITAL_PIN_12_NUMBER     PIN_PA19
// PORTS IN USE, WE CANNOT USE
/*
#define DIGITAL_PIN_11_PORT       PORT_PA16
#define DIGITAL_PIN_11_NUMBER     PIN_PA16
#define DIGITAL_PIN_10_PORT       PORT_PA18
#define DIGITAL_PIN_10_NUMBER     PIN_PA18
*/
#define DIGITAL_PIN_9_PORT       PORT_PA07
#define DIGITAL_PIN_9_NUMBER     PIN_PA07
#define DIGITAL_PIN_8_PORT       PORT_PA06
#define DIGITAL_PIN_8_NUMBER     PIN_PA06
#define DIGITAL_PIN_7_PORT       PORT_PA21
#define DIGITAL_PIN_7_NUMBER     PIN_PA21
#define DIGITAL_PIN_6_PORT       PORT_PA20
#define DIGITAL_PIN_6_NUMBER     PIN_PA20
#define DIGITAL_PIN_5_PORT       PORT_PA15
#define DIGITAL_PIN_5_NUMBER     PIN_PA15
#define DIGITAL_PIN_4_PORT       PORT_PA08
#define DIGITAL_PIN_4_NUMBER     PIN_PA08
#define DIGITAL_PIN_3_PORT       PORT_PA09
#define DIGITAL_PIN_3_NUMBER     PIN_PA09
#define DIGITAL_PIN_2_PORT       PORT_PA14
#define DIGITAL_PIN_2_NUMBER     PIN_PA14
#define DIGITAL_PIN_1_PORT       PORT_PA10
#define DIGITAL_PIN_1_NUMBER     PIN_PA10
#define DIGITAL_PIN_0_PORT       PORT_PA11
#define DIGITAL_PIN_0_NUMBER     PIN_PA11




// GCLK_MAIN Clock output IO Pin Definition
#define GCLK_MAIN_OUTPUT_PORT       PORTA
#define GCLK_MAIN_OUTPUT_PIN_NUMBER (28ul)
#define GCLK_MAIN_OUTPUT_PIN_MASK   PORT_PA28

// Constants for Clock Generators
#define GENERIC_CLOCK_GENERATOR_MAIN      (0u)
#define GENERIC_CLOCK_GENERATOR_XOSC32K   (1u)

// initialized at reset for WDT
#define GENERIC_CLOCK_GENERATOR_OSCULP32K (2u)
#define GENERIC_CLOCK_GENERATOR_OSC8M     (3u)

// Constants for Clock multiplexers
#define GENERIC_CLOCK_MULTIPLEXER_DFLL48M (0u)

// Constants for DFLL48M
#define MAIN_CLK_FREQ (48000000u)

// Assumes 32.768 kHz Crystal is connected
#define EXT_32K_CLK_FREQ (32768u)

#endif //CAPSTONE_WATER_MONITOR_COMM_DEFINITIONS_H
