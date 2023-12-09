#ifndef __STRING_UTIL_H
#define __STRING_UTIL_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

bool UTIL_STRING_isStartWith(const char* String, const char* StartString);
bool UTIL_STRING_comparedTo(const char* String, const char* CompareString);
uint32_t UTIL_STRING_getLength(const char* String);
int32_t UTIL_STRING_indexOf(const char* String, const char Character);
char* UTIL_STRING_getSubStringFromIndex(const char* String, uint32_t Index, char* Destination);
char* UTIL_STRING_getSubStringBetweenIndex(const char* String, uint32_t Index_Begin, uint32_t Index_End, char* Destination);
char* UTIL_STRING_getSubStringFromChar(const char* String, const char Character, char* Destination);
char* UTIL_STRING_getSubStringTerminatedChar(const char* String, uint32_t Char_Begin, uint32_t Char_Terminated, char* Destination);

#endif
