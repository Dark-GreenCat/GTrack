#ifndef NMEA_CONVERTER_H
#define NMEA_CONVERTER_H

#include <stdint.h>
#include "nmea_data.h"

// Extracts a substring from the source string and copies it to the destination string.
// The substring starts at the start_index and has a length of size.
char* NMEA_Parser_getSubstring(char* destination, const char* source, uint32_t start_index, uint32_t size);

// Converts a null-terminated string to a 32-bit signed integer.
// Non-digit characters are automatically ignored during the conversion.
int32_t NMEA_Parser_strtoi32(const char* str);

// Converts a substring of a null-terminated string to a 32-bit signed integer.
// The substring starts at the start_index and has a length of size.
// Non-digit characters are automatically ignored during the conversion.
int32_t NMEA_Parser_strntoi32(const char* str, uint32_t start_index, uint32_t size);

// Converts a null-terminated string to a 32-bit unsigned integer.
// Non-digit characters are automatically ignored during the conversion.
uint32_t NMEA_Parser_strtou32(const char* str);

// Converts a substring of a null-terminated string to a 32-bit unsigned integer.
// The substring starts at the start_index and has a length of size.
// Non-digit characters are automatically ignored during the conversion.
uint32_t NMEA_Parser_strntou32(const char* str, uint32_t start_index, uint32_t size);

// Converts a number to a string representation with a specified number of decimal places.
// The resulting string is stored in the result buffer.
char* NMEA_Parser_numtostr(int number, int decimal_places, char* result);

// Converts an nmea_float structure to a string representation.
// The resulting string is stored in the result buffer.
char* NMEA_Parser_nmeafloattostr(nmea_float number, char* result);

// Converts an nmea_float structure to a double value.
double NMEA_Parser_nmeafloattod(nmea_float number);

#endif