#include "text_decode.h"

// TODO: структура decoder
//compression_stats
errors_t TextDecode(text_coder_t* coder) {

    assert(file_input != NULL);
    assert(file_input != NULL);

    int encoding_length = fgetc(file_input);
    int coping_symbol   = EOF;

    while (encoding_length != EOF) {
        int amount = 0;

        if (DeterminePrintMode(encoding_length, &amount) == COPY_SYMBOL) {
            coping_symbol = fgetc(file_input);

            for (int i = 0; i < amount + 1; i++) {
                fputc(coping_symbol, file_output);
            }

            coder->initial_length += amount + 1; // TODO: вынести из цикла
            coder->compressed_length++;
        }
        else {
            for (int i = 0; i < amount + 1; i++) {
                coping_symbol = fgetc(file_input);
                fputc(coping_symbol, file_output);
            }

            coder->initial_length    += amount + 1; // TODO: вынести из цикла
            coder->compressed_length += amount + 1; // TODO: вынести из цикла
        }

        encoding_length = fgetc(file_input);
        coder->compressed_length++;
    }

    return NO_ERRORS;
}

compression_mode_t DeterminePrintMode(int number, int *amount) {
    *amount = number & LENGHT_MASK;

    return (number == (number & LENGHT_MASK)) ? COPY_SYMBOL : COPY_ARRAY;
    // TODO: через тернарный оператор

}
