#include "arg_parser.h"

static void SetCodeMode   (flags_t* flags, const char* arg, int count);
static void SetCodeMethod (flags_t* flags, const char* arg, int count);
static void SetInputFile  (flags_t* flags, const char* arg, int count);
static void SetOutputFile (flags_t* flags, const char* arg, int count);
static void PrintHelp     (flags_t* flags, const char* arg, int count);
static errors_t FindName(const char* name_begin_ptr, int i, const char* argv[], int* argc, flags_t* flags);

static const commands_t commands[] = {
    { "-e | -d",           "--encode | --decode ",
      "encode text by small sequence optimization | decode text by small sequence optimization",
      &SetCodeMode,    0},
    { "-sso | -ni | -b85", "--adove_rle | --naive | --base85",
      "use small sequence optimization | use naive optimization algorithm | use base85 algorithm",
      &SetCodeMethod, 0},
    { "-i",           "--input",
      "set input file",
      &SetInputFile,   1},
    { "-o",          "--output",
      "set output file",
      &SetOutputFile,  1},
    { "-h",                "--help",
      "print commands description",
      &PrintHelp,      0}
};

static const int commands_length = sizeof(commands) / sizeof(commands[0]);


errors_t ArgParser(int argc, const char* argv[], flags_t* flags) {
    while (--argc > 0) {
        argv++;

        for (int i = 0; i < commands_length; i++) {
            const char* short_name_ptr = strstr(commands[i].short_name, *argv);
            const char* long_name_ptr = strstr(commands[i].long_name, *argv);

            if (short_name_ptr != nullptr) {
                FindName(short_name_ptr, i, argv, &argc, flags);
            }
            else if(long_name_ptr != nullptr) {
                FindName(long_name_ptr, i, argv, &argc, flags);
            }
        }
    }

    if (flags->mode_commands_counter   > 1 ||
        flags->method_commands_counter > 1 ||
        flags->input_file_commands_counter > 1 ||
        flags->output_file_commands_counter > 1) {
        return COMMAND_INPUT_ERROR;
    }

    return NO_ERRORS;
}

static void SetCodeMode(flags_t* flags, const char* arg, int count) {
    (void) arg;

    if (count == 0) {
        flags->mode = ENCODE;
    }
    else if (count == 1) {
        flags->mode = DECODE;
    }

    flags->mode_commands_counter++;
}

static void SetCodeMethod(flags_t* flags, const char* arg, int count) {
    (void) arg;

    if (count == 0) {
        flags->method = SSO_METHOD;
    }
    else if (count == 1) {
        flags->method = NI_METHOD;
    }
    else if (count == 2) {
        flags->method = B85_METHOD;
    }

    flags->method_commands_counter++;
}

static void SetInputFile(flags_t* flags, const char* arg, int count) {
    (void) count;

    flags->input_file_commands_counter++;
    flags->file_input_name = arg;
}

static void SetOutputFile(flags_t* flags, const char* arg, int count) {
    (void) count;

    flags->output_file_commands_counter++;
    flags->file_output_name = arg;
}

static void PrintHelp(flags_t* flags, const char* arg, int count) {
    (void) flags;
    (void) arg;
    (void) count;

    for (int i = 0; i < commands_length; i++) {
        printf("%-4s %-10s %-10s \n", commands[i].short_name, commands[i].long_name, commands[i].description);
    }
}

void InitializeFlags(flags_t* flag) {
    flag->mode   = ENCODE;
    flag->method = NI_METHOD;

    flag->output_file_commands_counter = 0;
    flag->input_file_commands_counter  = 0;
    flag->method_commands_counter      = 0;
    flag->mode_commands_counter        = 0;

    flag->file_input_name  = nullptr;
    flag->file_output_name = nullptr;
}

static errors_t FindName(const char* name_begin_ptr, int i, const char* argv[], int* argc, flags_t* flags) {

        int count = 0;

        const char* symbol = commands[i].short_name;

        while ((symbol = strchr(symbol, '|')) != NULL && symbol < name_begin_ptr) {
            count++;
            symbol++;
        }

        if (commands[i].argument) {
            argv++;

            if (!(argc--)) {
                return COMMAND_INPUT_ERROR;
            }

            commands[i].change_flag(flags, *argv, count);
        }
        else {
            commands[i].change_flag(flags, nullptr, count);
        }
    return NO_ERRORS;
}
