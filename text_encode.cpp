#include "text_encode.h"

static int ArrayCopy(FILE *input, int symbol, int* symbol_amount, int unrepeatable_symbols[], compression_stats_t* coder);


errors_t TextEncode(text_encode_t* encoder) {

    assert(file_input != NULL);
    assert(file_input != NULL);

    int symbol      = fgetc(file_input);
    int next_symbol = fgetc(file_input);

    if (symbol == EOF) {
        return EMPTY_FILE_ERROR;
    }

    while (symbol != EOF) {
        int symbol_amount = 0;

        while (next_symbol == symbol &&
               next_symbol != EOF &&
               symbol_amount < MAX_LEN_SYMBOLS) {
            symbol_amount++;
            next_symbol = fgetc(file_input);
            coder->initial_length++;
        }

        if (symbol_amount == 0) {
            int unrepeatable_symbols[MAX_LEN_SYMBOLS] = {};
            unrepeatable_symbols[0] = symbol;

            symbol = ArrayCopy(file_input, next_symbol, &symbol_amount, unrepeatable_symbols, coder);
            next_symbol = symbol;

            fputc(symbol_amount | ARRAY_COPY_MASK, file_output);

            for (int i = 0; i < symbol_amount + 1; i++) {
                fputc(unrepeatable_symbols[i], file_output);
            }

            coder->compressed_length += symbol_amount + 2;
        }
        else {
            fputc(symbol_amount, file_output);
            fputc(symbol, file_output);

            coder->compressed_length += 2;

            symbol = next_symbol;
            next_symbol = fgetc(file_input);

            coder->initial_length++;
        }

        if (next_symbol == EOF) {
            break;
        }
    }

    // TODO: перенести в main
    // NOTE : достаточно изменить только один тип, т.к. все приводиться к сильнейшему типу в выражении

    return NO_ERRORS;
}

// TODO: нахуя копировать структуру и держать там указателиб хранитьь переменную в структуре и передавать указатель на структуру
int ArrayCopy(FILE *input, int symbol, int* symbol_amount, int unrepeatable_symbols[], compression_stats_t* coder) { //
    int next_symbol = EOF;

    while (true) {
        next_symbol = getc(input);
        (coder->initial_length)++;

        if (symbol == next_symbol || symbol == EOF) {
            break;
        }

        unrepeatable_symbols[++(*symbol_amount)] = *symbol_amount;
        symbol = next_symbol;
    }

    return next_symbol;
}
