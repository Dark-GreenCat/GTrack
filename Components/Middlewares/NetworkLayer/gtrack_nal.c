#include "gtrack_nal.h"
#include "w25q/w25q_pal.h"

const char* mqtt_hostname = "demo.thingsboard.io";
const char* mqtt_clientid = "demo.thingsboard.io";
const char* mqtt_username = "3QcnES9LsYKtGIIXxNXU";
const char* mqtt_password = "";
const char* mqtt_topic = "v1/devices/me/telemetry";

static nmea_date last_valid_date = { "", 12, 3, 24 , 1};
static nmea_time last_valid_time = { 0 };

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

bool NAL_GTRACK_Send(const char* message) {
    bool isMQTTOpen = false;
    bool isSuccess = false;
    int8_t result;
	uint8_t errorCount = 0;

    uint32_t timestart = HAL_GetTick();
    while (HAL_GetTick() - timestart < pal_mc60.timeout || errorCount < 10) {
		if (errorCount >= 10) {
			DEBUG("\nToo many attemps failed. Restarting GTrack...");
            PAL_W25Q_Queue_SaveState(&w25q, &flash);
            PAL_MC60_PowerOn(MC60_POWER_OFF);
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
                    PAL_W25Q_Queue_SaveState(&w25q, &flash);
                    NVIC_SystemReset();
                }
                DEBUG("\nFailed to open MQTT connection. Retrying in 3 seconds...");
                continue;
            }
			// errorCount = 0;
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
		// errorCount = 0;
		
        DEBUG("\n*** Publishing MQTT message: %s", message);
        result = NAL_GTRACK_PublishMessage(message);
        DEBUG("\nResult code: %d", result);
        isSuccess = (result == 0);

        if (isSuccess) {
			// errorCount = 0;
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

    return isSuccess;
}

char* NAL_GTRACK_ConstructMessage(char* destination, nmea_data* data) {
    char* ptr = destination; // Pointer to the temporary string

    char str_temp[15] = { 0 };

    *ptr = '{'; ptr++;

    // if (data->Date.is_valid)
    //     ptr += sprintf(ptr, "date:'%02d/%02d/%04d',", data->Date.day, data->Date.month, 2000 + data->Date.year);

    // if (data->Time.is_valid)
    //     ptr += sprintf(ptr, "time:'%02d:%02d:%02d',", data->Time.hours, data->Time.minutes, data->Time.seconds);

    if (data->Time.is_valid && data->Date.is_valid) {
        if (data->Date.year != 80) {
            last_valid_date = data->Date;
            last_valid_time = data->Time;
        }
        else {
            data->Time = last_valid_time;
            data->Date = last_valid_date;
            data->Time.seconds += 10;
        }
    }
        ptr += sprintf(ptr, "ts:%s,values:{", NMEA_Parser_nmeadata_to_timestamp(data, str_temp));
    
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

    bma253_accel_data_t bma253_accel_data;
    PAL_BMA253_Get_Accel_XYZ(&bma253_accel_data);
    ptr += sprintf(ptr, "ax:%d,ay:%d,az:%d,", bma253_accel_data.x, bma253_accel_data.y, bma253_accel_data.z);
    
    ptr += sprintf(ptr, "bat:%.2f,chg:%.2f,", PAL_SUPPLIER_GetBatteryVoltage(), PAL_SUPPLIER_GetChargerVoltage());

    *(ptr - 1) = '}';
    *ptr = '}';
    *(ptr + 1) = '\0';

    return destination;
}

char* NAL_GTRACK_ConstructMessageShort(char* destination, nmea_data* data) {
    char* ptr = destination; // Pointer to the temporary string

    char str_temp[15] = { 0 };

    *ptr = '{'; ptr++;
    
    if (data->Time.is_valid && data->Date.is_valid) {
        DEBUG("\nYEAR: %d\n", data->Date.year);
        if (data->Date.year != 80) {
            last_valid_date = data->Date;
            last_valid_time = data->Time;
        }
        else {
            data->Time = last_valid_time;
            data->Date = last_valid_date;
            data->Time.seconds += 10;
        }
        
        ptr += sprintf(ptr, "ts:%s,values:{", NMEA_Parser_nmeadata_to_timestamp(data, str_temp));
    }
    
    if (data->Location.is_valid) {
        ptr += sprintf(ptr, "l:%s,", NMEA_Parser_nmeafloattostr(data->Location.latitude, str_temp));
        ptr += sprintf(ptr, "L:%s,", NMEA_Parser_nmeafloattostr(data->Location.longitude, str_temp));
    }

    ptr += sprintf(ptr, "B:%.2f,", PAL_SUPPLIER_GetBatteryVoltage());

    *(ptr - 1) = '}';
    *(ptr + 0) = '}';
    *(ptr + 1) = '\0';

    return destination;
}
