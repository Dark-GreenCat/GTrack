#ifndef __UAL_GTRACK_H
#define __UAL_GTRACK_H

#include "mc60/mc60_pal.h"
#include "timer/timer_hcl.h"
#include "display/display_pal.h"
#include "gtrack_nal.h"

typedef enum {
    GEOTRACK_DEACTIVATE = 0,
    GEOTRACK_ACTIVATE
} feature_geotrack_state;

void UAL_GTRACK_Init();

void UAL_GTRACK_GeoTrack_Enable();
void UAL_GTRACK_GeoTrack_Activate(feature_geotrack_state state);
void UAL_GTRACK_GeoTrack_GetMetric();
void UAL_GTRACK_GeoTrack_UploadData();

#endif