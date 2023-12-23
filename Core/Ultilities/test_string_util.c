#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "string_util.h"

char* test_str1 = "Hello My name is Barry Alen";
uint32_t copied_index = 6;
uint32_t copied_length = 7;
uint32_t test_str_compare_number = 3;
char* test_str_startWith = "Hello ";
char* test_str_comparedTo = "HelloMy name is Barry Alen";

char* test_str_getLength = "Hello";
char test_str_indexOf = 'o';

uint32_t test_str_getSubString_index = 9;
char test_str_getSubString[100];

char test_str_getSubString_char = 'a';
uint32_t test_str_getSubStringBetweenIndex1 = 4,
         test_str_getSubStringBetweenIndex2 = 18;

char test_str_getSubStringBetweenChar1 = 'a',
     test_str_getSubStringBetweenChar2 = 'y';

int main() {
    printf("\nDuplicate of \"%s\" is \"%s\"", test_str1, UTIL_STRING_Duplicate(test_str1, test_str_getSubString));
    printf("\nCopy of \"%s\" from index %d with length %d is \"%s\"", test_str1, copied_index, copied_length, UTIL_STRING_Copy(test_str1, copied_index, copied_length, test_str_getSubString));
    printf("\nCompare difference between \"%s\" to \"%s\": %d", test_str1, test_str_startWith, UTIL_STRING_compareDifference(test_str1, test_str_startWith));
    printf("\nCompare difference between first %d character of \"%s\" to \"%s\": %d", test_str_compare_number, test_str1, test_str_startWith, UTIL_STRING_compareDifferenceFirstNChar(test_str1, test_str_startWith, test_str_compare_number));
    printf("\nDoes \"%s\" start with \"%s\": %d", test_str1, test_str_startWith, UTIL_STRING_isStartWith(test_str1, test_str_startWith)); 
    printf("\nDoes \"%s\" is the same with \"%s\": %d", test_str1, test_str_comparedTo, UTIL_STRING_comparedTo(test_str1, test_str_comparedTo));
    printf("\nLength of \"%s\": %d", test_str_getLength, UTIL_STRING_getLength(test_str_getLength));
    printf("\nIndex of \'%c\' in \"%s\": %d", test_str_indexOf, test_str1, UTIL_STRING_indexOf(test_str1, test_str_indexOf));
    printf("\nSubstring of \"%s\" from index %d is: %s", test_str1, test_str_getSubString_index, UTIL_STRING_getSubStringFromIndex(test_str1, test_str_getSubString_index, test_str_getSubString));
    printf("\nSubstring of \"%s\" from char %c is: %s", test_str1, test_str_getSubString_char, UTIL_STRING_getSubStringFromChar(test_str1, test_str_getSubString_char, test_str_getSubString));
    printf("\nSubstring of \"%s\" from index %d to %d is: %s", test_str1, test_str_getSubStringBetweenIndex1, test_str_getSubStringBetweenIndex2, UTIL_STRING_getSubStringBetweenIndex(test_str1, test_str_getSubStringBetweenIndex1, test_str_getSubStringBetweenIndex2, test_str_getSubString));
    printf("\nSubstring of \"%s\" before character '%c' is: \"%s\"", test_str1, 'y', UTIL_STRING_getSubStringBeforeChar(test_str1, 'y', test_str_getSubString));

  printf("\n\n\n");
  
  char SerialLine[128] = "AT+QGNSSRD: $GNGLL,,,,,N,044013.949,V,N*62@";
  char* p_SerialLine = SerialLine;
  printf("\nSerialLine: \"%s\"", p_SerialLine);
  UTIL_STRING_getSubStringAfterChar(p_SerialLine, ' ', p_SerialLine);
  printf("\nSerialLine after ' ' is: \"%s\"", p_SerialLine);
  UTIL_STRING_getSubStringBeforeChar(p_SerialLine, '@', p_SerialLine);
  printf("\nSerialLine before '@' is: \"%s", p_SerialLine);

  char GNGLL_Data[50];
  uint32_t index = -1;
  uint8_t timeout = 15;
  do {
    p_SerialLine += index + 1;
    UTIL_STRING_getSubStringBeforeChar(p_SerialLine, ',', GNGLL_Data);
    printf("\nData: \"%s\"", GNGLL_Data);
    index = (uint32_t) UTIL_STRING_indexOf(p_SerialLine, ',');
  } while (index != (uint32_t) -1 && timeout--);
}
