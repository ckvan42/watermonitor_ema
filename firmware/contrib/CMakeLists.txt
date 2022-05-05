# FreeRTOS
set(FreeRTOS_DIR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/Source)
set(FreeRTOS_DIR_INC 
	${FreeRTOS_DIR_SRC}/include
	${FreeRTOS_DIR_SRC}/portable/GCC/ARM_CM0)
set(FreeRTOS_SRCS
	${FreeRTOS_DIR_SRC}/timers.c
	${FreeRTOS_DIR_SRC}/tasks.c
	${FreeRTOS_DIR_SRC}/stream_buffer.c
	${FreeRTOS_DIR_SRC}/queue.c
	${FreeRTOS_DIR_SRC}/list.c
	${FreeRTOS_DIR_SRC}/event_groups.c
	${FreeRTOS_DIR_SRC}/croutine.c
	${FreeRTOS_DIR_SRC}/portable/GCC/ARM_CM0/port.c
	${FreeRTOS_DIR_SRC}/portable/MemMang/heap_2.c)

# pcg_basic
set(PCG_DIR_INC ${CMAKE_CURRENT_SOURCE_DIR}/pcg_basic)
set(PCG_DIR_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/pcg_basic/pcg_basic.c)

# coreMQTT
include(coreMQTT/mqttFilePaths.cmake)

set(CONTRIB_INCLUDES
	${FreeRTOS_DIR_INC} 
	${PCG_DIR_INC} 
	${MQTT_INCLUDE_PUBLIC_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/hri
    ${CMAKE_CURRENT_SOURCE_DIR}/hpl
    ${LoRaMAC_INCLUDES}
	PARENT_SCOPE)

set(CONTRIB_SRCS
	${FreeRTOS_SRCS}
	${PCG_DIR_SRCS}
	${MQTT_SOURCES}
    ${MQTT_SERIALIZER_SOURCES}
	PARENT_SCOPE)
