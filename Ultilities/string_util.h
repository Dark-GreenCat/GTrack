#ifndef __STRING_UTIL_H
#define __STRING_UTIL_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

char* UTIL_STRING_Duplicate(const char* String, char* CopiedString);
char* UTIL_STRING_Copy(const char* String, uint32_t StartIndex, uint32_t CopiedLength, char* CopiedString);
int16_t UTIL_STRING_compareDifference(const char* String, const char* CompareString);
int16_t UTIL_STRING_compareDifferenceFirstNChar(const char* String, const char* CompareString, const uint32_t NumberOfChar);
bool UTIL_STRING_isStartWith(const char* String, const char* StartString);
bool UTIL_STRING_comparedTo(const char* String, const char* CompareString);
uint32_t UTIL_STRING_getLength(const char* String);
int32_t UTIL_STRING_indexOf(const char* String, const char Character);
char* UTIL_STRING_getSubStringFromIndex(const char* String, uint32_t Index, char* Destination);
char* UTIL_STRING_getSubStringBetweenIndex(const char* String, uint32_t Index_Begin, uint32_t Index_End, char* Destination);
char* UTIL_STRING_getSubStringFromChar(const char* String, const char Character, char* Destination);
char* UTIL_STRING_getSubStringBeforeChar(const char* String, char TerminatedChar, char* Destination);
char* UTIL_STRING_getSubStringAfterChar(const char* String, char AfterChar, char* Destination);

#endif
