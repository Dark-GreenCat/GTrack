#ifndef __GGA_H
#define __GGA_H

#include <stdint.h>
#include "../../nmea_global.h"
#include "../../nmea_core.h"

#define GGA_FIELD_TIME                  1
#define GGA_FIELD_LATITUDE              2
#define GGA_FIELD_LATITUDE_CARDINAL     3
#define GGA_FIELD_LONGITUDE             4
#define GGA_FIELD_LONGITUDE_CARDINAL    5
#define GGA_FIELD_FIX_STATUS            6
#define GGA_FIELD_HDOP                  8
#define GGA_FIELD_ALTITUDE              9

static inline void saveFieldNMEA_GGA(nmea_data* data, uint8_t field_index) {
    switch (field_index) {
        case GGA_FIELD_TIME:
            setRawTime(&data->Time, Term);
            if(data->Time.time_raw[0] != '\0') {
                data->Time.is_valid = true;
                decodeTime(&data->Time);
            }
            else data->Time.is_valid = false;
            break;

        case GGA_FIELD_LATITUDE:
            setRawLocation(&data->Location.latitude_raw, Term);
            break;

        case GGA_FIELD_LATITUDE_CARDINAL:
            setRawLocationCardinal(&data->Location.latitude_raw, Term);
            break;

        case GGA_FIELD_LONGITUDE:
            setRawLocation(&data->Location.longitude_raw, Term);
            break;

        case GGA_FIELD_LONGITUDE_CARDINAL:
            setRawLocationCardinal(&data->Location.longitude_raw, Term);
            if(data->Location.longitude_raw.location[0] != '\0') {
                data->Location.is_valid = true;
                decodeLocation(&data->Location);
            }
            else data->Location.is_valid = false;
            break;
        
        case GGA_FIELD_FIX_STATUS:
            isFix = (*Term > '0');
            break;

        case GGA_FIELD_HDOP:
            setRawHDOP(&data->HDOP, Term);
            if(data->HDOP.hdop_raw[0] != '\0') {
                data->HDOP.is_valid = true;
                decodeHDOP(&data->HDOP);
            }
            else data->HDOP.is_valid = false;
            break;

        case GGA_FIELD_ALTITUDE:
            setRawAltitude(&data->Altitude, Term);
            if(data->Altitude.altitude_raw[0] != '\0') {
                data->Altitude.is_valid = true;
                decodeAltitude(&data->Altitude);
            }
            else data->Altitude.is_valid = false;
            break;

        default:
            break;
    }
}

#endif /* __GGA_H */