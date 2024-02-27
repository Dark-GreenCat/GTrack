#ifndef __DISPLAY_PAL_H
#define __DISPLAY_PAL_H

#include "usart/usart_pal.h"

void PAL_DISPLAY_Show(const char* str);
void PAL_DISPLAY_ShowNumber(uint32_t number);
void PAL_DISPLAY_ShowNumberSigned(int32_t number);

#endif