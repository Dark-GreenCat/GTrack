#include "display_pal.h"

void PAL_DISPLAY_Show(const char* str) {
    PAL_UART_OutString(huart_terminal, str);
}

void PAL_DISPLAY_ShowNumber(uint32_t number) {
    PAL_UART_OutNumber(huart_terminal, number);
}

void PAL_DISPLAY_ShowNumberSigned(int32_t number) {
    PAL_UART_OutNumber_Signed(huart_terminal, number);
}
