#ifndef TEXT_DECODE
#define TEXT_DECODE

#include <stdio.h>
#include <assert.h>

#include "define_constants.h"

typedef enum {
    COPY_SYMBOL = 0,
    COPY_ARRAY  = 1
} compression_mode_t; // TODO: rename, no print compression

errors_t TextDecode(text_coder_t* coder);
compression_mode_t DeterminePrintMode(int number, int *amount);

#endif /* TEXT_DECODE */
