#include "text_encode_sso.h"

static int ArrayCopy(text_coder_t* coder, int symbol, int* symbol_amount, int unrepeatable_symbols[]);


errors_t TextEncodeSSO(text_coder_t* coder) {

    assert(coder->file_input != nullptr);
    assert(coder->file_output != nullptr);

    int symbol      = fgetc(coder->file_input);
    int next_symbol = fgetc(coder->file_input);

    if (symbol == EOF) {
        return EMPTY_FILE_ERROR;
    }

    while (symbol != EOF) {
        int symbol_amount = 0;

        while (next_symbol == symbol &&
               next_symbol != EOF &&
               symbol_amount < MAX_LEN_SYMBOLS_SSO) {
            symbol_amount++;
            next_symbol = fgetc(coder->file_input);
            coder->stats.initial_length++;
        }

        if (symbol_amount == 0) {
            int unrepeatable_symbols[MAX_LEN_SYMBOLS_SSO] = {};
            unrepeatable_symbols[0] = symbol;

            symbol = ArrayCopy(coder, next_symbol, &symbol_amount, unrepeatable_symbols);
            next_symbol = symbol;

            fputc(symbol_amount | ARRAY_COPY_MASK, coder->file_output);

            for (int i = 0; i < symbol_amount + 1; i++) {
                fputc(unrepeatable_symbols[i], coder->file_output);
            }

            coder->stats.compressed_length += symbol_amount + 2;
        }
        else {
            fputc(symbol_amount, coder->file_output);
            fputc(symbol, coder->file_output);

            coder->stats.compressed_length += 2;

            symbol = next_symbol;
            next_symbol = fgetc(coder->file_input);

            coder->stats.initial_length++;
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
int ArrayCopy(text_coder_t* coder, int symbol, int* symbol_amount, int unrepeatable_symbols[]) { //
    int next_symbol = EOF;

    while (true) {
        next_symbol = getc(coder->file_input);
        (coder->stats.initial_length)++;

        if (symbol == next_symbol || symbol == EOF) {
            break;
        }

        unrepeatable_symbols[++(*symbol_amount)] = *symbol_amount;
        symbol = next_symbol;
    }

    return next_symbol;
}
