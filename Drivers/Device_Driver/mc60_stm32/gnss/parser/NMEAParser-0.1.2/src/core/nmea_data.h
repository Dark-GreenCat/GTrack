#ifndef __NMEA_DATA_H
#define __NMEA_DATA_H

#include <stdbool.h>
#include <stdint.h>

#define NMEA_MAX_FIELD_SIZE             15

#define NMEA_TIME_FIELD_SIZE            11
#define NMEA_DATE_FIELD_SIZE            7
#define NMEA_LOCATION_FIELD_SIZE        13
#define NMEA_SPEED_FIELD_SIZE           NMEA_MAX_FIELD_SIZE
#define NMEA_COURSE_FIELD_SIZE          NMEA_MAX_FIELD_SIZE
#define NMEA_HDOP_FIELD_SIZE            NMEA_MAX_FIELD_SIZE
#define NMEA_ALTITUDE_FIELD_SIZE        NMEA_MAX_FIELD_SIZE

typedef enum {
    NMEA_SENTENCE_RMC,
    NMEA_SENTENCE_GGA,
    NMEA_SENTENCE_OTHER
} nmea_sentence_type;

// Represents a floating-point value with decimal places
typedef struct {
    int32_t value;
    uint8_t decimal_places;
} nmea_float;

// Represents time information
typedef struct {
    char time_raw[NMEA_TIME_FIELD_SIZE]; // Raw time string
    uint8_t hours; // Hours (0-23)
    uint8_t minutes; // Minutes (0-59)
    uint8_t seconds; // Seconds (0-59)
    uint16_t milliseconds; // Milliseconds (0-999)
} nmea_time;

// Represents date information
typedef struct {
    char date_raw[NMEA_DATE_FIELD_SIZE]; // Raw date string
    uint8_t day; // Day (1-31)
    uint8_t month; // Month (1-12)
    uint8_t year; // Year (0-99)
} nmea_date;

// Represents location information in raw format
typedef struct {
    char location[NMEA_LOCATION_FIELD_SIZE]; // Raw location string
    char cardinal; // Cardinal direction (N, S, E, W)
} nmea_location_raw;

// Represents location information (latitude and longitude)
typedef struct {
    nmea_location_raw latitude_raw; // Raw latitude string
    nmea_location_raw longitude_raw; // Raw longitude string

    nmea_float latitude; // Latitude value (with decimal places)
    nmea_float longitude; // Longitude value (with decimal places)
} nmea_location;

// Represents speed information
typedef struct {
    char speed_raw[NMEA_SPEED_FIELD_SIZE]; // Raw speed string

    nmea_float speed_knot; // Speed value in knots (with decimal places)
} nmea_speed;

// Represents course information
typedef struct {
    char course_raw[NMEA_COURSE_FIELD_SIZE]; // Raw course string

    nmea_float course_degree; // Course value in degrees (with decimal places)
} nmea_course;

// Represents HDOP (Horizontal Dilution of Precision) information
typedef struct {
    char hdop_raw[NMEA_HDOP_FIELD_SIZE]; // Raw HDOP string

    nmea_float hdop; // HDOP value (with decimal places)
} nmea_hdop;

// Represents altitude information
typedef struct {
    char altitude_raw[NMEA_ALTITUDE_FIELD_SIZE]; // Raw altitude string

    nmea_float altitude_meter; // Altitude value in meters (with decimal places)
} nmea_altitude;

// Represents complete NMEA data
typedef struct {
    nmea_time Time; // Time information
    nmea_date Date; // Date information
    nmea_location Location; // Location information
    nmea_speed Speed; // Speed information
    nmea_course Course; // Course information
    nmea_hdop HDOP; // HDOP information
    nmea_altitude Altitude; // Altitude information
} nmea_data;

// Set the raw time data in the nmea_time structure
void setRawTime(nmea_time* time, char* term);
// Set the raw date data in the nmea_date structure
void setRawDate(nmea_date* date, char* term);
// Set the raw location data in the nmea_location_raw structure
void setRawLocation(nmea_location_raw* location_raw, char* term);
// Set the cardinal direction in the nmea_location_raw structure
void setRawLocationCardinal(nmea_location_raw* location_raw, char* term);
// Set the raw speed data in the nmea_speed structure
void setRawSpeed(nmea_speed* speed, char* term);
// Set the raw course data in the nmea_course structure
void setRawCourse(nmea_course* course, char* term);
// Set the raw HDOP (Horizontal Dilution of Precision) data in the nmea_hdop structure
void setRawHDOP(nmea_hdop* hdop, char* term);
// Set the raw altitude data in the nmea_altitude structure
void setRawAltitude(nmea_altitude* altitude, char* term);

#endif /* __NMEA_DATA_H */