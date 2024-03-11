#ifndef __DISPLAY_PAL_H
#define __DISPLAY_PAL_H

#include "usart/usart_pal.h"

void PAL_DISPLAY_Show(const char* str);
void PAL_DISPLAY_ShowNumber(uint32_t number);
void PAL_DISPLAY_ShowNumberSigned(int32_t number);

/**
 * Display formatted debug output with support for the following format specifiers:
 * - %d: Signed integer value
 * - %c: Character value
 * - %x: Lowercase hexadecimal value
 * - %X: Uppercase hexadecimal value
 * - %f: Floating-point value (default precision of 6 decimal places)
 * - %s: String value
 * - %.*f: Floating-point value with a variable precision specifier
 *
 * @param format The format string containing the format specifiers.
 * @param ... Additional arguments corresponding to the format specifiers.
 */
void PAL_DISPLAY_Debug(const char* format, ...);

#endif