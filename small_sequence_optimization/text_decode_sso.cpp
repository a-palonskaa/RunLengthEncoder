#include "text_decode_sso.h"

errors_t TextDecodeSSO(text_coder_t* coder) {

    assert(coder != NULL);
    assert(coder->file_input  != NULL);
    assert(coder->file_output != NULL);

    int encoding_length = fgetc(coder->file_input);
    int coping_symbol   = EOF;

    while (encoding_length != EOF) {
        int amount = 0;

        if (DeterminePrintMode(encoding_length, &amount) == COPY_SYMBOL) {
            coping_symbol = fgetc(coder->file_input);

            for (int i = 0; i < amount + 1; i++) {
                fputc(coping_symbol, coder->file_output);
            }

            coder->stats.initial_length += amount + 1;
            coder->stats.encoded_length++;
        }
        else {
            for (int i = 0; i < amount + 1; i++) {
                coping_symbol = fgetc(coder->file_input);
                fputc(coping_symbol, coder->file_output);
            }

            coder->stats.initial_length += amount + 1;
            coder->stats.encoded_length += amount + 1;
        }

        encoding_length = fgetc(coder->file_input);
        coder->stats.encoded_length++;
    }

    return NO_ERRORS;
}

compression_mode_t DeterminePrintMode(int number, int *amount) {
    *amount = number & LENGHT_MASK;

    // ХУЙНЯ ПЕРЕДЕЛЫВАЙ: why not array_copy_mask??????????
    return (number == *amount) ? COPY_SYMBOL : COPY_ARRAY;
}
