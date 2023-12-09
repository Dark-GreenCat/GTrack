#include "string_util.h"
#include <stdint.h>
#include <string.h>

bool UTIL_STRING_isStartWith(const char* String, const char* StartString) {
    return !((bool) strncmp(String, StartString, strlen(StartString)));
}

bool UTIL_STRING_comparedTo(const char* String, const char* CompareString) {
    return !((bool) strcmp(String, CompareString));
}

uint32_t UTIL_STRING_getLength(const char* String) {
    uint32_t count = 0;
    while (*String++ != '\0') {
        count++;
    }

    return count;
}

int32_t UTIL_STRING_indexOf(const char* String, const char Character) {
    int32_t index = -1;

    while (*String != '\0') {
        index++;
        if (*String == Character) {
            return index;
        }
        String++;
    }

    return -1;
}

char* UTIL_STRING_getSubStringFromIndex(const char* String, uint32_t Index, char* Destination) {
    char* Destination_Begin = Destination;

    const char* SubString = String + Index; 
    while (*SubString != '\0') {
        *Destination++ = *SubString++;
    }
    *Destination = '\0';

    return Destination_Begin;
}

char* UTIL_STRING_getSubStringBetweenIndex(const char* String, uint32_t Index_Begin, uint32_t Index_End, char* Destination) {
    char* Destination_Begin = Destination;

    for(uint32_t Index = Index_Begin; Index <= Index_End; Index++) {
        *Destination++ = String[Index];
    }
    *Destination = '\0';

    return Destination_Begin;
}

char* UTIL_STRING_getSubStringFromChar(const char* String, const char Character, char* Destination) {
    uint32_t Index = UTIL_STRING_indexOf(String, Character);
    return UTIL_STRING_getSubStringFromIndex(String, Index, Destination);
}

char* UTIL_STRING_getSubStringTerminatedChar(const char* String, uint32_t Char_Begin, uint32_t Char_Terminated, char* Destination) {
    char* Destination_Begin = Destination;
    uint32_t Index_Begin = UTIL_STRING_indexOf(String, Char_Begin);

    const char* SubString = String + Index_Begin;
    while (*SubString != Char_Terminated && *SubString != '\0') {
        *Destination++ = *SubString++;
    }
    *Destination = '\0';

    return Destination_Begin;
}
