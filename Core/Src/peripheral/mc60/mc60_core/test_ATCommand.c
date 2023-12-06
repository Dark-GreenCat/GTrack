#include <stdio.h>
#include "ATCommand.h"

uint8_t AT_Response[] =   "+QGNSSRD: $GNRMC,034035.000,A,3150.8617,N,11711.9038,E,3.02,183.45,240516,,,A*75\
                            \n$GNVTG,183.45,T,,M,3.02,N,5.59,K,A*20\
                            \n$GNGGA,034035.000,3150.8617,N,11711.9038,E,1,4,1.50,40.9,M,0.0,M,,*44\
                            \n$GPGSA,A,3,26,21,,,,,,,,,,,1.75,1.50,0.91*0A\
                            \n$GLGSA,A,3,82,70,,,,,,,,,,,1.75,1.50,0.91*1C\
                            \n$GPGSV,3,1,12,16,67,308,,26,58,021,16,23,40,307,,31,40,088,*7F\
                            \n$GPGSV,3,2,12,08,17,199,,09,14,320,,21,10,086,14,14,10,153,*73\
                            \n$GPGSV,3,3,12,22,09,226,,193,06,165,,32,03,154,,29,01,034,*45\
                            \n$GLGSV,3,1,09,81,44,073,,79,40,041,,82,38,145,15,80,36,323,*66\
                            \n$GLGSV,3,2,09,70,30,290,16,69,26,225,,78,12,078,,88,09,027,*64\
                            \n$GLGSV,3,3,09,71,05,334,*5B\
                            \n$GNGLL,3150.8617,N,11711.9038,E,034035.000,A,A*4C\
                            \n\
                            \nOK";

int main() {
    uint8_t lineCount = 1;
    uint8_t* response = AT_Response;

    while(*response != '\0') {
        printf("%c", *response);
        if(*response++ == '\n') lineCount++;
    }

    printf("\n\n> Line count: %d", lineCount);
}