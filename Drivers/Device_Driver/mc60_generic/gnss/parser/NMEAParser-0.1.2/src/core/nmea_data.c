#include "nmea_data.h"

#include <string.h>

void setRawTime(nmea_time* time, char* term) { strcpy(time->time_raw, term); }
void setRawDate(nmea_date* date, char* term) { strcpy(date->date_raw, term); }
void setRawLocation(nmea_location_raw* location_raw, char* term) { strcpy(location_raw->location, term); }
void setRawLocationCardinal(nmea_location_raw* location_raw, char* term) { location_raw->cardinal = *term; }
void setRawSpeed(nmea_speed* speed, char* term) { strcpy(speed->speed_raw, term); }
void setRawCourse(nmea_course* course, char* term) { strcpy(course->course_raw, term); }
void setRawHDOP(nmea_hdop* hdop, char* term) { strcpy(hdop->hdop_raw, term); }
void setRawAltitude(nmea_altitude* altitude, char* term) { strcpy(altitude->altitude_raw, term); }