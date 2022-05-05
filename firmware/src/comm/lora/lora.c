#include "watermonitor.h"

#include <lmic.h>
#include <lmic_bandplan.h>


// application router ID (LSBF)
static const u1_t APPEUI[8]  = { 0x02, 0x00, 0x00, 0x00, 0x00, 0xEE, 0xFF, 0xC0 };

// unique device ID (LSBF)
static const u1_t DEVEUI[8]  = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };

// device-specific AES key (derived from device EUI)
static const u1_t DEVKEY[16] = { 0xAB, 0x89, 0xEF, 0xCD, 0x23, 0x01, 0x67, 0x45, 0x54, 0x76, 0x10, 0x32, 0xDC, 0xFE, 0x98, 0xBA };


//////////////////////////////////////////////////
// APPLICATION CALLBACKS
//////////////////////////////////////////////////

// provide application router ID (8 bytes, LSBF)
void os_getArtEui (u1_t* buf) {
    memcpy(buf, APPEUI, 8);
}

// provide device ID (8 bytes, LSBF)
void os_getDevEui (u1_t* buf) {
    memcpy(buf, DEVEUI, 8);
}

// provide device key (16 bytes)
void os_getDevKey (u1_t* buf) {
    memcpy(buf, DEVKEY, 16);
}

void onEvent (ev_t ev) {
    switch(ev) {

      // network joined, session established
      case EV_JOINED:
          // enable pinging mode, start scanning...
          // (set local ping interval configuration to 2^1 == 2 sec)
          LMIC_setPingable(1);
          break;

      // beacon found by scanning
      case EV_BEACON_FOUND:
          // send empty frame up to notify server of ping mode and interval!
          LMIC_sendAlive();
          break;

      // data frame received in ping slot
      case EV_RXCOMPLETE:
          // log frame data
          asm("BKPT");
          break;
      default: break;
    }
}

osjob_t initjob;

static void initfunc (osjob_t* j)
{
    // reset MAC state
    LMIC_reset();
    // start joining
    //LMIC_startJoining();
    LMIC_setTxData2(1, (unsigned char*) "Hello", 5, 0);
    // init done - onEvent() callback will be invoked...
}

CommCtx* comm_init( void )
{
    // LMIC init
    os_init();
    os_setCallback(&initjob, initfunc);

    return NULL;
}

bool comm_connect(CommCtx* ctx, TransportInterface_t* transport_interface)
{
	return false;
}

void comm_disconnect(CommCtx* ctx)
{

}

bool comm_process(CommCtx* ctx)
{
	  // execute scheduled jobs and events
	  os_runloop_once();
	  return false;
}

