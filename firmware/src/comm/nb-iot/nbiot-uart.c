/* Low-Level Communication Interface - Source.

	2021 EMA YVR Capstone Group
 */

#include <sam.h>

/* Platform layer includes. */
#include "cellular_config.h"
#include "cellular_config_defaults.h"
#include "cellular_comm_interface.h"

#include "FreeRTOS.h"

#include "stream_buffer.h"
#include "task.h"
#include "cellular_platform.h"

struct CellularCommInterfaceContext {
	CellularCommInterfaceReceiveCallback_t receiveCallback;
	void* pUserData;
	StreamBufferHandle_t streambuf;

} localCommInterfaceContext;

void demo_uart(void) __attribute__((unused));
void demo_uart(void)
{
    // Mux C for A16 and A18
    PORT->Group[0].PINCFG[16].bit.PMUXEN = 1;
    PORT->Group[0].PINCFG[18].bit.PMUXEN = 1;
    PORT->Group[0].PMUX[8].bit.PMUXE = 0x02;
    PORT->Group[0].PMUX[9].bit.PMUXE = 0x02;

    PM->APBCMASK.bit.SERCOM1_ = 1;

    GCLK->CLKCTRL.bit.GEN = 0;
    GCLK->CLKCTRL.bit.CLKEN = 1;
    GCLK->CLKCTRL.bit.ID = 0x15;

    SERCOM1->USART.CTRLA.bit.SWRST = 1;
    SERCOM1->USART.CTRLA.bit.ENABLE = 0;
    while(SERCOM1->USART.SYNCBUSY.bit.ENABLE)
    	{ continue; }

    SERCOM1->USART.CTRLA.bit.MODE = 1;
    // Pin 2 -> RX
    // Pin 0 -> TX
    SERCOM1->USART.CTRLA.bit.TXPO = 0;
    SERCOM1->USART.CTRLA.bit.RXPO = 2;
    SERCOM1->USART.CTRLA.bit.FORM = 0;
    SERCOM1->USART.CTRLA.bit.DORD = 1;
    SERCOM1->USART.CTRLA.bit.CMODE = 0;

    SERCOM1->USART.BAUD.USARTFP.BAUD =
    		65536.0f*(1.0f-16.0f*NB_IOT_BAUD_RATE/MAIN_FREQUENCY);

    while(SERCOM1->USART.SYNCBUSY.bit.CTRLB)
    	{ continue; }
    SERCOM1->USART.CTRLB.bit.TXEN = 1;
    SERCOM1->USART.CTRLB.bit.RXEN = 1;

    SERCOM1->USART.CTRLA.bit.ENABLE = 1;

    while(1)
    {
    	while(!SERCOM1->USART.INTFLAG.bit.DRE)
    		{ continue; }
    	SERCOM1->USART.DATA.bit.DATA = 'H';
    }
}

void uart_init(void) {
	// Mux C for A16 and A18
	PORT->Group[0].PINCFG[16].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[18].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[8].bit.PMUXE = 0x02;
	PORT->Group[0].PMUX[9].bit.PMUXE = 0x02;

	PM->APBCMASK.bit.SERCOM1_ = 1;

	GCLK->CLKCTRL.bit.GEN = 0;
	GCLK->CLKCTRL.bit.CLKEN = 1;
	GCLK->CLKCTRL.bit.ID = 0x15;

	SERCOM1->USART.CTRLA.bit.SWRST = 1;
	SERCOM1->USART.CTRLA.bit.ENABLE = 0;
	while(SERCOM1->USART.SYNCBUSY.bit.ENABLE)
		{ continue; }

	SERCOM1->USART.CTRLA.bit.MODE = 1;
	// Pin 2 -> RX
	// Pin 0 -> TX
	SERCOM1->USART.CTRLA.bit.TXPO = 0;
	SERCOM1->USART.CTRLA.bit.RXPO = 2;
	SERCOM1->USART.CTRLA.bit.FORM = 0;
	SERCOM1->USART.CTRLA.bit.DORD = 1;
	SERCOM1->USART.CTRLA.bit.CMODE = 0;

	SERCOM1->USART.BAUD.USARTFP.BAUD =
			65536.0f*(1.0f-16.0f*NB_IOT_BAUD_RATE/(MAIN_FREQUENCY));

	while(SERCOM1->USART.SYNCBUSY.bit.CTRLB)
		{ continue; }
	SERCOM1->USART.CTRLB.bit.SBMODE = 1;
	SERCOM1->USART.CTRLB.bit.TXEN = 1;
	SERCOM1->USART.CTRLB.bit.RXEN = 1;

	SERCOM1->USART.INTENSET.bit.RXC = 1;

	NVIC_SetPriority(SERCOM1_IRQn, 3);
	NVIC_EnableIRQ(SERCOM1_IRQn);

	SERCOM1->USART.CTRLA.bit.ENABLE = 1;
}


//Pins 8 (PA 6) and 9 (PA7)
//Pin 8 is Tx, pin 9 is Rx
void ph_uart_init( void )
{
	PORT->Group[0].PINCFG[6].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[7].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[3].bit.PMUXE = 0x03;
	PORT->Group[0].PMUX[3].bit.PMUXO = 0x03;

	PM->APBCMASK.bit.SERCOM0_ = 1;

	GCLK->CLKCTRL.bit.GEN = 0;
	GCLK->CLKCTRL.bit.CLKEN = 1;
	GCLK->CLKCTRL.bit.ID = 0x14;

	SERCOM0->USART.CTRLA.bit.SWRST = 1;
	SERCOM0->USART.CTRLA.bit.ENABLE = 0;
	while(SERCOM0->USART.SYNCBUSY.bit.ENABLE)
		{ continue; }


	SERCOM0->USART.CTRLA.bit.MODE = 1;

	//PAD2 = PA6 = pin8 = Tx
	//PAD3 = PA7 = pin9 = Rx
    SERCOM0->USART.CTRLA.bit.TXPO = 1;
    SERCOM0->USART.CTRLA.bit.RXPO = 3;

    //Check this
    SERCOM0->USART.CTRLA.bit.DORD = 0; //MSB first
    SERCOM0->USART.CTRLA.bit.FORM = 0; //No Parity
    SERCOM0->USART.CTRLA.bit.CMODE = 0;

	SERCOM0->USART.CTRLB.bit.TXEN = 1;
	SERCOM0->USART.CTRLB.bit.RXEN = 1;

	SERCOM0->USART.BAUD.USARTFP.BAUD =
			65536.0f*(1.0f-16.0f*9600.0f/SystemCoreClock);

	SERCOM0->USART.CTRLB.bit.SBMODE = 0; //one stop bit
	SERCOM0->USART.INTENSET.bit.RXC = 1;

//	NVIC_SetPriority(SERCOM0_IRQn, 3);
//	NVIC_EnableIRQ(SERCOM0_IRQn);

	SERCOM0->USART.CTRLA.bit.ENABLE = 1;

}

//pins 3 (PA9, sercom2pad1) and 4 (PA8, sercom2pad0),
//pin 3 is Tx, pin 4 is Rx
void conductivity_uart_init ( void )
{
	PORT->Group[0].PINCFG[8].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[9].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[4].bit.PMUXE = 0x03;
	PORT->Group[0].PMUX[4].bit.PMUXO = 0x03;

	PM->APBCMASK.bit.SERCOM2_ = 1;

	GCLK->CLKCTRL.bit.GEN = 0;
	GCLK->CLKCTRL.bit.CLKEN = 1;
	GCLK->CLKCTRL.bit.ID = 0x16;

	SERCOM2->USART.CTRLA.bit.SWRST = 1;
	SERCOM2->USART.CTRLA.bit.ENABLE = 0;
	while(SERCOM2->USART.SYNCBUSY.bit.ENABLE)
		{ continue; }

	SERCOM2->USART.CTRLA.bit.MODE = 1;

	//PAD0 = PA8 = pin4 = Tx
	//PAD1 = PA9 = pin3 = Rx
    SERCOM2->USART.CTRLA.bit.TXPO = 0;
    SERCOM2->USART.CTRLA.bit.RXPO = 1;

    //Check this
    SERCOM2->USART.CTRLA.bit.DORD = 1; //LSB first
    SERCOM2->USART.CTRLA.bit.FORM = 0; //No Parity
    SERCOM2->USART.CTRLA.bit.CMODE = 0;

	SERCOM2->USART.CTRLB.bit.TXEN = 1;
	SERCOM2->USART.CTRLB.bit.RXEN = 1;

	SERCOM2->USART.BAUD.USARTFP.BAUD =
			65536.0f*(1.0f-16.0f*9600.0f/SystemCoreClock);

	SERCOM2->USART.CTRLB.bit.SBMODE = 0; //one stop bit
	SERCOM2->USART.INTENSET.bit.RXC = 1;

//	NVIC_SetPriority(SERCOM2_IRQn, 3);
//	NVIC_EnableIRQ(SERCOM2_IRQn);


	SERCOM2->USART.CTRLA.bit.ENABLE = 1;
}


uint16_t ph_sercom_data;
void SERCOM0_Handler(void)
{
	ph_sercom_data = SERCOM0->USART.DATA.bit.DATA;

}

uint16_t ec_sercom_data;
void SERCOM2_Handler(void)
{
	ec_sercom_data = SERCOM2->USART.DATA.bit.DATA;
}

void SERCOM1_Handler(void)
{
	uint16_t data = SERCOM1->USART.DATA.bit.DATA;
	BaseType_t needYield = false;
	if(localCommInterfaceContext.streambuf)
	{
		xStreamBufferSendFromISR(localCommInterfaceContext.streambuf,
		                                 &data,
		                                 1,
		                                 &needYield );
	}
	if(localCommInterfaceContext.receiveCallback)
	{
		CellularCommInterfaceError_t err =
				localCommInterfaceContext.receiveCallback(localCommInterfaceContext.pUserData, &localCommInterfaceContext);
		if(err == IOT_COMM_INTERFACE_SUCCESS)
			{ needYield = true;	}
	}

	if(needYield)
		{ portYIELD_FROM_ISR( true ); }
}

CellularCommInterfaceError_t uart_open( CellularCommInterfaceReceiveCallback_t receiveCallback,
                                                      void * pUserData,
                                                      CellularCommInterfaceHandle_t * pCommInterfaceHandle )
{
	CellularCommInterfaceError_t commIntRet = IOT_COMM_INTERFACE_SUCCESS;

	*pCommInterfaceHandle = (CellularCommInterfaceHandle_t)&localCommInterfaceContext;

	localCommInterfaceContext.streambuf = xStreamBufferCreate(50, 1);

	localCommInterfaceContext.pUserData = pUserData;
	localCommInterfaceContext.receiveCallback = receiveCallback;
	return commIntRet;
}

CellularCommInterfaceError_t uart_close( CellularCommInterfaceHandle_t commInterfaceHandle )
{
	CellularCommInterfaceError_t commIntRet = IOT_COMM_INTERFACE_SUCCESS;

	vStreamBufferDelete(localCommInterfaceContext.streambuf);
	localCommInterfaceContext.streambuf = NULL;

    return commIntRet;
}

CellularCommInterfaceError_t uart_send( CellularCommInterfaceHandle_t commInterfaceHandle,
                                                      const uint8_t * pData,
                                                      uint32_t dataLength,
                                                      uint32_t timeoutMilliseconds,
                                                      uint32_t * pDataSentLength )
{
	CellularCommInterfaceError_t commIntRet = IOT_COMM_INTERFACE_SUCCESS;
	*pDataSentLength = 0;
	TickType_t endTicks = xTaskGetTickCount() + pdMS_TO_TICKS(timeoutMilliseconds);
	while(dataLength)
	{
		while(!SERCOM1->USART.INTFLAG.bit.DRE)
		{
			if(xTaskGetTickCount() >= endTicks)
			{
				commIntRet = IOT_COMM_INTERFACE_TIMEOUT;
				return commIntRet;
			}
		}
		SERCOM1->USART.DATA.bit.DATA = *pData;
		pData ++;
		dataLength --;
		*pDataSentLength = *pDataSentLength + 1;
	}
	return commIntRet;
}

CellularCommInterfaceError_t uart_recv( CellularCommInterfaceHandle_t commInterfaceHandle,
                                                         uint8_t * pBuffer,
                                                         uint32_t bufferLength,
                                                         uint32_t timeoutMilliseconds,
                                                         uint32_t * pDataReceivedLength )
{
	CellularCommInterfaceError_t commIntRet = IOT_COMM_INTERFACE_SUCCESS;
	*pDataReceivedLength = xStreamBufferReceive(localCommInterfaceContext.streambuf, pBuffer, bufferLength,
			pdMS_TO_TICKS(timeoutMilliseconds));

	return commIntRet;
}
