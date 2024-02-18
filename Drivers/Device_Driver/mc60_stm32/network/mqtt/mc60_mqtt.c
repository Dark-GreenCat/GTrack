#include "mc60_mqtt.h"
#include <string.h>

int8_t MC60_MQTT_Open(mc60_t* mc60, uint8_t tcp_connect_id, const char* host_name, uint16_t port, uint32_t timeout) {
    int8_t ret = MC60_MQTT_OPEN_FAILED_TO_OPEN_NETWORK;
    
    char temp[109];
    sprintf(temp, "%d,\"%s\",%d", tcp_connect_id, host_name, port);
    MC60_ITF_SendCmdWithParam(mc60, "AT+QMTOPEN", temp);
    MC60_ITF_WaitForResponse(mc60, "\r\n", 2, timeout);

    mc60_result_process_t process;
    MC60_ITF_UTIL_ResultProcess_Init(temp, &process);
    uint32_t last = MC60_MCU_Uptime();
    while (last + timeout > MC60_MCU_Uptime()) {
        char c = MC60_ITF_ReceiveChar(mc60, timeout);
        if (c == 0) continue;

        last = MC60_MCU_Uptime();
        if (!MC60_ITF_UTIL_GetResult(&process, c)) continue;

        switch (process.termCount) {
            case 1:
                if (strcmp(temp, "+QMTOPEN") != 0) {
                    MC60_ITF_UTIL_ResultProcess_Init(temp, &process);
                    continue;
                }
                break;

            case 3:
                ret = (int8_t) MC60_ITF_UTIL_ResultToNum(temp);

            default:
                break;
        }
    }

    return ret;
}

int8_t MC60_MQTT_Connect(mc60_t* mc60, mc60_mqtt_tcp_id tcp_connect_id, const char* client_id, const char* user_name, const char* password, uint32_t timeout) {
    int8_t ret = -1;
    
    char temp[MC60_AT_COMMAND_MAX_SIZE];
    sprintf(temp, "%d,\"%s\",\"%s\",\"%s\"", tcp_connect_id, client_id, user_name, password);
    MC60_ITF_SendCmdWithParam(mc60, "AT+QMTCONN", temp);
    MC60_ITF_WaitForResponse(mc60, "\r\n", 2, timeout);

    mc60_result_process_t process;
    MC60_ITF_UTIL_ResultProcess_Init(temp, &process);
    uint32_t last = MC60_MCU_Uptime();
    while (last + timeout > MC60_MCU_Uptime()) {
        char c = MC60_ITF_ReceiveChar(mc60, timeout);
        if (c == 0) continue;

        last = MC60_MCU_Uptime();
        if (!MC60_ITF_UTIL_GetResult(&process, c)) continue;

        switch (process.termCount) {
            case 1:
                if (strcmp(temp, "+QMTCONN") != 0) {
                    MC60_ITF_UTIL_ResultProcess_Init(temp, &process);
                    continue;
                }
                break;

            case 2:
                ret = (int8_t) MC60_ITF_UTIL_ResultToNum(temp);

            default:
                break;
        }
    }

    return ret;
}

int8_t MC60_MQTT_Disconnect(mc60_t* mc60, mc60_mqtt_tcp_id tcp_connect_id, uint32_t timeout) {
    int8_t ret = -1;
    
    char temp[2];
    sprintf(temp, "%d", tcp_connect_id);
    MC60_ITF_SendCmdWithParam(mc60, "AT+QMTDISC", temp);
    MC60_ITF_WaitForResponse(mc60, "\r\n", 2, timeout);

    mc60_result_process_t process;
    MC60_ITF_UTIL_ResultProcess_Init(temp, &process);
    uint32_t last = MC60_MCU_Uptime();
    while (last + timeout > MC60_MCU_Uptime()) {
        char c = MC60_ITF_ReceiveChar(mc60, timeout);
        if (c == 0) continue;

        last = MC60_MCU_Uptime();
        if (!MC60_ITF_UTIL_GetResult(&process, c)) continue;

        switch (process.termCount) {
            case 1:
                if (strcmp(temp, "+QMTDISC") != 0) {
                    MC60_ITF_UTIL_ResultProcess_Init(temp, &process);
                    continue;
                }
                break;

            case 3:
                ret = (int8_t) MC60_ITF_UTIL_ResultToNum(temp);

            default:
                break;
        }
    }

    return ret;
}
