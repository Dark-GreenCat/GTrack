#include "display_pal.h"

#include "stdio.h"
#include "stdarg.h"

void PAL_DISPLAY_Show(const char* str) {
    PAL_UART_OutString(huart_terminal, str);
}

void PAL_DISPLAY_ShowNumber(uint32_t number) {
    PAL_UART_OutNumber(huart_terminal, number);
}

void PAL_DISPLAY_ShowNumberSigned(int32_t number) {
    PAL_UART_OutNumber_Signed(huart_terminal, number);
}

void PAL_DISPLAY_Debug(const char* format, ...) {
    va_list args;
    va_start(args, format);

    const char* p = format;
    char buffer[2] = { 0 };

    int precision = 0;
    while (*p != '\0') {
        if (*p == '%') {
            p++; // Move past the '%'
            if (*p == '.') {
                while (*++p != 'f') precision = precision * 10 + (*p - '0');
            }

            if (*p == '%') {
                HCL_UART_OutChar(huart_terminal, '%'); // Print literal '%'
            }
            else if (*p == 'c') {
                char value = va_arg(args, int);
                HCL_UART_OutChar(huart_terminal, value);
            }
            else if (*p == 'd') {
                int value = va_arg(args, int);
                PAL_UART_OutNumber_Signed(huart_terminal, value);
            }
            else if (*p == 'f') {
                double value = va_arg(args, double);
                if(precision == 0) precision = 6;
                PAL_UART_OutNumber_Double(huart_terminal, value, precision);
                precision = 0;
            }
            else if (*p == 's') {
                char* value = va_arg(args, char*);
                PAL_UART_OutString(huart_terminal, value);
            }
            else if (*p == 'x') {
                int value = va_arg(args, int);
                char buffer[9];
                sprintf(buffer, "%x", value);
                PAL_UART_OutString(huart_terminal, buffer);
            }
            else if (*p == 'X') {
                int value = va_arg(args, int);
                char buffer[9];
                sprintf(buffer, "%X", value);
                PAL_UART_OutString(huart_terminal, buffer);
            }            
            // Add more format specifiers as needed
        }
        else {
            HCL_UART_OutChar(huart_terminal, *p); // Print literal character
        }
        p++;
    }

    va_end(args);
}