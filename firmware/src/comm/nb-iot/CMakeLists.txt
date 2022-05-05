# cellular
set(CELLULAR_DIR_INC 
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/cellular/include
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/cellular/common/include
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/cellular/common/include/private
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/cellular/modules/bg96)

set(CELLULAR_DIR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/contrib/cellular)
set(CELLULAR_DIR_SRCS 
    ${CELLULAR_DIR_SRC}/common/src/cellular_3gpp_api.c
    ${CELLULAR_DIR_SRC}/common/src/cellular_3gpp_urc_handler.c
    ${CELLULAR_DIR_SRC}/common/src/cellular_at_core.c
    ${CELLULAR_DIR_SRC}/common/src/cellular_common_api.c
    ${CELLULAR_DIR_SRC}/common/src/cellular_common.c
    ${CELLULAR_DIR_SRC}/common/src/cellular_pkthandler.c
    ${CELLULAR_DIR_SRC}/common/src/cellular_pktio.c

	${CELLULAR_DIR_SRC}/modules/bg96/cellular_bg96.c
	${CELLULAR_DIR_SRC}/modules/bg96/cellular_bg96_wrapper.c
	${CELLULAR_DIR_SRC}/modules/bg96/cellular_bg96_urc_handler.c
	${CELLULAR_DIR_SRC}/modules/bg96/cellular_bg96_api.c)

# backoffAlgorithm
include(contrib/backoffAlgorithm/backoffAlgorithmFilePaths.cmake)

set(NBIOT_SRCS 
	${CELLULAR_DIR_SRCS}
	${BACKOFF_ALGORITHM_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/cellular_platform.c
	${CMAKE_CURRENT_SOURCE_DIR}/nbiot-uart.c
	${CMAKE_CURRENT_SOURCE_DIR}/nbiot-socket.c
	${CMAKE_CURRENT_SOURCE_DIR}/nbiot.c
	PARENT_SCOPE)
	
set(NBIOT_INCLUDES
	${BACKOFF_ALGORITHM_INCLUDE_PUBLIC_DIRS}
	${CELLULAR_DIR_INC}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE)
	
