#include "gtrack_ual.h"

void UAL_GTRACK_Init() {
    PAL_MC60_Init();
    NAL_GTrack_Init();
}

void UAL_GTRACK_GeoTrack_Enable() {
    bool mc60_state = false;
    PAL_UART_OutString(huart_terminal, "\nCheck MC60 Status: ");
    mc60_state = PAL_MC60_IsRunning();
    PAL_UART_OutNumber(huart_terminal, mc60_state);

    PAL_UART_OutString(huart_terminal, "\n-------- Power on MC60 --------\n");
    PAL_MC60_PowerOn(MC60_POWER_ON);
    PAL_UART_OutString(huart_terminal, "\n------ Check MC60 status ------");
    PAL_UART_OutString(huart_terminal, "\n\t>> Running command: AT\n");
    PAL_MC60_RunCommand("AT");
    HAL_Delay(5000);
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
    PAL_UART_OutString(huart_terminal, "\nCheck MC60 Status: ");
    mc60_state = PAL_MC60_IsRunning();
    PAL_UART_OutNumber(huart_terminal, mc60_state);
    if (!mc60_state) return;

    PAL_MC60_RunCommand("AT+QIFGCNT=2");
    PAL_MC60_RunCommand("AT+QICSGP=1,\"m-wap\",\"mms\",\"mms\"");
	//PAL_MC60_RunCommand("AT+QICSGP=1,\"v-internet\"");
    HAL_Delay(10000);
    PAL_MC60_RunCommand("AT+CREG?;+CGREG?");
    PAL_MC60_RunCommand("AT+QGNSSTS?");
    PAL_MC60_RunCommand("AT+QGREFLOC=21.04196,105.786865");
    PAL_MC60_RunCommand("AT+QGNSSEPO=1");
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
}

void UAL_GTRACK_GeoTrack_Activate(feature_geotrack_state state) {
    PAL_UART_OutString(huart_terminal, "\n-------- Power on GNSS --------\n");
    MC60_ITF_GNSS_PowerOn(&pal_mc60.core);
}

void UAL_GTRACK_GeoTrack_GetMetric() {
    char buffer[256];
    nmea_data GPSData;

    UAL_GTRACK_GeoTrack_Activate(GEOTRACK_ACTIVATE);
    HAL_Delay(2000);
    PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
    PAL_UART_OutString(huart_terminal, "\nConnecting GNSS...\n");
    if (MC60_GNSS_Get_Navigation_Info(&pal_mc60.core, &GPSData, 3000)) {
        MC60_ITF_SendCmd(&pal_mc60.core, "AT+QGNSSC=0");
        HAL_Delay(200);
        PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
        NMEA_Parser_changeTimezone(&GPSData, 7);
        char temp[30];
        sprintf(buffer, "\n----- CAPTURING GNSS DATA -----\n");
        sprintf(buffer + strlen(buffer), "Time: %02d:%02d:%02d\n", GPSData.Time.hours, GPSData.Time.minutes, GPSData.Time.seconds);
        sprintf(buffer + strlen(buffer), "Date: %02d/%02d/%04d\n", GPSData.Date.day, GPSData.Date.month, 2000 + GPSData.Date.year);
        sprintf(buffer + strlen(buffer), "Latitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.latitude, temp));
        sprintf(buffer + strlen(buffer), "Longitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.longitude, temp));
        sprintf(buffer + strlen(buffer), "Speed: %s knots\n", NMEA_Parser_nmeafloattostr(GPSData.Speed.speed_knot, temp));
        sprintf(buffer + strlen(buffer), "Course: %s degrees\n", NMEA_Parser_nmeafloattostr(GPSData.Course.course_degree, temp));
        sprintf(buffer + strlen(buffer), "HDOP: %s\n", NMEA_Parser_nmeafloattostr(GPSData.HDOP.hdop, temp));
        sprintf(buffer + strlen(buffer), "Altitude: %s m\n", NMEA_Parser_nmeafloattostr(GPSData.Altitude.altitude_meter, temp));
        sprintf(buffer + strlen(buffer), "\n");

        PAL_UART_OutString(huart_terminal, buffer);
        sprintf(buffer, "{lat:%s,long:%s}", NMEA_Parser_nmeafloattostr(GPSData.Location.latitude, temp),
            NMEA_Parser_nmeafloattostr(GPSData.Location.longitude, temp));

        NAL_GTRACK_Send(buffer);
    }

}
