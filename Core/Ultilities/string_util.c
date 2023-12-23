#include "string_util.h"
#include <stdint.h>
#include <stdio.h>

char* UTIL_STRING_Duplicate(const char* String, char* CopiedString) {
    char* p_CopiedString = CopiedString;
    while (*String != '\0') *CopiedString++ = *String++;
    *CopiedString = '\0';

    return p_CopiedString;
}

char* UTIL_STRING_Copy(const char* String, uint32_t StartIndex, uint32_t CopiedLength, char* CopiedString){
    char* p_CopiedString = CopiedString;
    while (CopiedLength--) {
        *CopiedString++ = String[StartIndex++];
    }
    *CopiedString = '\0';

    return p_CopiedString;
}

int16_t UTIL_STRING_compareDifference(const char* String, const char* CompareString) {
    int16_t Difference = 0;
    while (*String != '\0' && *CompareString != '\0') {
         Difference = *String++ - *CompareString++;
         if(Difference != 0) break;
    }
    
    if (*String != '\0' && *CompareString == '\0') return 1;
    if (*String == '\0' && *CompareString != '\0') return -1;
    return Difference;
}

int16_t UTIL_STRING_compareDifferenceFirstNChar(const char* String, const char* CompareString, const uint32_t NumberOfChar) {
    int16_t Difference = 0;
    uint32_t Index = 0;
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
    uint32_t Count = 0;
    while (*String++ != '\0') Count++;

    return Count;
}

int32_t UTIL_STRING_indexOf(const char* String, const char Character) {
    int32_t Index = -1;

    while (*String != '\0') {
        Index++;
        if (*String == Character) return Index;
        String++;
    }

    return -1;
}

char* UTIL_STRING_getSubStringFromIndex(const char* String, uint32_t Index, char* Destination) {
    return UTIL_STRING_Duplicate(String + Index, Destination);
}

char* UTIL_STRING_getSubStringBetweenIndex(const char* String, uint32_t Index_Begin, uint32_t Index_End, char* Destination) {
    return UTIL_STRING_Copy(String, Index_Begin, Index_End - Index_Begin + 1, Destination);
}

char* UTIL_STRING_getSubStringFromChar(const char* String, const char Character, char* Destination) {
    uint32_t Index = (uint32_t) UTIL_STRING_indexOf(String, Character);
    if(Index == (uint32_t) -1) {
        *Destination = '\0';
        return Destination;
    }
    return UTIL_STRING_getSubStringFromIndex(String, Index, Destination);
}

char* UTIL_STRING_getSubStringBeforeChar(const char* String, char TerminatedChar, char* Destination) {
    uint32_t Index_End = 0;
    while (String[Index_End] != TerminatedChar && String[Index_End] != '\0') {  
        Index_End++;
    }

    return UTIL_STRING_Copy(String, 0, Index_End, Destination);
}

char* UTIL_STRING_getSubStringAfterChar(const char* String, char AfterChar, char* Destination) {
    uint32_t Index = (uint32_t) UTIL_STRING_indexOf(String, AfterChar);

    return UTIL_STRING_getSubStringFromIndex(String, Index + 1, Destination);
}
