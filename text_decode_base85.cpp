#include "text_decode_base85.h"

static int FiveBytesToInt(int* bytes5);
void IntToFourBytes(int bytes5_to_int, int* bytes4);
int Power(int base, int power);

const int char_masks[] = {0xFF000000, 0xFF0000, 0xFF00, 0xFF};

int TextDecodeBase85(text_coder_t* coder) {
    assert(coder != nullptr);
    assert(coder->stats.encoded_length == 0);
    assert(coder->stats.initial_length == 0);

    bool flag = true;

    while (flag) {
        int bytes5[5] = {};
        int bytes4[4] = {};
        int i = 0;

        bytes5[0] = getc(coder->file_input);

        while (bytes5[i] != EOF && i < 4 && bytes5[i] != 122) {
            i++;
            bytes5[i] = getc(coder->file_input);
        }

        int bytes_amount = i;

        if (bytes5[i] == 122) {
            for (int i = 0; i < 5; i++) {
                fputc(0, coder->file_output);
            }
        }
        else {
            if (bytes5[i] == EOF) {
                for (int i = bytes_amount ; i < 5; i++) {
                    printf("NULL %d  ", i);
                    bytes5[i] = 117;
                }

                bytes_amount--;
                flag = false;
            }

            int bytes5_to_int = FiveBytesToInt(bytes5);
            printf("int = %d \n", bytes5_to_int);
            IntToFourBytes(bytes5_to_int, bytes4);


            for (int i = 0; i < bytes_amount; i++) {
                fputc(bytes4[i], coder->file_output);
            }
        }
    }
    return 0;
}

int FiveBytesToInt(int* bytes5) {
    int value = 0;

    for (int i = 0; i < 5; i++) {
        printf("bytes[%d] = %d \n", i, bytes5[i]);
        printf("%d \n", (bytes5[i] - 33) * Power(85, (4 - i)));
        value += (bytes5[i] - 33) * Power(85, (4 - i));
    }

    return value;
}

void IntToFourBytes(int bytes5_to_int, int* bytes4) {
    for (int i = 0; i < 4; i++) {
        bytes4[i] = (bytes5_to_int & char_masks[i]) >> (8 * (3 - i));
    }
}

int Power(int base, int power) {
    int result = 1;
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}
