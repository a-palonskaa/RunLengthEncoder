#include "text_encode_naive_implementation.h"

errors_t TextEncodeNaiveImplementation(text_coder_t* coder) {

    assert(coder != nullptr);
    assert(coder->file_input != nullptr);
    assert(coder->file_output != nullptr);

    int symbol = fgetc(coder->file_input);
    int next_symbol = EOF;

    if (symbol == EOF) {
        return EMPTY_FILE_ERROR;
    }

    while (symbol != EOF) {
        int symbol_amount = 0;

        while ((next_symbol = fgetc(coder->file_input)) == symbol &&
                next_symbol != EOF &&
                symbol_amount < MAX_LEN_SYMBOLS_NO) {
            symbol_amount++;
            coder->stats.initial_length++;
        }

        coder->stats.initial_length++;

        fputc(symbol_amount, coder->file_output);
        fputc(symbol, coder->file_output);

        coder->stats.encoded_length += 2;

        symbol = next_symbol;
    }
    return NO_ERRORS;
}
// NOTE: /bit_optimization
// NaiveImplementation
// sso
// small sequaence optimization
