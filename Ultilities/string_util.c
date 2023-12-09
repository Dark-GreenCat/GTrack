#include "string_util.h"

int16_t UTIL_STRING_compareDifference(const char* String, const char* CompareString) {
    int16_t Difference;
    while (*String != '\0' && *CompareString != '\0') {
         Difference = *String++ - *CompareString++;
         if(Difference != 0) break;
    }
    
    if (*String != '\0' && *CompareString == '\0') return 1;
    if (*String == '\0' && *CompareString != '\0') return -1;
    return Difference;
}

int16_t UTIL_STRING_compareDifferenceFirstNChar(const char* String, const char* CompareString, const uint32_t NumberOfChar) {
    int16_t Difference;
    uint32_t Index;
    for(Index = 0; Index < NumberOfChar; Index++) {
        if(String[Index] == '\0' || CompareString[Index] == '\0') break;
        Difference = String[Index] - CompareString[Index];
        if(Difference != 0) break;
    }
    
    Index--;
    if (String[Index] != '\0' && CompareString[Index] == '\0') return 1;
    if (String[Index] == '\0' && CompareString[Index] != '\0') return -1;
    return Difference;
}

bool UTIL_STRING_isStartWith(const char* String, const char* StartString) {
    return !((bool) UTIL_STRING_compareDifferenceFirstNChar(String, StartString, strlen(StartString)));
}

bool UTIL_STRING_comparedTo(const char* String, const char* CompareString) {
    return !((bool) UTIL_STRING_compareDifference(String, CompareString));
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
