/*
 * NB-IoT specific code
 *
 * 2021-2022 EMA YVR Capstone Group
 */

#include "comm.h"

#include <FreeRTOS.h>
#include <backoff_algorithm.h>
#include <task.h>
#include <pcg_basic.h>
#include <sam.h>
#include <stdbool.h>
#include <string.h>

#include "nbiot-uart.h"
#include "nbiot-socket.h"

struct CommCtx_
{
	NetworkContext_t network;
	CellularHandle_t cellular;
};

#define BACKOFF_BASE_MS ( 500U )
#define BACKOFF_MAX_DELAY_MS ( 5000U )
#define BACKOFF_MAX_ATTEMPTS ( 5U )

#define CELLULAR_SIM_CARD_WAIT_INTERVAL_MS       ( 500UL )
#define CELLULAR_MAX_SIM_RETRY                   ( 5U )
#define CELLULAR_PDN_CONNECT_WAIT_INTERVAL_MS    ( 1000UL )


CellularCommInterface_t pCommIntf = {
		.open = uart_open,
		.close = uart_close,
		.recv = uart_recv,
		.send = uart_send
};

bool setupCellular( CellularHandle_t* CellularHandle)
{
    bool cellularRet = true;
    CellularError_t cellularStatus = CELLULAR_SUCCESS;
    CellularSimCardStatus_t simStatus = { 0 };
    CellularServiceStatus_t serviceStatus = { 0 };

    uint8_t tries = 0;
    CellularPdnConfig_t pdnConfig = { CELLULAR_PDN_CONTEXT_IPV4, CELLULAR_PDN_AUTH_NONE, CELLULAR_APN, "", "" };
    CellularPdnStatus_t PdnStatusBuffers = { 0 };
    char localIP[ CELLULAR_IP_ADDRESS_MAX_SIZE ] = { '\0' };
    uint32_t timeoutCountLimit = ( CELLULAR_PDN_CONNECT_TIMEOUT / CELLULAR_PDN_CONNECT_WAIT_INTERVAL_MS ) + 1U;
    uint32_t timeoutCount = 0;
    uint8_t NumStatus = 1;

    /* Initialize Cellular Comm Interface. */
    cellularStatus = Cellular_Init( CellularHandle, &pCommIntf );

    if( cellularStatus == CELLULAR_SUCCESS )
    {
        /* wait until SIM is ready */
        for( tries = 0; tries < CELLULAR_MAX_SIM_RETRY; tries++ )
        {
            cellularStatus = Cellular_GetSimCardStatus( *CellularHandle, &simStatus );

            if( ( cellularStatus == CELLULAR_SUCCESS ) &&
                ( ( simStatus.simCardState == CELLULAR_SIM_CARD_INSERTED ) &&
                  ( simStatus.simCardLockState == CELLULAR_SIM_CARD_READY ) ) )
            {
                configPRINTF( ( ">>>  Cellular SIM okay  <<<\r\n" ) );
                break;
            }
            else
            {
                configPRINTF( ( ">>>  Cellular SIM card state %d, Lock State %d <<<\r\n",
                                simStatus.simCardState,
                                simStatus.simCardLockState ) );
            }

            vTaskDelay( pdMS_TO_TICKS( CELLULAR_SIM_CARD_WAIT_INTERVAL_MS ) );
        }
    }

    /* Setup the PDN config. */
    if( cellularStatus == CELLULAR_SUCCESS )
    {
        cellularStatus = Cellular_SetPdnConfig( *CellularHandle, CELLULAR_PDN_CONTEXT_ID, &pdnConfig );
    }
    else
    {
        configPRINTF( ( ">>>  Cellular SIM failure  <<<\r\n" ) );
    }

    /* Rescan network. */
    if( cellularStatus == CELLULAR_SUCCESS )
    {
        cellularStatus = Cellular_RfOff( *CellularHandle );
    }

    if( cellularStatus == CELLULAR_SUCCESS )
    {
        cellularStatus = Cellular_RfOn( *CellularHandle );
    }

    /* Get service status. */
    if( cellularStatus == CELLULAR_SUCCESS )
    {
        while( timeoutCount < timeoutCountLimit )
        {
            cellularStatus = Cellular_GetServiceStatus( *CellularHandle, &serviceStatus );

            if( ( cellularStatus == CELLULAR_SUCCESS ) &&
                ( ( serviceStatus.psRegistrationStatus == CELLULAR_NETWORK_REGISTRATION_STATUS_REGISTERED_HOME ) ||
                  ( serviceStatus.psRegistrationStatus == CELLULAR_NETWORK_REGISTRATION_STATUS_REGISTERED_ROAMING ) ) )
            {
                configPRINTF( ( ">>>  Cellular module registered  <<<\r\n" ) );
                break;
            }
            else
            {
                configPRINTF( ( ">>>  Cellular GetServiceStatus failed %d, ps registration status %d  <<<\r\n",
                                cellularStatus, serviceStatus.psRegistrationStatus ) );
            }

            timeoutCount++;

            if( timeoutCount >= timeoutCountLimit )
            {
                configPRINTF( ( ">>>  Cellular module can't be registered  <<<\r\n" ) );
            }

            vTaskDelay( pdMS_TO_TICKS( CELLULAR_PDN_CONNECT_WAIT_INTERVAL_MS ) );
        }
    }

    if( cellularStatus == CELLULAR_SUCCESS )
    {
        cellularStatus = Cellular_ActivatePdn( *CellularHandle, CELLULAR_PDN_CONTEXT_ID );
    }

    if( cellularStatus == CELLULAR_SUCCESS )
    {
        cellularStatus = Cellular_GetIPAddress( *CellularHandle, CELLULAR_PDN_CONTEXT_ID, localIP, sizeof( localIP ) );
    }

    if( cellularStatus == CELLULAR_SUCCESS )
    {
        cellularStatus = Cellular_GetPdnStatus( *CellularHandle, &PdnStatusBuffers, CELLULAR_PDN_CONTEXT_ID, &NumStatus );
    }

    if( ( cellularStatus == CELLULAR_SUCCESS ) && ( PdnStatusBuffers.state == 1 ) )
    {
        configPRINTF( ( ">>>  Cellular module registered, IP address %s  <<<\r\n", localIP ) );
        cellularRet = true;
    }
    else
    {
        cellularRet = false;
    }

    return cellularRet;
}

bool comm_process(CommCtx* ctx)
	{ return true; /* Not implemented for NB-IoT */ }

CommCtx* comm_init()
{
    CommCtx* ctx = pvPortMalloc(sizeof(struct CommCtx_));

    /* Setup UART */
    uart_init();

    /* Setup cellular. */
    setupCellular(&ctx->cellular);

    return ctx;
}

bool comm_connect(struct CommCtx_* ctx, TransportInterface_t* transport_interface)
{
	BackoffAlgorithmContext_t backoff;
    BackoffAlgorithm_InitializeParams( &backoff,
                                       BACKOFF_BASE_MS,
                                       BACKOFF_MAX_DELAY_MS,
                                       BACKOFF_MAX_ATTEMPTS );

    SockInfo socket = {0};
    socket.host = MQTT_BROKER_ENDPOINT;
    socket.port = MQTT_BROKER_PORT;
    socket.receiveTimeoutMs = SEND_RECV_TIMEOUT_MS;
    socket.sendTimeoutMs = SEND_RECV_TIMEOUT_MS;

    uint16_t nextBackoff;
    BackoffAlgorithmStatus_t backoff_status = BackoffAlgorithmSuccess;

    // Connect to AWS
    SockError socket_status = SOCK_ERROR_SUCCESS;
    do
    {
    	socket_status = Sock_Connect( &ctx->network, ctx->cellular, &socket);

        if( socket_status != SOCK_ERROR_SUCCESS )
        {
        	backoff_status = BackoffAlgorithm_GetNextBackoff( &backoff, pcg32_random(), &nextBackoff );

            if( backoff_status == BackoffAlgorithmRetriesExhausted )
            	{ return false; }
            else if( backoff_status == BackoffAlgorithmSuccess )
            	{ vTaskDelay( pdMS_TO_TICKS( nextBackoff ) ); }
        }
    } while( ( socket_status != SOCK_ERROR_SUCCESS ) && ( backoff_status == BackoffAlgorithmSuccess ) );

    transport_interface->send = Sock_send;
    transport_interface->recv = Sock_recv;
    transport_interface->pNetworkContext = &ctx->network;

    return true;
}

extern void comm_disconnect(struct CommCtx_* ctx)
{
	Sock_Disconnect(&ctx->network);
}
