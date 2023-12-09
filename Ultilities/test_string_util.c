#include <stdint.h>
#include <stdio.h>
#include "string_util.h"

char* test_str1 = "Hello My name is Barry Alen";
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
    printf("\nDoes \"%s\" start with \"%s\": %d", test_str1, test_str_startWith, UTIL_STRING_isStartWith(test_str1, test_str_startWith)); 
    printf("\nDoes \"%s\" is the same with \"%s\": %d", test_str1, test_str_comparedTo, UTIL_STRING_comparedTo(test_str1, test_str_comparedTo));
    printf("\nLength of \"%s\": %d", test_str_getLength, UTIL_STRING_getLength(test_str_getLength));
    printf("\nIndex of \'%c\' in \"%s\": %d", test_str_indexOf, test_str1, UTIL_STRING_indexOf(test_str1, test_str_indexOf));
    printf("\nSubstring of \"%s\" from index %d is: %s", test_str1, test_str_getSubString_index, UTIL_STRING_getSubStringFromIndex(test_str1, test_str_getSubString_index, test_str_getSubString));
    printf("\nSubstring of \"%s\" from char %c is: %s", test_str1, test_str_getSubString_char, UTIL_STRING_getSubStringFromChar(test_str1, test_str_getSubString_char, test_str_getSubString));
    printf("\nSubstring of \"%s\" from index %d to %d is: %s", test_str1, test_str_getSubStringBetweenIndex1, test_str_getSubStringBetweenIndex2, UTIL_STRING_getSubStringBetweenIndex(test_str1, test_str_getSubStringBetweenIndex1, test_str_getSubStringBetweenIndex2, test_str_getSubString));
    printf("\nSubstring of \"%s\" from character %c to %c is: %s", test_str1, test_str_getSubStringBetweenChar1, test_str_getSubStringBetweenChar2, UTIL_STRING_getSubStringTerminatedChar(test_str1, test_str_getSubStringBetweenChar1, test_str_getSubStringBetweenChar2, test_str_getSubString));
}
