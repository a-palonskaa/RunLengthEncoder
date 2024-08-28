#ifndef TEXT_ENCODE_H
#define TEXT_ENCODE_H

#include <stdio.h>
#include <assert.h>

#include "define_constants.h"

errors_t TextEncode(FILE *file_input, FILE *file_output, compression_stats_t* coder);
errors_t TextEncode(text_encode_t* encoder);

#endif /* TEXT_ENCODE_H */
// ХУЙНЯ ПЕРЕДЕЛЫВАЙ: добавить первую версию в этот файл
