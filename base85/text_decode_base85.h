#ifndef TEXT_DECODE_BASE85_H
#define TEXT_DECODE_BASE85_H

#include <stdio.h>

#include "define_constants.h"

errors_t TextDecodeBase85(text_coder_t* coder);

unsigned int Power(unsigned int base, unsigned int power);

#endif /* TEXT_DECODE_BASE85_H */
