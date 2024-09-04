#include <assert.h>

#include "text_decode_base85.h"
#include "base85_constants.h"

#define BYTES4_MASK(i) ((3 - (i)) << 3)

static unsigned int FiveBytesToInt(unsigned int* bytes5);
static void IntToFourBytes(unsigned int bytes5_to_int, unsigned int* bytes4);

const unsigned int CHAR_MASKS[] = {
    0xFF000000,
    0x00FF0000,
    0x0000FF00,
    0x000000FF
};

errors_t TextDecodeBase85(text_coder_t* coder) {
    assert(coder != nullptr);
    assert(coder->stats.encoded_length == 0);
    assert(coder->stats.initial_length == 0);

    STATICS_ASSERT(BYTES5_CNT == 5, WRONG_AMOUNT_OF_BYTES_FOR_BASE85);
    STATICS_ASSERT(BYTES4_CNT == 4, WRONG_AMOUNT_OF_BYTES_FOR_BASE85);

    bool flag = true;

    while (flag) {
        unsigned int bytes5[BYTES5_CNT] = {}; // ХУЙНЯ ПЕРЕДЕЛЫВАЙ: подумать почему здесь должен unsigned  в принципе
        unsigned int bytes4[BYTES4_CNT] = {};
        unsigned int i = 0;

        while ((bytes5[i] = getc(coder->file_input)) != EOF &&
                i < BYTES5_CNT - 1 &&
                bytes5[i] != Z_ASCII_CODE) {
            i++;
        }

        unsigned int bytes_amount = i;

        coder->stats.encoded_length += bytes_amount + 1;

        if (bytes5[i] == Z_ASCII_CODE) {
            for (unsigned int j = 0; j < BYTES5_CNT; j++) {
                fputc(0, coder->file_output);
            }

            coder->stats.initial_length += BYTES5_CNT;
        }
        else {
            if (bytes5[i] == EOF) {
                for (unsigned int j = bytes_amount ; j < BYTES5_CNT; j++) {
                    bytes5[j] = U_ASCII_CODE;
                }

                coder->stats.encoded_length--;
                bytes_amount--;
                flag = false;
            }

            unsigned int bytes5_to_int = FiveBytesToInt(bytes5);
            IntToFourBytes(bytes5_to_int, bytes4);

            for (unsigned int j = 0; j < bytes_amount; j++) {
                fputc(bytes4[j], coder->file_output);
            }

            coder->stats.initial_length += bytes_amount;
        }
    }
    return NO_ERRORS;
}

unsigned int FiveBytesToInt(unsigned int* bytes5) {
    assert(bytes5 != nullptr);

    unsigned int value = 0;
    unsigned int power85_bytes5_cnt = Power(85, 4);

    for (unsigned int i = 0; i < BYTES5_CNT; i++) {
        value += (bytes5[i] - 33) * power85_bytes5_cnt;
        power85_bytes5_cnt /= 85;

    }
    return value;
}

static void IntToFourBytes(unsigned int bytes5_to_int, unsigned int* bytes4) {
    assert(bytes4 != nullptr);

    for (unsigned int i = 0; i < BYTES4_CNT; i++) {
        bytes4[i] = (bytes5_to_int & CHAR_MASKS[i]) >> BYTES4_MASK(i); //ХУЙНЯ ПЕРЕДЕЛЫВАЙ -
    }
}

unsigned int Power(unsigned int base, unsigned int power) {
    unsigned int result = 1;

    for (unsigned int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}
