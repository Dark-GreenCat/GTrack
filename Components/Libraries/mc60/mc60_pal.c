#include "mc60_pal.h"

#include "gpio/gpio_hcl.h"

const char* mqtt_hostname = "demo.thingsboard.io";
const char* mqtt_clientid = "demo.thingsboard.io";
const char* mqtt_username = "3QcnES9LsYKtGIIXxNXU";
const char* mqtt_password = "";
const char* mqtt_topic = "v1/devices/me/telemetry";

MC60_TypeDef pal_mc60;

void PAL_MC60_Init() {
    pal_mc60.timeout = PAL_MC60_TIMEOUT;

    MC60_ITF_Init(&pal_mc60.core, huart_mc60, &hgpio_mc60_pwrkey, &hgpio_mc60_gnss_en, &hgpio_mc60_vdd_ext);
    HCL_GPIO_WritePin(&hgpio_mc60_gsm_en, GPIO_PIN_RESET);

    PAL_MC60_MQTT_Init();
}

void PAL_MC60_MQTT_Init() {
    pal_mc60.mqtt.tcpid = PAL_MC60_MQTT_TCP_ID;
    pal_mc60.mqtt.port = PAL_MC60_MQTT_PORT;
    pal_mc60.mqtt.hostname = (char*)mqtt_hostname;
    pal_mc60.mqtt.clientid = (char*)mqtt_clientid;
    pal_mc60.mqtt.username = (char*)mqtt_username;
    pal_mc60.mqtt.password = (char*)mqtt_password;
}

void PAL_MC60_PowerOn() {
    bool mc60_state = false;
    PAL_UART_OutString(huart_terminal, "\nCheck MC60 Status: ");
    mc60_state = MC60_ITF_IsRunning(&pal_mc60.core);
    PAL_UART_OutNumber(huart_terminal, mc60_state);

    PAL_UART_OutString(huart_terminal, "\n-------- Power on MC60 --------\n");
    MC60_ITF_PowerOn(&pal_mc60.core);
    PAL_UART_OutString(huart_terminal, "\n------ Check MC60 status ------");
    PAL_UART_OutString(huart_terminal, "\n\t>> Running command: AT\n");
    MC60_ITF_SendCmd(&pal_mc60.core, "AT");
    HAL_Delay(6000);
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
    PAL_UART_OutString(huart_terminal, "\nCheck MC60 Status: ");
    mc60_state = MC60_ITF_IsRunning(&pal_mc60.core);
    PAL_UART_OutNumber(huart_terminal, mc60_state);
    if(!mc60_state) return;

    MC60_ITF_SendCmd(&pal_mc60.core, "AT+QIFGCNT=2");
    MC60_ITF_SendCmd(&pal_mc60.core, "AT+QICSGP=1,\"m-wap\",\"mms\",\"mms\"");
    HAL_Delay(7000);
    MC60_ITF_SendCmd(&pal_mc60.core, "AT+CREG?;+CGREG?");
    MC60_ITF_SendCmd(&pal_mc60.core, "AT+QGNSSTS?");
    MC60_ITF_SendCmd(&pal_mc60.core, "AT+QGREFLOC=21.04196,105.786865");
    MC60_ITF_SendCmd(&pal_mc60.core, "AT+QGNSSEPO=1");
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
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
        result = PAL_MC60_MQTT_Publish(&pal_mc60, topic, message);
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
