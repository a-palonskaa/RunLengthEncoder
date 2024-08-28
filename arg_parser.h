#ifndef ARG_PARSER_H
#define ARG_PARSER_H
// NOTE: include guard
#include <stdio.h>
#include <string.h>

#include "define_constants.h"

// TODO: typedef
typedef enum {
    DECODE = 0,
    ENCODE = 1
} operation_mode_t;

typedef struct {
    operation_mode_t mode;
    int file_commands_counter;   // TODO: rename
    int mode_commands_counter;   // TODO: what, rename
    const char* file_input_name; // TODO: NAME file + const
    const char* file_output_name;
} flags_t;

typedef void (*change_flag_t) (flags_t* flags, const char* arg); // TODO: const

typedef struct {
    char short_name[MAX_LEN_NAME];
    char long_name[MAX_LEN_NAME];
    char description[MAX_LEN_NAME];
    change_flag_t change_flag;
    bool argument; // TODO: rename
} commands_t;

errors_t ArgParser(int argc, const char* argv[], flags_t* flags);
void InitializeFlags(flags_t* flag); // TODO: rename

#endif /* ARG_PARSER_H */ // TODO: всратый формат комментария

// TODO: объектники не в билде
