#include "gtrack_ual.h"
#include "w25q/w25q_pal.h"

bool UAL_MC60_isTurningOn = false;
bool UAL_MC60_isGettingGNSS = false;
bool UAL_MC60_isSendingToMQTT = false;

void UAL_GTRACK_Init() {
    PAL_MC60_Init();
    NAL_GTrack_Init();
}

void UAL_GTRACK_GeoTrack_Enable() {
    UAL_MC60_isTurningOn = true;
    HCL_TIMER_Start(htim_led);

    bool mc60_state = false;
    mc60_state = PAL_MC60_IsRunning();
    DEBUG("\nCheck MC60 Status: %d", mc60_state);

    DEBUG("\n-------- Power on MC60 --------\n");
    PAL_MC60_PowerOn(MC60_POWER_ON);
    DEBUG("\n------ Check MC60 status ------");
    DEBUG("\n\t>> Running command: AT\n");
    PAL_MC60_RunCommand("AT");
    HAL_Delay(5000);
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
    mc60_state = PAL_MC60_IsRunning();
    DEBUG("\nCheck MC60 Status: %d", mc60_state);
    if (!mc60_state) return;


    PAL_MC60_RunCommand("AT+QIFGCNT=2");
    PAL_MC60_RunCommand("AT+QICSGP=1,\"m-wap\",\"mms\",\"mms\"");
    //PAL_MC60_RunCommand("AT+QICSGP=1,\"v-internet\"");
    HAL_Delay(10000);
    PAL_MC60_RunCommand("AT+CREG?;+CGREG?");
    PAL_MC60_RunCommand("AT+QGNSSTS?");
    PAL_MC60_RunCommand("AT+QGREFLOC=21.04196,105.786865");
    PAL_MC60_RunCommand("AT+QGNSSEPO=1");
    PAL_MC60_RunCommand("AT+QSCLK=0");
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);

    HCL_TIMER_Stop(htim_led);
    UAL_MC60_isTurningOn = false;
}

void UAL_GTRACK_GeoTrack_Activate(feature_geotrack_state state) {
    if (state == GEOTRACK_DEACTIVATE) {
        DEBUG("\n-------- Power off GNSS --------\n");
        PAL_MC60_GNSS_PowerOn(MC60_GNSS_POWER_OFF);
    }
    else {
        DEBUG("\n-------- Power on GNSS --------\n");
        PAL_MC60_GNSS_PowerOn(MC60_GNSS_POWER_ON);
        HAL_Delay(2000);
    }
}

void UAL_GTRACK_GeoTrack_GetMetric() {
    bool gnss_power_state = false;

    char buffer[256];
    nmea_data GPSData;
    NMEA_Parser_Reset(&GPSData);

    UAL_GTRACK_GeoTrack_Activate(GEOTRACK_ACTIVATE);
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
    gnss_power_state = MC60_ITF_GNSS_checkPower(&pal_mc60.core);
    DEBUG("\nGNSS Power Status: %d", gnss_power_state);

    if (!gnss_power_state) {
        DEBUG("\nGNSS is currently off!");
        return;
    }

    DEBUG("\nConnecting GNSS...\n");
    UAL_MC60_isGettingGNSS = true;
    HCL_TIMER_Start(htim_led);
    bool isGetGNSSSuccess = MC60_GNSS_Get_Navigation_Info(&pal_mc60.core, &GPSData, 3000);
    HCL_TIMER_Stop(htim_led);
    UAL_MC60_isGettingGNSS = false;

    if (isGetGNSSSuccess) {
        UAL_GTRACK_GeoTrack_Activate(GEOTRACK_DEACTIVATE);
        HAL_Delay(200);
        PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
        NMEA_Parser_changeTimezone(&GPSData, 7);
        char temp[30];
        sprintf(buffer, "\n----- CAPTURING GNSS DATA -----\n");
        sprintf(buffer + strlen(buffer), "Time: %02d:%02d:%02d\n", GPSData.Time.hours, GPSData.Time.minutes, GPSData.Time.seconds);
        sprintf(buffer + strlen(buffer), "Date: %02d/%02d/%04d\n", GPSData.Date.day, GPSData.Date.month, 2000 + GPSData.Date.year);
        sprintf(buffer + strlen(buffer), "Timestamp: %s\n", NMEA_Parser_nmeadata_to_timestamp(&GPSData, temp));
        sprintf(buffer + strlen(buffer), "Latitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.latitude, temp));
        sprintf(buffer + strlen(buffer), "Longitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.longitude, temp));
        sprintf(buffer + strlen(buffer), "Speed: %s knots\n", NMEA_Parser_nmeafloattostr(GPSData.Speed.speed_knot, temp));
        sprintf(buffer + strlen(buffer), "Course: %s degrees\n", NMEA_Parser_nmeafloattostr(GPSData.Course.course_degree, temp));
        sprintf(buffer + strlen(buffer), "HDOP: %s\n", NMEA_Parser_nmeafloattostr(GPSData.HDOP.hdop, temp));
        sprintf(buffer + strlen(buffer), "Altitude: %s m\n", NMEA_Parser_nmeafloattostr(GPSData.Altitude.altitude_meter, temp));
        sprintf(buffer + strlen(buffer), "\n");

        DEBUG(buffer);
        NMEA_Parser_changeTimezone(&GPSData, -7);
        NAL_GTRACK_ConstructMessageShort(buffer, &GPSData);
        PAL_W25Q_Queue_Enqueue(&flash, buffer, strlen(buffer) + 1);
    }
}

bool UAL_GTRACK_GeoTrack_UploadData() {
    bool isSuccess = false;
    uint16_t BackUpDataIndex = flash.PageIndexGet;
    uint16_t BackUpDataCount = flash.Count;

    char buffer[BUFFER_SIZE] = { 0 };

    char* ptr = buffer;
    char str_temp[MAX_MESSAGE_SIZE] = {0};
    bool IsDataExist = false;

    *ptr++ = '[';
    while (!PAL_W25Q_Queue_IsEmpty(&flash)) {
        IsDataExist = true;

        PAL_W25Q_Queue_Dequeue(&flash, str_temp, MAX_MESSAGE_SIZE);
        // Check if there is enough space in the buffer for the next string
        if ((ptr - buffer) + strlen(str_temp) + 1 >= BUFFER_SIZE) {
            // Buffer is full, stop copying data
            break;
        }
        ptr += sprintf(ptr, "%s,", str_temp);
    }
    if (IsDataExist) {
        *(ptr - 1) = ']';
        UAL_MC60_isSendingToMQTT = true;
        HCL_TIMER_Start(htim_led);
        isSuccess = NAL_GTRACK_Send(buffer);
        HCL_TIMER_Stop(htim_led);
        UAL_MC60_isSendingToMQTT = false;
    }

    if (!isSuccess) {
        flash.PageIndexGet = BackUpDataIndex;
        flash.Count = BackUpDataCount;
    }

    return isSuccess;
}
