#include "mc60_pal.h"

#include "gpio/gpio_hcl.h"

MC60_TypeDef pal_mc60;

void PAL_MC60_Init() {
    pal_mc60.timeout = PAL_MC60_TIMEOUT;

    MC60_ITF_Init(&pal_mc60.core, huart_mc60, &hgpio_mc60_pwrkey, &hgpio_mc60_gnss_en, &hgpio_mc60_vdd_ext);
    HCL_GPIO_WritePin(&hgpio_mc60_gsm_en, GPIO_PIN_RESET);
}

void PAL_MC60_MQTT_Init(mc60_mqtt_t* mc60_mqtt) {
    pal_mc60.mqtt.tcpid = mc60_mqtt->tcpid;
    pal_mc60.mqtt.port = mc60_mqtt->port;
    pal_mc60.mqtt.hostname = mc60_mqtt->hostname;
    pal_mc60.mqtt.clientid = mc60_mqtt->clientid;
    pal_mc60.mqtt.username = mc60_mqtt->username;
    pal_mc60.mqtt.password = mc60_mqtt->password;
}

bool PAL_MC60_IsRunning() {
    return MC60_ITF_IsRunning(&pal_mc60.core);
}

void PAL_MC60_PowerOn(mc60_state state) {
    if(state == MC60_POWER_OFF) MC60_ITF_PowerOff(&pal_mc60.core);
    else MC60_ITF_PowerOn(&pal_mc60.core);
}

void PAL_MC60_GNSS_PowerOn(mc60_gnss_state state) {
    if(state == MC60_GNSS_POWER_OFF) MC60_ITF_GNSS_PowerOff(&pal_mc60.core);
    else MC60_ITF_GNSS_PowerOn(&pal_mc60.core);
}

void PAL_MC60_RunCommand(const char* cmd) {
    MC60_ITF_SendCmd(&pal_mc60.core, cmd);
}

void PAL_MC60_MQTT_Send(const char* topic, const char* message) {
    bool isMQTTOpen = false;
    bool isSuccess = false;
    int8_t result;

    uint32_t timestart = HAL_GetTick();
    while (HAL_GetTick() - timestart < pal_mc60.timeout) {
        if (!isMQTTOpen) {
            PAL_UART_OutString(huart_terminal, "\n*** Opening MQTT connection...");
            result = PAL_MC60_MQTT_Open(&pal_mc60);
            isSuccess = (result == 0 || result == 2);
            PAL_UART_OutString(huart_terminal, "\nResult code: "); PAL_UART_OutNumber_Signed(huart_terminal, result);
            if (!isSuccess) {
                if (result == 3) NVIC_SystemReset();
                PAL_UART_OutString(huart_terminal, "\nFailed to open MQTT connection. Retrying in 3 seconds...");
                continue;
            }

            isMQTTOpen = true;
        }

        PAL_UART_OutString(huart_terminal, "\n*** Connecting MQTT broker...");
        result = PAL_MC60_MQTT_Connect(&pal_mc60);
        PAL_UART_OutString(huart_terminal, "\nResult code: "); PAL_UART_OutNumber_Signed(huart_terminal, result);
        isSuccess = (result == 0 || result == 1);
        if (!isSuccess) {
            PAL_UART_OutString(huart_terminal, "\nFailed to connect to MQTT broker. Retrying in 3 seconds...");
            PAL_MC60_MQTT_Disconnect(&pal_mc60);
            isMQTTOpen = false;
            continue;
        }

        PAL_UART_OutString(huart_terminal, "\n*** Publishing MQTT message: ");
        PAL_UART_OutString(huart_terminal, message);
        result = PAL_MC60_MQTT_Publish(&pal_mc60, 0, 0, 0, topic, message);
        PAL_UART_OutString(huart_terminal, "\nResult code: "); PAL_UART_OutNumber_Signed(huart_terminal, result);
        isSuccess = (result == 0);
        if (isSuccess) {
            PAL_UART_OutString(huart_terminal, "\nMessage published successfully. Disconnecting from MQTT broker...");
            PAL_MC60_MQTT_Disconnect(&pal_mc60);
            isMQTTOpen = false;
            return;
        }
        else {
            PAL_UART_OutString(huart_terminal, "\nFailed to publish MQTT message. Disconnecting and retrying in 3 seconds...");
            PAL_MC60_MQTT_Disconnect(&pal_mc60);
            isMQTTOpen = false;
            continue;
        }
    }
}
