#include "arg_parser.h"
// TODO: const для чара ALL!!!!!
static void SetEncodeMode(flags_t* flags, const char* arg);
static void SetDecodeMode(flags_t* flags, const char* arg);
static void SetInputFile(flags_t* flags, const char* arg);
static void SetOutputFile(flags_t* flags, const char* arg);
static void PrintHelp(flags_t* flags, const char* arg);

// TODO: static
static const commands_t commands[] = {{"-e", "--encode",          "encode given text", &SetEncodeMode, 0},
                                      {"-d", "--decode",          "decode given text", &SetDecodeMode, 0},
                                      {"-i",  "--input",             "set input file",  &SetInputFile, 1},
                                      {"-o", "--output",            "set output file", &SetOutputFile, 1},
                                      {"-h",   "--help", "print commands description",     &PrintHelp, 0}};
// TODO: static
static const int commands_length = sizeof(commands) / sizeof(commands[0]);

// TODO: const
errors_t ArgParser(int argc, const char* argv[], flags_t* flags) {

    while (--argc > 0) {
        argv++;

        for (int i = 0; i < commands_length; i++) {

            if (!strcmp(*argv, commands[i].short_name) ||
                !strcmp(*argv, commands[i].long_name)) {

                if (commands[i].argument) {
                    argv++;

                    if (!(argc--)) {
                        return COMMAND_INPUT_ERROR; // TODO: whar err
                    }

                    commands[i].change_flag(flags, *argv);
                }
                else {
                    commands[i].change_flag(flags, nullptr);
                }

                break;
            }
        }
    }
    return NO_ERRORS;
}

static void SetEncodeMode(flags_t* flags, const char* arg) {
    (void) arg;

    flags->mode = ENCODE;
    flags->mode_commands_counter++;
}

static void SetDecodeMode(flags_t* flags, const char* arg) {
    (void) arg;

    flags->mode = DECODE;
    flags->mode_commands_counter++;
}

static void SetInputFile(flags_t* flags, const char* arg) {
    flags->file_commands_counter++;
    flags->file_input_name = arg;
}

static void SetOutputFile(flags_t* flags, const char* arg) {
    flags->file_commands_counter++;
    flags->file_output_name = arg;
}

static void PrintHelp(flags_t* flags, const char* arg) {
    (void) flags;
    (void) arg;

    for (int i = 0; i < commands_length; i++) {
        printf("%-4s %-10s %-10s \n", commands[i].short_name, commands[i].long_name, commands[i].description);
    }
}

void InitializeFlags(flags_t* flag) {
    flag->mode = ENCODE;
    flag->file_commands_counter = 0;
    flag->mode_commands_counter   = 0;
    flag->file_input_name  = nullptr;
    flag->file_output_name = nullptr;
}

// NOTE: стандарт языка си++ запрещает неявные (int a = nullptr - ERROR) преобразования nullptr_t к неуказательным типам кроме bool

// char *pc = nullptr;     // верно
// int  *pi = nullptr;     // верно
// bool   b = nullptr;     // верно. b = false.
// int    i = nullptr;     // ошибка а с (void*)0 было бы верно
