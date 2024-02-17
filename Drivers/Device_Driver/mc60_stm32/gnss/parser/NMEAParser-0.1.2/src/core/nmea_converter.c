#include "nmea_converter.h"

#include <string.h>
#include <stdio.h>

char* NMEA_Parser_getSubstring(char* destination, const char* source, uint32_t start_index, uint32_t size) {
    strncpy(destination, source + start_index, size);
    destination[size] = '\0';

    return destination;
}

int32_t NMEA_Parser_strtoi32(const char* str) {
    int32_t result = 0;
    int32_t sign = 1;
    int32_t i = 0;
    bool overflow = false;

    // Check for negative sign
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    // Parse digits
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            int32_t digit = str[i] - '0';
            if (!overflow && (result > INT32_MAX / 10 || (result == INT32_MAX / 10 && digit > (INT32_MAX % 10 + (sign == -1))))) {
                overflow = true;
            }
            if (!overflow) {
                result = result * 10 + digit;
            }
        }
    }

    return result * sign;
}

int32_t NMEA_Parser_strntoi32(const char* str, uint32_t start_index, uint32_t size) {
    char number[size + 1];
    NMEA_Parser_getSubstring(number, str, start_index, size);
    return NMEA_Parser_strtoi32(number);
}


uint32_t NMEA_Parser_strtou32(const char* str) {
    uint32_t result = 0;
    uint32_t i = 0;
    bool overflow = false;

    // Parse digits
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            uint32_t digit = str[i] - '0';
            if (!overflow && (result > UINT32_MAX / 10 || (result == UINT32_MAX / 10 && digit > UINT32_MAX % 10))) {
                overflow = true;
            }
            if (!overflow) {
                result = result * 10 + digit;
            }
        }
    }

    return result;
}

uint32_t NMEA_Parser_strntou32(const char* str, uint32_t start_index, uint32_t size) {
    char number[size + 1];
    NMEA_Parser_getSubstring(number, str, start_index, size);
    return NMEA_Parser_strtou32(number);
}

char* NMEA_Parser_numtostr(int number, int decimal_places, char* result) {
    int sign = (number < 0) ? -1 : 1;
    number = (number < 0) ? -number : number;

    int divisor = 1;
    for (int i = 0; i < decimal_places; ++i) {
        divisor *= 10;
    }
    int integer_part = number / divisor;
    int fractional_part = number % divisor;

    sprintf(result, "%s%d.%0*d", (sign < 0) ? "-" : "", integer_part, decimal_places, fractional_part);

    return result;
}

char* NMEA_Parser_nmeafloattostr(nmea_float number, char* result) {
    return NMEA_Parser_numtostr(number.value, number.decimal_places, result);
}

double NMEA_Parser_nmeafloattod(nmea_float number) {
    double result = (double) number.value;
    for (uint8_t i = 0; i < number.decimal_places; i++) {
        result /= 10.0f;
    }

    return result;
}
