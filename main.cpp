#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "text_encode_sso.h"
#include "text_decode_sso.h"
#include "arg_parser.h"
#include "text_decode_naive_implementation.h"
#include "text_encode_naive_implementation.h"

// TODO: where const
int main(int argc, const char* argv[]) {

    flags_t flag = {};

    // TODO: rename
    InitializeFlags(&flag);

    // TODO: no initialization
    FILE* file_input  = nullptr;
    FILE* file_output = nullptr;

    // TODO: whar error
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
//text_encode_t* encoder
    text_coder_t coder = {};

    coder.file_input  = file_input;
    coder.file_output = file_output;

    if (flag.mode == DECODE_SSO) {
        TextDecodeSSO(&coder);
    }
    else if (flag.mode == ENCODE_SSO) {
        TextEncodeSSO(&coder);
    }
    else if (flag.mode == ENCODE_NO) {
        TextEncodeNaiveImplementation(&coder);
    }
    else if (flag.mode == DECODE_NO) {
        TextDecodeNaiveImplementation(&coder);
    }
    // TODO: move to main
    printf("Compression coeff is %lf, length was %d, compressed length is %d \n",
          (float) coder.stats.initial_length / coder.stats.compressed_length,
           coder.stats.initial_length, coder.stats.compressed_length);

    fclose(file_input);
    fclose(file_output);

    // TODO: почему 1
    return NO_ERRORS;
}
