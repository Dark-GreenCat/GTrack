#include "gtrack_nal.h"

const char* mqtt_hostname = "demo.thingsboard.io";
const char* mqtt_clientid = "demo.thingsboard.io";
const char* mqtt_username = "3QcnES9LsYKtGIIXxNXU";
const char* mqtt_password = "";
const char* mqtt_topic = "v1/devices/me/telemetry";

void NAL_GTrack_Init() {
    mc60_mqtt_t mqtt = {
        .tcpid = NAL_GTRACK_MQTT_TCP_ID,
        .port = NAL_GTRACK_MQTT_PORT,
        .hostname = (char*)mqtt_hostname,
        .clientid = (char*)mqtt_clientid,
        .username = (char*)mqtt_username,
        .password = (char*)mqtt_password
    };

    PAL_MC60_MQTT_Init(&mqtt);
}

int8_t NAL_GTRACK_OpenNetwork() {
    return PAL_MC60_MQTT_Open(&pal_mc60);
}

int8_t NAL_GTRACK_ConnectBroker() {
    return PAL_MC60_MQTT_Connect(&pal_mc60);
}

int8_t NAL_GTRACK_Disconnect() {
    return PAL_MC60_MQTT_Disconnect(&pal_mc60);
}

int8_t NAL_GTRACK_PublishMessage(const char* message) {
    return PAL_MC60_MQTT_Publish(&pal_mc60, NAL_GTRACK_MQTT_MESSAGE_ID, NAL_GTRACK_MQTT_QOS, NAL_GTRACK_MQTT_RETAIN, mqtt_topic, message);
}

void NAL_GTRACK_Send(const char* message) {
    bool isMQTTOpen = false;
    bool isSuccess = false;
    int8_t result;

    uint32_t timestart = HAL_GetTick();
    while (HAL_GetTick() - timestart < pal_mc60.timeout) {
        if (!isMQTTOpen) {
            PAL_UART_OutString(huart_terminal, "\n*** Opening MQTT connection...");
            result = NAL_GTRACK_OpenNetwork();
            isSuccess = (result == 0 || result == 2);
            PAL_UART_OutString(huart_terminal, "\nResult code: "); PAL_UART_OutNumber_Signed(huart_terminal, result);
            if (!isSuccess) {
                if (result == 3) {
                    PAL_UART_OutString(huart_terminal, "\nFailed to setup PDP context. Restarting GTrack...");
                    NVIC_SystemReset();
                }
                PAL_UART_OutString(huart_terminal, "\nFailed to open MQTT connection. Retrying in 3 seconds...");
                continue;
            }

            isMQTTOpen = true;
        }

        PAL_UART_OutString(huart_terminal, "\n*** Connecting MQTT broker...");
        result = NAL_GTRACK_ConnectBroker();
        PAL_UART_OutString(huart_terminal, "\nResult code: "); PAL_UART_OutNumber_Signed(huart_terminal, result);
        isSuccess = (result == 0 || result == 1);
        if (!isSuccess) {
            PAL_UART_OutString(huart_terminal, "\nFailed to connect to MQTT broker. Retrying in 3 seconds...");
            NAL_GTRACK_Disconnect();
            isMQTTOpen = false;
            continue;
        }

        PAL_UART_OutString(huart_terminal, "\n*** Publishing MQTT message: ");
        PAL_UART_OutString(huart_terminal, message);
        result = NAL_GTRACK_PublishMessage(message);
        PAL_UART_OutString(huart_terminal, "\nResult code: "); PAL_UART_OutNumber_Signed(huart_terminal, result);
        isSuccess = (result == 0);

        if (isSuccess) PAL_UART_OutString(huart_terminal, "\nMessage published successfully. Disconnecting from MQTT broker...");
        else PAL_UART_OutString(huart_terminal, "\nFailed to publish MQTT message. Disconnecting and retrying in 3 seconds...");

        NAL_GTRACK_Disconnect();
        isMQTTOpen = false;
        continue;
    }
}
