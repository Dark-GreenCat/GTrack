#include <math.h>
#include "nmea_decoder.h"
#include "nmea_converter.h"

void decodeTime(nmea_time* time) {
    const char* raw = time->time_raw;

    time->hours = (uint8_t) NMEA_Parser_strntou32(raw, 0, 2);
    time->minutes = (uint8_t) NMEA_Parser_strntou32(raw, 2, 2);
    time->seconds = (uint8_t) NMEA_Parser_strntou32(raw, 4, 2);
    time->milliseconds = (uint16_t) NMEA_Parser_strntou32(raw, 7, 3);
}

void decodeDate(nmea_date* date) {
    const char* raw = date->date_raw;

    date->day = (uint8_t) NMEA_Parser_strntou32(raw, 0, 2);
    date->month = (uint8_t) NMEA_Parser_strntou32(raw, 2, 2);
    date->year = (uint8_t) NMEA_Parser_strntou32(raw, 4, 2);
}

void decodeLocation(nmea_location* location) {
    // Decode latitude
    const char* raw = location->latitude_raw.location;
    int32_t integer = NMEA_Parser_strntoi32(raw, 0, 2);
    int32_t fraction = round(NMEA_Parser_strntoi32(raw, 2, 7) * 5 / 3.0f); 
    location->latitude.value = integer * 1000000 + fraction;
    location->latitude.decimal_places = 6;

    // Decode longitude
    raw = location->longitude_raw.location;
    integer = NMEA_Parser_strntoi32(raw, 0, 3);
    fraction = round(NMEA_Parser_strntoi32(raw, 3, 7) * 5 / 3.0f); 
    location->longitude.value = integer * 1000000 + fraction;
    location->longitude.decimal_places = 6;

    // Adjust latitude and longitude based on cardinal direction
    if (location->latitude_raw.cardinal == 'S') {
        location->latitude.value = -location->latitude.value;
    }
    if (location->longitude_raw.cardinal == 'W') {
        location->longitude.value = -location->longitude.value;
    }
}

void decodeSpeed(nmea_speed* speed) {
    const char* raw = speed->speed_raw;
    int32_t value = NMEA_Parser_strtoi32(raw);
    speed->speed_knot.value = value;
    speed->speed_knot.decimal_places = 2;
}

void decodeCourse(nmea_course* course) {
    const char* raw = course->course_raw;
    int32_t value = NMEA_Parser_strtoi32(raw);
    course->course_degree.value = value;
    course->course_degree.decimal_places = 2;
}

void decodeHDOP(nmea_hdop* hdop) {
    const char* raw = hdop->hdop_raw;
    int32_t value = NMEA_Parser_strtoi32(raw);
    hdop->hdop.value = value;
    hdop->hdop.decimal_places = 2;
}

void decodeAltitude(nmea_altitude* altitude) {
    const char* raw = altitude->altitude_raw;
    int32_t value = NMEA_Parser_strtoi32(raw);
    altitude->altitude_meter.value = value;
    altitude->altitude_meter.decimal_places = 1;
}
