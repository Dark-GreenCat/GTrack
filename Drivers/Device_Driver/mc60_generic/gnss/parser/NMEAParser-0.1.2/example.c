#include <stdio.h>
#include <stdlib.h>
#include "nmea_parser.h"

void test_parser() {
    // char sentence[] = "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A";
    char* sentence_rmc = "+QGNSSRD: $GNRMC,100234.000,A,2102.5194,N,10547.2117,E,0.66,166.83,061223,,,A*70\r\n";
    char* sentence_gga = "AT+GNSSRD?: $GNGGA,100236.000,2102.5239,N,10547.2110,E,1,5,2.98,50.0,M,-20.9,M,,*58\r\n";

    nmea_data GPSData = { 0 };
    char temp[15];
    for (int i = 0; sentence_rmc[i] != '\0'; i++) {
        if (NMEA_Parser_Process(&GPSData, sentence_rmc[i])) {
            // GMT+7
            NMEA_Parser_changeTimezone(&GPSData, 7);
            printf("\n----- CAPTURING RMC DATA -----\n");
            printf("Time: %02d:%02d:%02d\n", GPSData.Time.hours, GPSData.Time.minutes, GPSData.Time.seconds);
            printf("Date: %02d/%02d/%04d\n", GPSData.Date.day, GPSData.Date.month, 2000 + GPSData.Date.year);
            printf("Latitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.latitude, temp));
            printf("Longitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.longitude, temp));
            printf("Speed: %s knots\n", NMEA_Parser_nmeafloattostr(GPSData.Speed.speed_knot, temp));
            printf("Course: %s degrees\n", NMEA_Parser_nmeafloattostr(GPSData.Course.course_degree, temp));
            printf("HDOP: %s\n", NMEA_Parser_nmeafloattostr(GPSData.HDOP.hdop, temp));
            printf("Altitude: %sm\n", NMEA_Parser_nmeafloattostr(GPSData.Altitude.altitude_meter, temp));
            printf("\n");
        }
    }

    for (int i = 0; sentence_gga[i] != '\0'; i++) {
        if (NMEA_Parser_Process(&GPSData, sentence_gga[i])) {
            // GMT+7
            NMEA_Parser_changeTimezone(&GPSData, 7);
            printf("\n----- CAPTURING GGA DATA -----\n");
            printf("Time: %02d:%02d:%02d\n", GPSData.Time.hours, GPSData.Time.minutes, GPSData.Time.seconds);
            printf("Date: %02d/%02d/%04d\n", GPSData.Date.day, GPSData.Date.month, 2000 + GPSData.Date.year);
            printf("Latitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.latitude, temp));
            printf("Longitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.longitude, temp));
            printf("Speed: %s knots\n", NMEA_Parser_nmeafloattostr(GPSData.Speed.speed_knot, temp));
            printf("Course: %s degrees\n", NMEA_Parser_nmeafloattostr(GPSData.Course.course_degree, temp));
            printf("HDOP: %s\n", NMEA_Parser_nmeafloattostr(GPSData.HDOP.hdop, temp));
            printf("Altitude: %sm\n", NMEA_Parser_nmeafloattostr(GPSData.Altitude.altitude_meter, temp));
            printf("\n");
        }
    }
}

void test_converter() {
    // Test NMEA_Parser_strtoi32
    const char* str1 = "12345";
    int32_t result1 = NMEA_Parser_strtoi32(str1);
    printf("NMEA_Parser_strtoi32: %d\n", result1);  // Expected output: 12345

    // Test NMEA_Parser_strntoi32
    const char* str2 = "Hello 6789";
    uint32_t start_index = 6;
    uint32_t size = 4;
    int32_t result2 = NMEA_Parser_strntoi32(str2, start_index, size);
    printf("NMEA_Parser_strntoi32: %d\n", result2);  // Expected output: 6789

    // Test NMEA_Parser_strtou32
    const char* str3 = "98765";
    uint32_t result3 = NMEA_Parser_strtou32(str3);
    printf("NMEA_Parser_strtou32: %u\n", result3);  // Expected output: 98765

    // Test NMEA_Parser_strntou32
    const char* str4 = "Test 456";
    uint32_t result4 = NMEA_Parser_strntou32(str4, 5, 3);
    printf("NMEA_Parser_strntou32: %u\n", result4);  // Expected output: 456

    // Test NMEA_Parser_numtostr
    int number1 = 12345;
    int decimal_places = 2;
    char result5[20];
    char* str5 = NMEA_Parser_numtostr(number1, decimal_places, result5);
    printf("NMEA_Parser_numtostr: %s\n", str5);  // Expected output: "123.45"

    // Test NMEA_Parser_nmeafloattostr
    nmea_float number2 = {12345, 2};
    char result6[20];
    char* str6 = NMEA_Parser_nmeafloattostr(number2, result6);
    printf("NMEA_Parser_nmeafloattostr: %s\n", str6);  // Expected output: "123.45"

    // Test NMEA_Parser_nmeafloattod
    double result7 = NMEA_Parser_nmeafloattod(number2);
    printf("NMEA_Parser_nmeafloattod: %lf\n", result7);  // Expected output: 123.45
}

int main() {
    test_converter();
    test_parser();
    return 0;
}