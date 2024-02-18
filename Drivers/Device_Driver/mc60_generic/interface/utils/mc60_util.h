#ifndef __MC60_UTIL_H
#define __MC60_UTIL_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char* result;

    uint8_t termCount;
    uint32_t curTermIndex;
    bool isResponse, isCommandTerm;
} mc60_result_process_t;

void MC60_ITF_UTIL_ResultProcess_Init(char* result, mc60_result_process_t* mc60_result_process);
int32_t MC60_ITF_UTIL_ResultToNum(const char* str);
char* MC60_ITF_UTIL_ResultToString(char* destination, const char* str);

/**
 * Parses the result received from the MC60 module.
 *
 * The result should be in the format: +<COMMAND>: <number/string>,<number/string>,...
 * Before using this function, make sure to call MC60_ITF_UTIL_ResultProcess_Init() to initialize the result processing.
 *
 * The result format can be one of the following:
 *   - If the first character is '+': The result is a command response, string.
 *   - If the first character is '"': The result is a string.
 *   - Otherwise: The result is a number.
 *
 * The function updates the provided `process` structure accordingly.
 *
 * @param process Pointer to the mc60_result_process_t structure for result processing.
 * @param c The character to process.
 * @return true if a result term is complete and ready for processing, false otherwise.
 */
bool MC60_ITF_UTIL_GetResult(mc60_result_process_t* process, char c);

#endif // __MC60_UTIL_H