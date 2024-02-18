#ifndef __MC60_PAL_H
#define __MC60_PAL_H

#include <string.h>
#include "mc60_driver.h"

#define PAL_MC60_TIMEOUT           3000

#define PAL_MC60_MQTT_TCP_ID       MC60_MQTT_TCP_CONNECT_ID_0
#define PAL_MC60_MQTT_PORT         1883
#define PAL_MC60_MQTT_MESSAGE_ID   0
#define PAL_MC60_MQTT_QOS          MC60_MQTT_QOS_AT_MOST_ONCE
#define PAL_MC60_MQTT_RETAIN       0

extern const char* mqtt_hostname;
extern const char* mqtt_clientid;
extern const char* mqtt_username;
extern const char* mqtt_password;
extern const char* mqtt_topic;

typedef struct {
    mc60_mqtt_tcp_id tcpid;
    uint16_t port;
    char* hostname;
    char* clientid;
    char* username;
    char* password;
} mc60_mqtt_t;

typedef struct {
    mc60_t core;
    mc60_mqtt_t mqtt;

    uint32_t timeout;
} MC60_TypeDef;

extern MC60_TypeDef pal_mc60;

void PAL_MC60_Init();
void PAL_MC60_MQTT_Init();
void PAL_MC60_PowerOn();
void PAL_MC60_MQTT_Send(const char* topic, const char* message);

static inline int8_t PAL_MC60_MQTT_Open(MC60_TypeDef* mc60) {
    return MC60_MQTT_Open(&mc60->core, mc60->mqtt.tcpid, mc60->mqtt.hostname, mc60->mqtt.port, mc60->timeout);
}

static inline int8_t PAL_MC60_MQTT_Connect(MC60_TypeDef* mc60) {
    return MC60_MQTT_Connect(&mc60->core, mc60->mqtt.tcpid, mc60->mqtt.clientid, mc60->mqtt.username, mc60->mqtt.password, mc60->timeout);
}

static inline int8_t PAL_MC60_MQTT_Disconnect(MC60_TypeDef* mc60) {
    return MC60_MQTT_Disconnect(&mc60->core, mc60->mqtt.tcpid, mc60->timeout);
}

static inline int8_t PAL_MC60_MQTT_Publish(MC60_TypeDef* mc60, const char* topic, const char* message) {
    uint16_t message_length = strlen(message);
    return MC60_MQTT_Publish(&mc60->core, mc60->mqtt.tcpid, PAL_MC60_MQTT_MESSAGE_ID, PAL_MC60_MQTT_QOS, PAL_MC60_MQTT_RETAIN, topic, message, message_length, mc60->timeout);
}


#endif