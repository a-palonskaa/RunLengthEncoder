#ifndef TEXT_DECODE_SSO_H
#define TEXT_DECODE_SSO_H

#include <stdio.h>
#include <assert.h>

#include "define_constants.h"

typedef enum {
    COPY_SYMBOL = 0,
    COPY_ARRAY  = 1
} compression_mode_t;

errors_t TextDecodeSSO(text_coder_t* coder);
compression_mode_t DeterminePrintMode(int number, int *amount);

#endif /* TEXT_DECODE_SSO_H */
