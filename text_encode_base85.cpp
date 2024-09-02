#include "text_encode_base85.h"

static int FourBytesToInt(int* bytes4);
static int IntToFiveBytes(int bytes4, int* bytes5);

int TextEncodeBase85(text_coder_t* coder) {
    assert(coder != nullptr);
    assert(coder->stats.encoded_length == 0);
    assert(coder->stats.initial_length == 0);

    bool flag = true;

    while (flag) {
        int bytes5[5] = {};
        int bytes4[4] = {};
        int i = 0;

        coder->stats.initial_length++;

        while ((bytes4[i] = getc(coder->file_input)) != EOF && i < 3) {
            i++;
            coder->stats.initial_length++;
        }

        int bytes_amount = i;

        if (bytes4[i] == EOF) {
            coder->stats.initial_length--;

            for (int j = bytes_amount; j < 3; j++) {
                bytes4[j] = 0;
            }

            bytes_amount--;
            flag = false;
        }

        int bytes4_to_int = FourBytesToInt(bytes4);

        int null_symbol_amount = IntToFiveBytes(bytes4_to_int, bytes5);

        if (null_symbol_amount == 5) {
            fputc('z', coder->file_output);

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
    return 0;
}

static int FourBytesToInt(int* bytes4) {
    return bytes4[3] | bytes4[2]<<8 | bytes4[1]<<16 | bytes4[0]<<24;
}

static int IntToFiveBytes(int bytes4, int* bytes5) {
    assert(bytes5 != nullptr);

    int null_symbol_amount = 0;

    for (int i = 0; i < 5; i++) {
        bytes5[4-i] = bytes4 % 85;
        bytes4 = bytes4 / 85;

        if (!bytes5[i]) {
            null_symbol_amount++;
        }
    }

    return null_symbol_amount;
}
