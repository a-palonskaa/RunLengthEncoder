#include <stdio.h>

#ifdef _DEBUG
#define STATICS_ASSERT(statement, text)  \
    do {                                 \
        if (!(statement)) {              \
            printf(text);                \
            return COMMAND_INPUT_ERROR;  \
        }                                \
    } while (0)
#else
#define STATICS_ASSERT(statement, text) ;
#endif


//как вызывать функции тольк она этапе компиляции в си
