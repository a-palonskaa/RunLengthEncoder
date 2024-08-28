#include "text_decode_naive_implementation.h"

errors_t TextDecodeNaiveImplementation(text_coder_t* coder) {

    assert(coder != nullptr);
    assert(coder->file_input != nullptr);
    assert(coder->file_output != nullptr);

    int amount = EOF;
    int coping_symbol = EOF;

    while ((amount = fgetc(coder->file_input))!= EOF && (coping_symbol = fgetc(coder->file_input)) != EOF) {
        coder->stats.compressed_length += 2;
        for (int i = 0; i < amount + 1; i++) {
            fputc(coping_symbol, coder->file_output);
            coder->stats.initial_length++;
        }
    }

    return NO_ERRORS;
}
