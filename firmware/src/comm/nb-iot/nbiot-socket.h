#ifndef COREMQTT_DRIVER
#define COREMQTT_DRIVER

/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

/* Logging related header files are required to be included in the following order:
 * 1. Include the header file "logging_levels.h".
 * 2. Define LIBRARY_LOG_NAME and  LIBRARY_LOG_LEVEL.
 * 3. Include the header file "logging_stack.h".
 */

/* Include header that defines log levels. */
#include "logging_levels.h"

/* Logging configuration for the Sockets. */
#ifndef LIBRARY_LOG_NAME
    #define LIBRARY_LOG_NAME     "TlsTransport"
#endif
#ifndef LIBRARY_LOG_LEVEL
    #define LIBRARY_LOG_LEVEL    LOG_ERROR
#endif

#include "logging_stack.h"

/************ End of logging configuration ****************/


/* Transport interface include. */
#include "transport_interface.h"

/* FreeRTOS Cellular Library include. */
#include "cellular_config.h"
#include "cellular_config_defaults.h"
#include "cellular_types.h"
#include "cellular_api.h"
#include "cellular_comm_interface.h"
#include "cellular_common.h"

struct NetworkContext
{
	CellularHandle_t cellHandle;
	CellularSocketHandle_t socket;
	 EventGroupHandle_t events;
};

typedef struct SockInfo_
{
	const char * host;
	uint16_t port;

	uint32_t receiveTimeoutMs;
	uint32_t sendTimeoutMs;

} SockInfo;

typedef enum SockError_
{
	SOCK_ERROR_SUCCESS,
	SOCK_ERROR_FAIL

} SockError;

#define SOCKET_OPENED_CALLBACK_BIT 1
#define SOCKET_DATA_RECV_CALLBACK_BIT 2
#define SOCKET_CLOSED_CALLBACK_BIT 3

SockError Sock_Connect( NetworkContext_t * pNetworkContext, CellularHandle_t handle, SockInfo* info);
SockError Sock_Disconnect( NetworkContext_t * pNetworkContext );

int32_t Sock_recv( NetworkContext_t * pNetworkContext, void * pBuffer, size_t bytesToRecv );
int32_t Sock_send( NetworkContext_t * pNetworkContext, const void * pBuffer, size_t bytesToSend );

#endif /* COREMQTT_DRIVER */
