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
    pal_mc60.mqtt.hostname = (char*) mqtt_hostname;
    pal_mc60.mqtt.clientid = (char*) mqtt_clientid;
    pal_mc60.mqtt.username = (char*) mqtt_username;
    pal_mc60.mqtt.password = (char*) mqtt_password;
}

void PAL_MC60_MQTT_Send(const char* topic, const char* message) {
    bool isMQTTOpen = false;
    bool isSuccess = false;
    int8_t result;
    while (1) {
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

        PAL_UART_OutString(huart_terminal, "\n*** Publishing MQTT message...");
        result = PAL_MC60_MQTT_Publish(&pal_mc60, topic, message);
        PAL_UART_OutString(huart_terminal, "\nResult code: "); PAL_UART_OutNumber_Signed(huart_terminal, result);
        isSuccess = (result == 0);
        if (isSuccess) {
            PAL_UART_OutString(huart_terminal, "\nMessage published successfully. Disconnecting from MQTT broker...");
            PAL_MC60_MQTT_Disconnect(&pal_mc60);
            isMQTTOpen = false;
            continue;
        }
        else {
            PAL_UART_OutString(huart_terminal, "\nFailed to publish MQTT message. Disconnecting and retrying in 3 seconds...");
            PAL_MC60_MQTT_Disconnect(&pal_mc60);
            isMQTTOpen = false;
            continue;
        }
    }
}
