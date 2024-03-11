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
	uint8_t errorCount = 0;

    uint32_t timestart = HAL_GetTick();
    while (HAL_GetTick() - timestart < pal_mc60.timeout) {
		if (errorCount >= 10) {
			DEBUG("\nToo many attemps failed. Restarting GTrack...");
			NVIC_SystemReset();
		}
		
        if (!isMQTTOpen) {
            DEBUG("\n*** Opening MQTT connection...");
            result = NAL_GTRACK_OpenNetwork();
            isSuccess = (result == 0 || result == 2);
            DEBUG("\nResult code: %d", result);
            if (!isSuccess) {
				errorCount++;
                if (result == 3) {
                    DEBUG("\nFailed to setup PDP context. Restarting GTrack...");
                    NVIC_SystemReset();
                }
                DEBUG("\nFailed to open MQTT connection. Retrying in 3 seconds...");
                continue;
            }
			errorCount = 0;
            isMQTTOpen = true;
        }

        DEBUG("\n*** Connecting MQTT broker...");
        result = NAL_GTRACK_ConnectBroker();
        DEBUG("\nResult code: %d", result);
        isSuccess = (result == 0 || result == 1);
        if (!isSuccess) {
            DEBUG("\nFailed to connect to MQTT broker. Retrying in 3 seconds...");
            NAL_GTRACK_Disconnect();
			errorCount++;
            isMQTTOpen = false;
            continue;
        }
		errorCount = 0;
		
        DEBUG("\n*** Publishing MQTT message: %s", message);
        result = NAL_GTRACK_PublishMessage(message);
        DEBUG("\nResult code: %d", result);
        isSuccess = (result == 0);

        if (isSuccess) {
			errorCount = 0;
			DEBUG("\nMessage published successfully. Disconnecting from MQTT broker...");
        }
		else {
			errorCount++;
			DEBUG("\nFailed to publish MQTT message. Disconnecting and retrying in 3 seconds...");
		}
		
        NAL_GTRACK_Disconnect();
        isMQTTOpen = false;
        break;
    }
}

char* NAL_GTRACK_ConstructMessage(char* destination, nmea_data* data) {
    char temp[256] = { 0 }; // Define a temporary string
    char* ptr = temp; // Pointer to the temporary string

    char str_temp[15] = { 0 };

    *ptr = '{'; ptr++;

    if (data->Date.is_valid)
        ptr += sprintf(ptr, "date:'%02d/%02d/%04d',", data->Date.day, data->Date.month, 2000 + data->Date.year);

    if (data->Time.is_valid)
        ptr += sprintf(ptr, "time:'%02d:%02d:%02d',", data->Time.hours, data->Time.minutes, data->Time.seconds);
    
    if (data->Location.is_valid) {
        ptr += sprintf(ptr, "lat:%s,", NMEA_Parser_nmeafloattostr(data->Location.latitude, str_temp));
        ptr += sprintf(ptr, "long:%s,", NMEA_Parser_nmeafloattostr(data->Location.longitude, str_temp));
    }

    if (data->Speed.is_valid)
        ptr += sprintf(ptr, "spd:%s,", NMEA_Parser_nmeafloattostr(data->Speed.speed_knot, str_temp));

    if (data->Altitude.is_valid)
        ptr += sprintf(ptr, "alt:%s,", NMEA_Parser_nmeafloattostr(data->Altitude.altitude_meter, str_temp));

    if (data->Course.is_valid)
        ptr += sprintf(ptr, "crs:%s,", NMEA_Parser_nmeafloattostr(data->Course.course_degree, str_temp));

    if (data->HDOP.is_valid)
        ptr += sprintf(ptr, "hdop:%s,", NMEA_Parser_nmeafloattostr(data->HDOP.hdop, str_temp));

    ptr += sprintf(ptr, "bat:%.2f,chg:%.2f,", PAL_SUPPLIER_GetBatteryVoltage(), PAL_SUPPLIER_GetChargerVoltage());

    *(ptr - 1) = '}';

    strcpy(destination, temp); // Copy the temporary string to the destination

    return destination;
}