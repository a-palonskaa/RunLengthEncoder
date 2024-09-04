#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "arg_parser.h"
#include "text_encode_sso.h"
#include "text_decode_sso.h"
#include "text_decode_naive_implementation.h"
#include "text_encode_naive_implementation.h"
#include "text_encode_base85.h"
#include "text_decode_base85.h"

int main(int argc, char* argv[]) {

    flags_t flag = {};

    InitializeFlags(&flag);

    FILE* file_input  = nullptr;
    FILE* file_output = nullptr;

    if (ArgParser(argc, argv, &flag) == COMMAND_INPUT_ERROR) {
        return COMMAND_INPUT_ERROR;
    }

    if ((file_input = fopen(flag.file_input_name, "r")) == nullptr) {
        perror("INPUT FILE OPENING ERROR");
        return FILE_OPEN_ERROR;
    }

    if ((file_output = fopen(flag.file_output_name, "w")) == nullptr) {
        perror("OUTPUT FILE OPENING ERROR");
        return FILE_OPEN_ERROR;
    }

    text_coder_t coder = {};

    coder.file_input  = file_input;
    coder.file_output = file_output;

    if (flag.mode == DECODE) {

        if (flag.method == SSO_METHOD) {
            TextDecodeSSO(&coder);
        }
        else if (flag.method == NI_METHOD) {
            TextDecodeNaiveImplementation(&coder);
        }
        else if (flag.method == B85_METHOD) {
            TextDecodeBase85(&coder);
        }
    }
    else if (flag.mode == ENCODE) {

        if (flag.method == SSO_METHOD) {
            TextEncodeSSO(&coder);
        }
        else if (flag.method == NI_METHOD) {
            TextEncodeNaiveImplementation(&coder);
        }
        else if (flag.method == B85_METHOD) {
            TextEncodeBase85(&coder);
        }
    }

    printf("Compression coefficient is %.2lf, length was %d, encoded length is %d \n",
          (float) coder.stats.initial_length / coder.stats.encoded_length,
           coder.stats.initial_length, coder.stats.encoded_length);

    fclose(file_input);
    fclose(file_output);

    return NO_ERRORS;
}
