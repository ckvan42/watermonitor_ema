#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

uint32_t SystemCoreClock;

#include "board_definitions.h"

#include "power.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION			1
#define configUSE_IDLE_HOOK				0
#define configUSE_TICK_HOOK				0
#define configCPU_CLOCK_HZ				( CPU_FREQUENCY )
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )
#define configSYSTICK_CLOCK_HZ 			( ( TickType_t ) CPU_FREQUENCY )
#define configMAX_PRIORITIES			( 5 )
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 70 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 22000 ) )
#define configMAX_TASK_NAME_LEN			( 5 )
#define configUSE_TRACE_FACILITY		1
#define configUSE_16_BIT_TICKS			0
#define configIDLE_SHOULD_YIELD			1
#define configUSE_MUTEXES				1
#define configQUEUE_REGISTRY_SIZE		8
#define configCHECK_FOR_STACK_OVERFLOW	0
#define configUSE_RECURSIVE_MUTEXES		1
#define configUSE_MALLOC_FAILED_HOOK	0
#define configUSE_APPLICATION_TASK_TAG	0
#define configUSE_COUNTING_SEMAPHORES	1
#define configUSE_QUEUE_SETS			1
#define configUSE_TICKLESS_IDLE 		1
//#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP 2

#define configSUPPORT_STATIC_ALLOCATION 1
#define configSUPPORT_DYNAMIC_ALLOCATION 1	//For

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( 2 )
#define configTIMER_QUEUE_LENGTH		5
#define configTIMER_TASK_STACK_DEPTH	( 80 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1
#define INCLUDE_uxTaskGetStackHighWaterMark        1
#define INCLUDE_xTaskGetSchedulerState             1
#define INCLUDE_xTimerGetTimerTaskHandle           0
#define INCLUDE_xTaskGetIdleTaskHandle             0
#define INCLUDE_xQueueGetMutexHolder               1
#define INCLUDE_eTaskGetState			1
#define INCLUDE_xEventGroupSetBitsFromISR          1
#define INCLUDE_xTimerPendFunctionCall  1
#define INCLUDE_pcTaskGetTaskName                  1
#define INCLUDE_xTaskDelayUntil 1

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { portDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

/* The size of the global output buffer that is available for use when there
are multiple command interpreters running at once (for example, one on a UART
and one on TCP/IP).  This is done to prevent an output buffer being defined by
each implementation - which would waste RAM.  In this case, there is only one
command interpreter running. */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE 2048

#define configPRINTF(X)

#define configPRE_SLEEP_PROCESSING(time) time = hal_preSleep(time);
#define configPOST_SLEEP_PROCESSING(time) time = hal_postSleep(time);

#endif /* FREERTOS_CONFIG_H */
