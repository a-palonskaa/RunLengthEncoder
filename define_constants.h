#ifndef DEFINE_CONSTANTS_H
#define DEFINE_CONSTANTS_H

#include <stdio.h>

const int MAX_LEN_SYMBOLS_SSO  = 127;
const int MAX_LEN_NAME = 100;
const int MAX_LEN_SYMBOLS_NO = 255;

// 0b0111'1111
// 0x   7    F
const int LENGHT_MASK = 0x7F;

// 0b1000'0000
// 0x   8    0
const int ARRAY_COPY_MASK = 0x80;

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
