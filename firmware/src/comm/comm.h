#ifndef INC_COMM_H_
#define INC_COMM_H_

#include <stdbool.h>
#include "transport_interface.h"

struct CommCtx_;
typedef struct CommCtx_ CommCtx;

#define MQTT_BROKER_ENDPOINT    "a1vgq6tp09249f-ats.iot.us-west-2.amazonaws.com"
#define MQTT_BROKER_PORT       ( 8883U )
#define MQTT_CLIENT_IDENTIFIER "arn:aws:iot:us-west-2:046241544403:thing/ema2022-nbiot-2"
#define MQTT_TOPIC             "test_topic"
#define MQTT_KEEPALIVE_SECONDS  ( 60U )

#define SEND_RECV_TIMEOUT_MS ( 5000U )

extern CommCtx *comm_init(void);

extern bool comm_process(CommCtx *ctx);

extern bool comm_connect(CommCtx *ctx, TransportInterface_t *transport_interface);

extern void comm_disconnect(CommCtx *ctx);

#endif
