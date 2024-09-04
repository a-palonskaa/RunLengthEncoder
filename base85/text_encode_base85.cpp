#include <assert.h>

#include "text_encode_base85.h"
#include "base85_constants.h"

static int FourBytesToInt(const int* bytes4);
static int IntToFiveBytes(int bytes4, int* bytes5);

errors_t TextEncodeBase85(text_coder_t* coder) {
    assert(coder != nullptr);
    assert(coder->stats.encoded_length == 0);
    assert(coder->stats.initial_length == 0);

    STATICS_ASSERT(BYTES5_CNT == 5, WRONG_AMOUNT_OF_BYTES_FOR_BASE85);
    STATICS_ASSERT(BYTES4_CNT == 4, WRONG_AMOUNT_OF_BYTES_FOR_BASE85);

    bool flag = true;

    while (flag) {
        int bytes5[BYTES5_CNT] = {};
        int bytes4[BYTES4_CNT] = {};
        int i = 0;

        while ((bytes4[i] = getc(coder->file_input)) != EOF && i < BYTES4_CNT - 1) {
            i++;
        }

        int bytes_amount = i;
        coder->stats.initial_length += bytes_amount + 1;

        if (bytes4[i] == EOF) {
            for (int j = bytes_amount; j < BYTES4_CNT - 1; j++) {
                bytes4[j] = 0;
            }

            coder->stats.initial_length--;
            bytes_amount--;
            flag = false;
        }

        int bytes4_to_int = FourBytesToInt(bytes4);
        int null_symbol_amount = IntToFiveBytes(bytes4_to_int, bytes5);

        if (null_symbol_amount == BYTES5_CNT) {
            fputc(Z_ASCII_CODE, coder->file_output);

            coder->stats.encoded_length++;
        }
        else {
            for (int j = 0; j < bytes_amount + 2; j++) {
                bytes5[j] += 33;

                fputc(bytes5[j], coder->file_output);

                coder->stats.encoded_length++;
            }
        }
    }
    return NO_ERRORS;
}

static int FourBytesToInt(const int* bytes4) {
    assert(bytes4 != nullptr);

    return bytes4[3] | bytes4[2]<<8 | bytes4[1]<<16 | bytes4[0]<<24;
}

static int IntToFiveBytes(int bytes4, int* bytes5) { // ХУЙНЯ ПЕРЕДЕЛЫВАЙ: неочевидное return value
    assert(bytes5 != nullptr);

    int null_symbol_amount = 0;

    for (int i = 0; i < BYTES5_CNT; i++) {
        bytes5[BYTES5_CNT - 1 -i] = bytes4 % 85;
        bytes4 = bytes4 / 85;

        if (!bytes5[i]) {
            null_symbol_amount++;
        }
    }

    return null_symbol_amount;
}
