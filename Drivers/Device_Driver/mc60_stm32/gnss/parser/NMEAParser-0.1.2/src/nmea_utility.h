#ifndef __NMEA_UTILITY_H
#define __NMEA_UTILITY_H

#include <time.h>

#include "nmea_core.h"

// This header file provides utility functions for processing NMEA data.

// Processes the incoming character 'c' and updates the NMEA data structure 'data' accordingly.
// Returns true if a complete NMEA sentence is parsed and processed successfully, false otherwise.
bool NMEA_Parser_Process(nmea_data* data, char c);

// Converts the NMEA data structure to the 'struct tm' format.
void NMEA_Parser_nmeadata_to_tm(const nmea_data* data, struct tm* timeinfo);
// Converts the 'struct tm' time information to the NMEA data structure.
void NMEA_Parser_tm_to_nmeadata(const struct tm* timeinfo, nmea_data* data);
// Changes the time zone of the NMEA data structure.
void NMEA_Parser_changeTimezone(nmea_data* data, int timezone_offset);

#endif