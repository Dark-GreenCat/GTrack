#ifndef __GTRACK_NAL_H
#define __GTRACK_NAL_H

#include "mc60/mc60_pal.h"
#include "display/display_pal.h"
#include "supplier/supplier_pal.h"

#define NAL_GTRACK_MQTT_TCP_ID          MC60_MQTT_TCP_CONNECT_ID_0
#define NAL_GTRACK_MQTT_PORT            1883
#define NAL_GTRACK_MQTT_MESSAGE_ID      ((uint16_t) 0)
#define NAL_GTRACK_MQTT_QOS             ((mc60_mqtt_qos) MC60_MQTT_QOS_AT_MOST_ONCE)
#define NAL_GTRACK_MQTT_RETAIN          ((bool) 0)

extern const char* mqtt_hostname;
extern const char* mqtt_clientid;
extern const char* mqtt_username;
extern const char* mqtt_password;
extern const char* mqtt_topic;

void NAL_GTrack_Init();

int8_t NAL_GTRACK_OpenNetwork();
int8_t NAL_GTRACK_ConnectBroker();
int8_t NAL_GTRACK_Disconnect();
int8_t NAL_GTRACK_PublishMessage(const char* message);

void NAL_GTRACK_Send(const char* message);

char* NAL_GTRACK_ConstructMessage(char* destination, nmea_data* data);

#endif