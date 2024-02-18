#ifndef __MC60_MQTT_H
#define __MC60_MQTT_H

#include <stdio.h>
#include "../../interface/mc60_interface.h"

typedef enum {
    MC60_MQTT_TCP_CONNECT_ID_0 = 0,
    MC60_MQTT_TCP_CONNECT_ID_1,
    MC60_MQTT_TCP_CONNECT_ID_2,
    MC60_MQTT_TCP_CONNECT_ID_3,
    MC60_MQTT_TCP_CONNECT_ID_4,
    MC60_MQTT_TCP_CONNECT_ID_5,
} mc60_mqtt_tcp_id;

typedef enum {
    MC60_MQTT_OPEN_FAILED_TO_OPEN_NETWORK = -1,
    MC60_MQTT_OPEN_NETWORK_OPENED_SUCCESS = 0,
    MC60_MQTT_OPEN_WRONG_PARAMETER = 1,
    MC60_MQTT_OPEN_MQTT_IDENTIFIER_OCCUPIED = 2,
    MC60_MQTT_OPEN_FAILED_TO_ACTIVATE_PDP = 3,
    MC60_MQTT_OPEN_FAILED_TO_PARSE_DOMAIN = 4,
    MC60_MQTT_OPEN_NETWORK_DISCONNECT_ERROR = 5
} mc60_mqtt_open_result;

int8_t MC60_MQTT_Open(mc60_t* mc60, uint8_t tcp_connect_id, const char* host_name, uint16_t port, uint32_t timeout);
int8_t MC60_MQTT_Connect(mc60_t* mc60, mc60_mqtt_tcp_id tcp_connect_id, const char* client_id, const char* user_name, const char* password, uint32_t timeout);

#endif