#include <stdio.h>

#include "utils.h"

int main() {
  char* MC60_Response =
    "AT+QGNSSRD?\r\r\n"
    "+QGNSSRD: $GNRMC,100237.000,A,2102.5257,N,10547.2108,E,0.46,211.71,061223,,,A*7D\r\n"
    "$GNVTG,211.71,T,,M,0.46,N,0.85,K,A*28\r\n"
    "$GNGGA,100237.000,2102.5257,N,10547.2108,E,1,5,2.98,52.6,M,-20.9,M,,*5C\r\n"
    "$GPGSA,A,3,07,27,08,,,,,,,,,,3.14,2.98,0.99*0D\r\n"
    "$GLGSA,A,3,73,80,,,,,,,,,,,3.14,2.98,0.99*17\r\n"
    "$GPGSV,2,1,07,08,74,005,23,42,44,117,,07,35,327,31,27,32,035,33*74\r\n"
    "$GPGSV,2,2,07,193,,,,194,,,,195,,,*44\r\n"
    "$GLGSV,1,1,02,80,38,025,33,73,20,325,29*6A\r\n"
    "$GNGLL,2102.5257,N,10547.2108,E,100237.000,A,A*48\r\n"
    "\r\n"
    "OK\r\n";
  
  char MC60_ResponseLine[128];
  while(MC60_Response) {
    MC60_Response = MC60_Response_getFirstLine(MC60_Response, MC60_ResponseLine);
    printf("\nRES LINE: %s", MC60_ResponseLine);
    
    char* p_MC60_ResponseLine = MC60_ResponseLine;
    char MC60_ResponseLine_Header[32];
    p_MC60_ResponseLine = MC60_ResponseLine_getHeader(p_MC60_ResponseLine, MC60_ResponseLine_Header);
    printf("\n\tHEADER: %s", MC60_ResponseLine_Header);
    
    while (p_MC60_ResponseLine) {
      char MC60_ResponseLine_Data[32];
      p_MC60_ResponseLine = MC60_ResponseLine_getFirstData(p_MC60_ResponseLine, MC60_ResponseLine_Data);
      printf("\n\t\tDATA: %s", MC60_ResponseLine_Data);
    }
  }

  // char MC60_InfoResponse[512];
  // while (MC60_Response) {
  //   MC60_Response = MC60_Response_getFirstInfo(MC60_Response, MC60_InfoResponse); 
  //   printf("\nINFO RES: %s", MC60_InfoResponse);
  //   printf("\nRemain: %s", MC60_Response);
  // }
}
