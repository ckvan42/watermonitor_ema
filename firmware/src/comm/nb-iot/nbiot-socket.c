#include "nbiot-socket.h"

#include <task.h>

static TaskHandle_t xTaskToNotify = NULL;

void socketOpenCallback( CellularUrcEvent_t urcEvent,
						 CellularSocketHandle_t socketHandle,
						 void * netctx_ )
{
	NetworkContext_t* netctx = (NetworkContext_t*) netctx_;
	(void) xEventGroupSetBits( netctx->events, SOCKET_OPENED_CALLBACK_BIT);
}

void socketClosedCallback( CellularSocketHandle_t socketHandle,
						 void * netctx_ )
{
	NetworkContext_t* netctx = (NetworkContext_t*) netctx_;
	(void) xEventGroupSetBits( netctx->events, SOCKET_CLOSED_CALLBACK_BIT);
}

void socketDataReadyCallback( CellularSocketHandle_t socketHandle,
						 	  void * netctx_ )
{
	NetworkContext_t* netctx = (NetworkContext_t*) netctx_;
	(void) xEventGroupSetBits( netctx->events,SOCKET_DATA_RECV_CALLBACK_BIT );
}

SockError Sock_Connect( NetworkContext_t * pNetworkContext, CellularHandle_t handle, SockInfo* info)
{
	CellularSocketAddress_t pRemoteSocketAddress;
	pRemoteSocketAddress.port = info->port;
	pRemoteSocketAddress.ipAddress.ipAddressType = CELLULAR_IP_ADDRESS_V4;
	memcpy(pRemoteSocketAddress.ipAddress.ipAddress, info->host, 65);

	pNetworkContext->cellHandle = handle;
	pNetworkContext->events = xEventGroupCreate();

	Cellular_ATCommandRaw(pNetworkContext->cellHandle,
			NULL,
			"AT+QSSLCFG=\"cacert\",0,\"AmazonRootCA1.pem\"",
			CELLULAR_AT_NO_RESULT,
			NULL, NULL, 0);

	Cellular_ATCommandRaw(pNetworkContext->cellHandle,
				NULL,
				"AT+QSSLCFG=\"clientcert\",0,\"certificate.pem.crt\"",
				CELLULAR_AT_NO_RESULT,
				NULL, NULL, 0);
	Cellular_ATCommandRaw(pNetworkContext->cellHandle,
				NULL,
				"AT+QSSLCFG=\"clientkey\",0,\"private.pem.key\"",
				CELLULAR_AT_NO_RESULT,
				NULL, NULL, 0);
	Cellular_ATCommandRaw(pNetworkContext->cellHandle,
				NULL,
				"AT+QSSLCFG=\"ciphersuite\",0,0xFFFF",
				CELLULAR_AT_NO_RESULT,
				NULL, NULL, 0);
	Cellular_ATCommandRaw(pNetworkContext->cellHandle,
				NULL,
				"AT+QSSLCFG=\"seclevel\",0,2",
				CELLULAR_AT_NO_RESULT,
				NULL, NULL, 0);
	Cellular_ATCommandRaw(pNetworkContext->cellHandle,
				NULL,
				"AT+QSSLCFG=\"sslversion\",0,4",
				CELLULAR_AT_NO_RESULT,
				NULL, NULL, 0);



	Cellular_CreateSocket(pNetworkContext->cellHandle,
			1,
			CELLULAR_SOCKET_DOMAIN_AF_INET,
			CELLULAR_SOCKET_TYPE_STREAM,
			CELLULAR_SOCKET_PROTOCOL_TCP,
			&pNetworkContext->socket);
	xTaskToNotify = xTaskGetCurrentTaskHandle();
	Cellular_SocketConnect(pNetworkContext->cellHandle, pNetworkContext->socket, CELLULAR_ACCESSMODE_BUFFER, &pRemoteSocketAddress);
	Cellular_SocketRegisterSocketOpenCallback(pNetworkContext->cellHandle, pNetworkContext->socket,
			socketOpenCallback, pNetworkContext);
	Cellular_SocketRegisterClosedCallback(pNetworkContext->cellHandle, pNetworkContext->socket,
			socketClosedCallback, pNetworkContext);
	Cellular_SocketRegisterDataReadyCallback(pNetworkContext->cellHandle, pNetworkContext->socket,
				socketDataReadyCallback, pNetworkContext);
	if(xEventGroupWaitBits(pNetworkContext->events, SOCKET_OPENED_CALLBACK_BIT, pdTRUE, pdFALSE, pdMS_TO_TICKS( 10000 )))
		return SOCK_ERROR_SUCCESS;
	else
		return SOCK_ERROR_FAIL;
}

SockError Sock_Disconnect( NetworkContext_t * pNetworkContext )
{
	Cellular_SocketClose(pNetworkContext->cellHandle, pNetworkContext->socket);
	if(xEventGroupWaitBits(pNetworkContext->events, SOCKET_CLOSED_CALLBACK_BIT, pdTRUE, pdFALSE, pdMS_TO_TICKS( 10000 )))
		return SOCK_ERROR_SUCCESS;
	else
		return SOCK_ERROR_FAIL;
}

int32_t Sock_recv( NetworkContext_t * pNetworkContext, void * pBuffer, size_t bytesToRecv )
{
	uint32_t recvlen;
	Cellular_SocketRecv(pNetworkContext->cellHandle, pNetworkContext->socket, pBuffer, bytesToRecv, &recvlen);
	return recvlen;
}

int32_t Sock_send( NetworkContext_t * pNetworkContext, const void * pBuffer, size_t bytesToSend )
{
	uint32_t sendlen;
	Cellular_SocketSend(pNetworkContext->cellHandle, pNetworkContext->socket, pBuffer, bytesToSend, &sendlen);
	return sendlen;
}
