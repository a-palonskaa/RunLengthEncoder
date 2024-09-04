#ifndef DEFINE_CONSTANTS_H
#define DEFINE_CONSTANTS_H

#include <stdio.h>

// ХУЙНЯ ПЕРЕДЕЛЫВАЙ: это не константы main

#define STATICS_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1] //REVIEW -

const int MAX_LEN_NAME        = 100;

typedef enum {
    NO_ERRORS           = 0,
    FILE_OPEN_ERROR     = 1,
    COMMAND_INPUT_ERROR = 2,
    EMPTY_FILE_ERROR    = 3
} errors_t;

typedef struct {
    int initial_length;
    int encoded_length;
} compression_stats_t;

typedef struct {
    FILE *file_input;
    FILE *file_output;
    compression_stats_t stats;
} text_coder_t;

#endif /* DEFINE_CONSTANTS_H */
