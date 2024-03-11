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

    int precision = 0;
    while (*p != '\0') {
        if (*p == '%') {
            p++; // Move past the '%'
            if (*p == '.') {
                while (*++p != 'f') precision = precision * 10 + (*p - '0');
            }

            switch (*p) {
            case '%':
                HCL_UART_OutChar(huart_terminal, '%');
                break;
            case 'c': {
                char value;
                value = va_arg(args, int);
                HCL_UART_OutChar(huart_terminal, value);
                break;
            }
            case 'd': {
                int value;
                value = va_arg(args, int);
                PAL_UART_OutNumber_Signed(huart_terminal, value);
                break;
            }
            case 'f': {
                double value;
                value = va_arg(args, double);
                if (precision == 0)
                    precision = 6;
                PAL_UART_OutNumber_Double(huart_terminal, value, precision);
                precision = 0;
                break;
            }
            case 's': {
                char* value;
                value = va_arg(args, char*);
                PAL_UART_OutString(huart_terminal, value);
                break;
            }
            case 'x': {
                int value;
                char buffer[9];
                value = va_arg(args, int);
                sprintf(buffer, "%x", value);
                PAL_UART_OutString(huart_terminal, buffer);
                break;
            }
            case 'X': {
                int value;
                char buffer[9];
                value = va_arg(args, int);
                sprintf(buffer, "%X", value);
                PAL_UART_OutString(huart_terminal, buffer);
                break;
            }
            default:
                break;
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