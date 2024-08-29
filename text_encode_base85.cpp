#include "text_encode_base85.h"

static int FourBytesToInt(int* bytes4);
static int IntToFiveBytes(int bytes4, int* bytes5);

int TextEncodeBase85(FILE* file_in,FILE* file_out) {
    bool flag = 1;

    while (flag) {
        int bytes5[5] = {};
        int bytes4[4] = {};
        bytes4[0] = getc(file_in);
        int i = 0;

        while (bytes4[i] != EOF && i < 3) {
            i++;
            bytes4[i] = getc(file_in);
        }

        int bytes_amount = i;
        printf("bytes_amount = %d \n", i);

        if (bytes4[i] == EOF) { //обработка когда меньше 4
            for (int i = bytes_amount; i < 3; i++) {
                bytes4[i] = 0;
            }
            bytes_amount--;
            flag = 0;
        }
        //обработать EOF и i
        int bytes4_to_int = FourBytesToInt(bytes4);
        int null_symbol_amount = IntToFiveBytes(bytes4_to_int, bytes5);

        if (null_symbol_amount == 5) {
            fputc('z', file_out);
        }
        else {
            for (int i = 0; i < bytes_amount + 2; i++) {
                printf("i = %d \n", i);
                bytes5[i] += 33;
                fputc(bytes5[i], file_out);
            }
        }
    }
    return 0;
}

static int FourBytesToInt(int* bytes4) {
    return bytes4[3] | bytes4[2]<<8 | bytes4[1]<<16 | bytes4[0]<<24;
}

static int IntToFiveBytes(int bytes4, int* bytes5) {
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
