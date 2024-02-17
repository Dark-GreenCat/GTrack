#ifndef __NMEA_DECODER_H
#define __NMEA_DECODER_H

#include <stdbool.h>
#include "nmea_data.h"

// Decodes the raw time string in the nmea_time structure and sets the result in the hours, minutes, seconds, and milliseconds fields.
void decodeTime(nmea_time* time);

// Decodes the raw date string in the nmea_date structure and sets the result in the day, month, and year fields.
void decodeDate(nmea_date* date);

// Decodes the raw location string in the nmea_location structure and sets the result in the latitude and longitude fields.
void decodeLocation(nmea_location* location_raw);

// Decodes the raw speed string in the nmea_speed structure and sets the result in the speed_knot field.
void decodeSpeed(nmea_speed* speed);

// Decodes the raw course string in the nmea_course structure and sets the result in the course_degree field.
void decodeCourse(nmea_course* course);

// Decodes the raw HDOP string in the nmea_hdop structure and sets the result in the hdop field.
void decodeHDOP(nmea_hdop* hdop);

// Decodes the raw altitude string in the nmea_altitude structure and sets the result in the altitude_meter field.
void decodeAltitude(nmea_altitude* altitude);

#endif /* __NMEA_DECODER_H */