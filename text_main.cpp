#include <stdio.h>

#include "text_encode_base85.h"
#include "text_decode_base85.h"
#include "define_constants.h"

int main() {
    FILE* in = fopen("in.txt", "r");
    FILE* out = fopen("out.txt", "w");
    TextEncodeBase85(in, out);
    printf("hi");
    fclose(in);
    fclose(out);
    return 0;
}
