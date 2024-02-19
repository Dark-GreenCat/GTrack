#ifndef __MC60_PAL_H
#define __MC60_PAL_H

#include <string.h>
#include "mc60_driver.h"

#define PAL_MC60_TIMEOUT           3000

typedef enum {
    MC60_POWER_OFF = 0,
    MC60_POWER_ON 
} mc60_state;

typedef enum {
    MC60_GNSS_POWER_OFF = 0,
    MC60_GNSS_POWER_ON 
} mc60_gnss_state;

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
void PAL_MC60_MQTT_Init(mc60_mqtt_t* mc60_mqtt);
bool PAL_MC60_IsRunning();
void PAL_MC60_PowerOn(mc60_state state);
void PAL_MC60_GNSS_PowerOn(mc60_gnss_state state);
void PAL_MC60_RunCommand(const char* cmd);
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

static inline int8_t PAL_MC60_MQTT_Publish(MC60_TypeDef* mc60, uint16_t message_id, mc60_mqtt_qos qos, bool retain, const char* topic, const char* message) {
    uint16_t message_length = strlen(message);
    return MC60_MQTT_Publish(&mc60->core, mc60->mqtt.tcpid, message_id, qos, retain, topic, message, message_length, mc60->timeout);
}


#endif