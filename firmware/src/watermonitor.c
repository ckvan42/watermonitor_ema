#include <sys/cdefs.h>
/*
 * Main Water Monitor Source File
 *
 * 2021-2022 EMA YVR Capstone Group
 */

#include "comm.h"

#include <sam.h>
#include <stdbool.h>
#include <string.h>
#include <pcg_basic.h>

// Include JSON Generation library
#include "json.h"
#define MAX_JSON_STRING_LENGTH 256

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>
#include <stdint.h>

#include "board_definitions.h"
#include "sensor.h"

#include <core_mqtt.h>

extern void board_init(void);

uint32_t SystemCoreClock = CPU_FREQUENCY;

static uint8_t mqtt_buffer[1024U];

MQTTFixedBuffer_t mqtt_buffer_ref =
        {mqtt_buffer, 1024U};

uint32_t mqtt_get_time(void) {
    TickType_t xTickCount = 0;
    uint32_t ulTimeMs = 0UL;

    /* Get the current tick count. */
    xTickCount = xTaskGetTickCount();

    /* Convert the ticks to milliseconds. */
    ulTimeMs = (uint32_t) xTickCount / portTICK_RATE_MS;

    return ulTimeMs;
}

void mqtt_event_callback(MQTTContext_t *pxMQTTContext,
                         MQTTPacketInfo_t *pxPacketInfo,
                         MQTTDeserializedInfo_t *pxDeserializedInfo) {

}

_Noreturn static void uart_test(void *pvParameters) __attribute__((unused));
_Noreturn static void uart_test(void *pvParameters)
{
	//char message[] = "L,0";// = 'a';
    char message[10];
	//int val = 0;
	while(1)
	{
		while(!(SERCOM2->USART.INTFLAG.bit.RXC)){}
        message[0] = SERCOM2->USART.DATA.reg;
        
        // for(int i = 0; i < strlen(message); i++)
        //     {
        //         while(!(SERCOM2->USART.INTFLAG.bit.DRE)){}
                
        //         SERCOM2->USART.DATA.reg = message[i];    
        //     } 0   
        SERCOM2->USART.DATA.reg = message[0]+32;  
        vTaskDelay(1000 * portTICK_RATE_MS);
	}
}


_Noreturn static void WaterMonitorTask(void *pvParameters) __attribute__((unused));
_Noreturn static void WaterMonitorTask(void *pvParameters) {
    MQTTContext_t mqtt;
    CommCtx *ctx = comm_init();

    Sensor sensor_ec;
	sensor_ec = sensor_init(0, EC);

    while (1) {
        if (!comm_process(ctx)) { continue; }

        // ADDED BY SENSOR TEAM
        // *******************************************
        JsonNode* json_data_object = json_mkobject();

        // Take Sensor Measurements
        sensor_ec->measure(sensor_ec);
		sensor_ec->convert(sensor_ec);

        json_append_member(json_data_object, "ec", json_mknumber(sensor_ec->value_output));

        char buffer[MAX_JSON_STRING_LENGTH] = {0};
        char* data_payload = json_stringify(json_data_object, buffer);
        // *******************************************

        // Setup MQTT communication
        TransportInterface_t mqtt_interface;
        // Connect to server
        configASSERT(comm_connect(ctx, &mqtt_interface));

        MQTT_Init(&mqtt, &mqtt_interface, mqtt_get_time, mqtt_event_callback, &mqtt_buffer_ref);

        MQTTConnectInfo_t mqtt_connect_info = {0};
        mqtt_connect_info.cleanSession = true;
        mqtt_connect_info.pClientIdentifier = MQTT_CLIENT_IDENTIFIER;
        mqtt_connect_info.clientIdentifierLength = (uint16_t) strlen(MQTT_CLIENT_IDENTIFIER);
        mqtt_connect_info.keepAliveSeconds = MQTT_KEEPALIVE_SECONDS;

        bool session_present;

        MQTT_Connect(&mqtt,
                     &mqtt_connect_info,
                     NULL,
                     SEND_RECV_TIMEOUT_MS,
                     &session_present);

        // Publish!!
        MQTTPublishInfo_t publish = {0};
        publish.qos = MQTTQoS1;
        publish.retain = false;
        publish.pTopicName = MQTT_TOPIC;
        publish.topicNameLength = (uint16_t) strlen(MQTT_TOPIC);
        publish.pPayload = data_payload;
        publish.payloadLength = strlen(data_payload);

        MQTT_Publish(&mqtt, &publish, MQTT_GetPacketId(&mqtt));

        // Disconnect
        MQTT_Disconnect(&mqtt);
        comm_disconnect(ctx);

        vPortFree(data_payload);
		data_payload = NULL;
		json_delete(json_data_object);
		sensor_reset(sensor_ec);

        // Wait a bit
        vTaskDelay(1000 * portTICK_RATE_MS);
    }
    sensor_destroy(sensor_ec);
}

_Noreturn static void TestComm(void *pvParameters) __attribute__((unused));
_Noreturn static void TestComm(void *pvParameters) {
	MQTTContext_t mqtt;
	CommCtx *ctx = comm_init();

	while (1) {
		if (!comm_process(ctx)) { continue; }

		// Setup MQTT communication
		TransportInterface_t mqtt_interface;
		// Connect to server
		configASSERT(comm_connect(ctx, &mqtt_interface));

		MQTT_Init(&mqtt, &mqtt_interface, mqtt_get_time, mqtt_event_callback, &mqtt_buffer_ref);

		MQTTConnectInfo_t mqtt_connect_info = {0};
		mqtt_connect_info.cleanSession = true;
		mqtt_connect_info.pClientIdentifier = MQTT_CLIENT_IDENTIFIER;
		mqtt_connect_info.clientIdentifierLength = (uint16_t) strlen(MQTT_CLIENT_IDENTIFIER);
		mqtt_connect_info.keepAliveSeconds = MQTT_KEEPALIVE_SECONDS;

		bool session_present;

		MQTT_Connect(&mqtt,
					 &mqtt_connect_info,
					 NULL,
					 SEND_RECV_TIMEOUT_MS,
					 &session_present);

		// Publish!!
		MQTTPublishInfo_t publish = {0};
		publish.qos = MQTTQoS1;
		publish.retain = false;
		publish.pTopicName = MQTT_TOPIC;
		publish.topicNameLength = (uint16_t) strlen(MQTT_TOPIC);
		publish.pPayload = "Hello, World!";
		publish.payloadLength = strlen("Hello, World!");

		MQTT_Publish(&mqtt, &publish, MQTT_GetPacketId(&mqtt));

		// Disconnect
		MQTT_Disconnect(&mqtt);
		comm_disconnect(ctx);

		// Wait a bit
		vTaskDelay(1000 * portTICK_RATE_MS);
	}
}

_Noreturn static void TestSensorsTask(void *pvParameters) __attribute__((unused));
_Noreturn static void TestSensorsTask(void *pvParameters) {
	Sensor sensor_ec;
	sensor_ec = sensor_init(0, EC);

    while (1) {
        // ADDED BY SENSOR TEAM

    	sensor_ec->measure(sensor_ec);
		sensor_ec->convert(sensor_ec);

        // Wait a bit
        vTaskDelay(5000 * portTICK_RATE_MS);
        sensor_reset(sensor_ec);
    }
    sensor_destroy(sensor_ec);
}

_Noreturn static void TestJSONTask(void *pvParameters) __attribute__((unused));
_Noreturn static void TestJSONTask(void *pvParameters) {
	while (1) {
		JsonNode* json_data_object = json_mkobject();

		json_append_member(json_data_object, "ec", json_mknumber(10.003));

		char buffer[MAX_JSON_STRING_LENGTH] = {0};
		char* data_payload = json_stringify(json_data_object, buffer);


		vPortFree(data_payload);
		data_payload = NULL;
		json_delete(json_data_object);

		// Wait a bit
		vTaskDelay(1000 * portTICK_RATE_MS);
	}
}

_Noreturn static void TestJSONSensorTask(void *pvParameters) __attribute__((unused));
_Noreturn static void TestJSONSensorTask(void *pvParameters) {
	Sensor sensor_ec;
	sensor_ec = sensor_init(0, EC);

	while (1) {
		JsonNode* json_data_object = json_mkobject();

		sensor_ec->measure(sensor_ec);
	    sensor_ec->convert(sensor_ec);

		json_append_member(json_data_object, "ec", json_mknumber(sensor_ec->value_output));
		//json_append_member(json_data_object, "ec", json_mknumber(10.03));
		char buffer[MAX_JSON_STRING_LENGTH] = {0};
		char* data_payload = json_stringify(json_data_object, buffer);


		vPortFree(data_payload);
		data_payload = NULL;
		json_delete(json_data_object);
		sensor_reset(sensor_ec);

		// Wait a bit
		vTaskDelay(1000 * portTICK_RATE_MS);
	}
	sensor_destroy(sensor_ec);
}

int main(void) {
    board_init();
    __disable_irq();

    pcg32_srandom(0x3AB32C5C21459B, 0x2BC5913);

    xTaskCreate(uart_test,         /* Function that implements the task. */
                "WaterMonitor",           /* Text name for the task - only used for debugging. */
                1000, /* Size of stack (in words, not bytes) to allocate for the task. */
                NULL,                     /* Task parameter - not used in this case. */
                1,  /* Task priority, must be between 0 and configMAX_PRIORITIES - 1. */
                NULL);                   /* Used to pass out a handle to the created task - not used in this case. */

    /* Start the RTOS scheduler. */
    vTaskStartScheduler();

    for (;;) { asm("BKPT"); }
}

UBaseType_t uxRand(void) { return pcg32_random(); }

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    /* If the buffers to be provided to the Idle task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
     * state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize) {
    /* If the buffers to be provided to the Timer task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

