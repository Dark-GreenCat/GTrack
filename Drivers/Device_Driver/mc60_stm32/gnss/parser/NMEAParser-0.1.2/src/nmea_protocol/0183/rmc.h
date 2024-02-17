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
            decodeTime(&data->Time);
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
            decodeLocation(&data->Location);
            break;

        case RMC_FIELD_SPEED:
            setRawSpeed(&data->Speed, Term);
            decodeSpeed(&data->Speed);
            break;

        case RMC_FIELD_COURSE:
            setRawCourse(&data->Course, Term);
            decodeCourse(&data->Course);
            break;

        case RMC_FIELD_DATE:
            setRawDate(&data->Date, Term);
            decodeDate(&data->Date);
            break;

        default:
            break;
    }
}

#endif /* __RMC_H */