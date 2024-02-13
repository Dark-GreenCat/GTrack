#ifndef __BAM253_PAL_H
#define __BAM253_PAL_H

#include <stdint.h>
#include "bma253_driver.h"
#include "i2c/i2c_hcl.h"

typedef bma253_t BMA253_TypeDef;

extern BMA253_TypeDef pal_bma253;

void PAL_BMA253_Init();
void PAL_BMA253_Get_Accel_XYZ(bma253_accel_data_t* bma253_accel_data);

#endif