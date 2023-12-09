#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

char* MC60_Response_getFirstInfo(char* MC60_Response, char* Destination);
char* MC60_Response_getFirstLine(char* MC60_Response, char* Destination);

char* MC60_ResponseLine_getHeader(char* MC60_ResponseLine, char* Destination);
char* MC60_ResponseLine_getFirstData(char* MC60_ResponseLine, char* Destination);

#endif
