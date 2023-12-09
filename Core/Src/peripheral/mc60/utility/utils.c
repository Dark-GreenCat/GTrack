#include "utils.h"
#include <stdio.h>
#include <string.h>

char *MC60_Response_getFirstInfo(char *MC60_Response, char *Destination) {
  if (*MC60_Response == '\0') {
    *Destination = '\0';
    return NULL;
  }

  char *p_Info_Begin = strstr(MC60_Response, "\r\n");
  char *p_Info_End = NULL;

  if (p_Info_Begin) {
    p_Info_End = strstr(p_Info_Begin + 2, "\r\n\r\n");
    // if (p_Info_End == NULL)
    // p_Info_End = strstr(p_Info_Begin + 2, "\r\n\0");

    if (p_Info_End) {
      p_Info_Begin += 2;

      while (p_Info_Begin < p_Info_End) {
        *Destination++ = *p_Info_Begin++;
      }
    }
  }

  *Destination = '\0';

  return p_Info_End + 2;
}

char *MC60_Response_getFirstLine(char *MC60_Response, char *Destination) {
  if (MC60_Response == NULL) {
    *Destination = '\0';
    return NULL;
  }

  while (!(*MC60_Response == '\r' && *(MC60_Response + 1) == '\n')) {
      if (*MC60_Response == '\0') {
          *Destination = '\0';
          return NULL;
      }
      *Destination++ = *MC60_Response++;
  }

  *Destination = '\0';

  return MC60_Response + 2;
}


char* MC60_ResponseLine_getHeader(char* MC60_ResponseLine, char* Destination) {
  if (MC60_ResponseLine == NULL) {
    *Destination = '\0';
    return NULL;
  }

  if(*MC60_ResponseLine == '+') {
    while (*++MC60_ResponseLine != ':') {
      *Destination++ = *MC60_ResponseLine;
    }

    MC60_ResponseLine++;
  }
  *Destination = '\0';

  return MC60_ResponseLine;
}


char* MC60_ResponseLine_getFirstData(char* MC60_ResponseLine, char* Destination) {
  if(MC60_ResponseLine == NULL) {
    *Destination = '\0';
    return NULL;
  }

  while (*MC60_ResponseLine == ' ') MC60_ResponseLine++;
  while (*MC60_ResponseLine != ',' && *MC60_ResponseLine != '\0') {
    *Destination++ = *MC60_ResponseLine++;
  }
  *Destination = '\0';
  
  if(*MC60_ResponseLine == '\0') return NULL;
  return MC60_ResponseLine + 1;
}
