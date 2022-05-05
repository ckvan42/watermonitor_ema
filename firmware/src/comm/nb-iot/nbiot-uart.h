/* Low-Level Communication Interface - Header.

	2021 EMA YVR Capstone Group
 */

#ifndef NB_IOT_UART_H_
#define NB_IOT_UART_H_

#include "cellular_config.h"
#include "cellular_config_defaults.h"
#include "cellular_types.h"
#include "cellular_api.h"
#include "cellular_comm_interface.h"
#include "cellular_common.h"

// Initialize the UART
extern void uart_init( void );

extern void ph_uart_init( void );

extern void conductivity_uart_init( void );

extern CellularCommInterfaceError_t
uart_open( CellularCommInterfaceReceiveCallback_t receiveCallback,
		   void * pUserData,
		   CellularCommInterfaceHandle_t * pCommInterfaceHandle );

extern CellularCommInterfaceError_t
uart_close( CellularCommInterfaceHandle_t commInterfaceHandle );

extern CellularCommInterfaceError_t
uart_send( CellularCommInterfaceHandle_t commInterfaceHandle,
		   const uint8_t * pData,
		   uint32_t dataLength,
		   uint32_t timeoutMilliseconds,
		   uint32_t * pDataSentLength );

extern CellularCommInterfaceError_t
uart_recv( CellularCommInterfaceHandle_t commInterfaceHandle,
           uint8_t * pBuffer,
           uint32_t bufferLength,
           uint32_t timeoutMilliseconds,
           uint32_t * pDataReceivedLength );

#endif /* NB_IOT_UART_H_ */
