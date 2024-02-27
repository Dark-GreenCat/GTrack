#ifndef __RMC_H
#define __RMC_H

#include <stdint.h>
#include "../../nmea_global.h"
#include "../../nmea_core.h"

#define RMC_FIELD_TIME                  1
#define RMC_FIELD_DATA_VALID            2  
#define RMC_FIELD_LATITUDE              3
#define RMC_FIELD_LATITUDE_CARDINAL     4
#define RMC_FIELD_LONGITUDE             5
#define RMC_FIELD_LONGITUDE_CARDINAL    6
#define RMC_FIELD_SPEED                 7
#define RMC_FIELD_COURSE                8
#define RMC_FIELD_DATE                  9

static inline void saveFieldNMEA_RMC(nmea_data* data, uint8_t field_index) {
    switch (field_index) {
        case RMC_FIELD_TIME:
            setRawTime(&data->Time, Term);
            if(data->Time.time_raw[0] != '\0') {
                data->Time.is_valid = true;
                decodeTime(&data->Time);
            }
            else data->Time.is_valid = false;
            break;
        
        case RMC_FIELD_DATA_VALID:
            isFix = (*Term == 'A');
            break;

        case RMC_FIELD_LATITUDE:
            setRawLocation(&data->Location.latitude_raw, Term);
            break;

        case RMC_FIELD_LATITUDE_CARDINAL:
            setRawLocationCardinal(&data->Location.latitude_raw, Term);
            break;

        case RMC_FIELD_LONGITUDE:
            setRawLocation(&data->Location.longitude_raw, Term);
            break;

        case RMC_FIELD_LONGITUDE_CARDINAL:
            setRawLocationCardinal(&data->Location.longitude_raw, Term);
            if(data->Location.longitude_raw.location[0] != '\0') {
                data->Location.is_valid = true;
                decodeLocation(&data->Location);
            }
            else data->Location.is_valid = false;
            break;

        case RMC_FIELD_SPEED:
            setRawSpeed(&data->Speed, Term);
            if(data->Speed.speed_raw[0] != '\0') {
                data->Speed.is_valid = true;
                decodeSpeed(&data->Speed);
            }
            else data->Speed.is_valid = false;
            break;

        case RMC_FIELD_COURSE:
            setRawCourse(&data->Course, Term);
            if(data->Course.course_raw[0] != '\0') {
                data->Course.is_valid = true;
                decodeCourse(&data->Course);            
            }
            else data->Course.is_valid = false;
            break;

        case RMC_FIELD_DATE:
            setRawDate(&data->Date, Term);
            if(data->Date.date_raw[0] != '\0') {
                data->Date.is_valid = true;
                decodeDate(&data->Date);
            }
            else data->Date.is_valid = false;
            break;

        default:
            break;
    }
}

#endif /* __RMC_H */