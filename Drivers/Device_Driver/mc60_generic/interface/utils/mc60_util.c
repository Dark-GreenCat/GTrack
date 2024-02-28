#include "mc60_util.h"
#include <string.h>

void MC60_ITF_UTIL_ResultProcess_Init(char* result, mc60_result_process_t* mc60_result_process) {
    mc60_result_process->result = result;
    mc60_result_process->result[0] = '\0';

    mc60_result_process->termCount = 0;
    mc60_result_process->curTermIndex = 0;
    mc60_result_process->isResponse = false;
    mc60_result_process->isCommandTerm = false;
}

int32_t MC60_ITF_UTIL_ResultToNum(const char* str) {
    int32_t number = 0;
    bool isNegative = (*str == '-');
    if (isNegative) ++str;

    while (*str >= '0' && *str <= '9') {
        number = number * 10 + (*str - '0');
        ++str;
    }

    if (isNegative) number = -number;

    return number;
}

char* MC60_ITF_UTIL_ResultToString(char* destination, const char* str) {
    char* ret = destination;

    if (*str != '+') str++;
    for (; *str != '"' && *str != '\0'; str++) {
        *destination++ = *str;
    }
    *destination = '\0';

    return ret;
}

bool MC60_ITF_UTIL_GetResult(mc60_result_process_t* process, char c) {
    if (c == '+') {
        process->isResponse = process->isCommandTerm = true;
    }
    if (!process->isResponse)
        return false;
    if (c == '\r' || c == '\n')
        process->isResponse = false;

    switch (c) {
        case ',':
        case '\r':
        case '\n':
        case ':':
            process->result[process->curTermIndex] = '\0';
            process->curTermIndex = 0;
            process->termCount++;
            process->isCommandTerm = false;
            return true;

        case ' ':
            if (process->isCommandTerm)
                process->result[process->curTermIndex++] = c;
            break;

        case '+':
            process->result[0] = '+';
            process->result[1] = '\0';
            process->curTermIndex = 1;
            break;

        default:
            process->result[process->curTermIndex++] = c;
            break;
    }

    return false;
}