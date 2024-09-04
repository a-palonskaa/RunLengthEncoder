#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stdio.h>
#include <string.h>

#include "define_constants.h"

typedef enum {
    DECODE     = 0,
    ENCODE     = 1
} operation_mode_t;

typedef enum {
    SSO_METHOD = 0,
    NI_METHOD  = 1,
    B85_METHOD = 2
} operation_method_t;

typedef struct {
    operation_mode_t mode;
    operation_method_t method;
    int input_file_commands_counter;
    int output_file_commands_counter;
    int mode_commands_counter;
    int method_commands_counter;
    const char* file_input_name;
    const char* file_output_name;
} flags_t;

typedef void (*change_flag_t) (flags_t* flags, const char* arg, int count);

typedef struct {
    char short_name[MAX_LEN_NAME];
    char long_name[MAX_LEN_NAME];
    char description[MAX_LEN_NAME];
    change_flag_t change_flag;
    bool argument;
} commands_t;

errors_t ArgParser(int argc, char* argv[], flags_t* flags);
void InitializeFlags(flags_t* flag);

#endif /* ARG_PARSER_H */
