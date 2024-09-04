#include "arg_parser.h"

static void SetCodeMode     (flags_t* flags, const char* arg, int count);
static void SetCodeMethod   (flags_t* flags, const char* arg, int count);
static void SetInputFile    (flags_t* flags, const char* arg, int count);
static void SetOutputFile   (flags_t* flags, const char* arg, int count);
static void SetPrintHelpMode(flags_t* flags, const char* arg, int count);
static void PrintHelp();
static errors_t FindName(const char* name_begin_ptr, int i, char** argv[], int* argc, flags_t* flags);
static errors_t ValidateInput(flags_t* flags);

static const commands_t COMMANDS[] = {
    { "-e | -d",           "--encode | --decode ",
      "encode text by small sequence optimization | decode text by small sequence optimization",
      &SetCodeMode,      0},
    { "-sso | -ni | -b85", "--adove_rle | --naive | --base85",
      "use small sequence optimization | use naive optimization algorithm | use base85 algorithm",
      &SetCodeMethod,    0},
    { "-i",           "--input",
      "set input file",
      &SetInputFile,     1},
    { "-o",          "--output",
      "set output file",
      &SetOutputFile,    1},
    { "-h",                "--help",
      "print commands description",
      &SetPrintHelpMode, 0}
};

static const int COMMANDS_CNT = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

errors_t ArgParser(int argc, char* argv[], flags_t* flags) {
    while (--argc > 0) {
        int known_cmd = 0;
        argv++;

        for (int cmd_nr = 0; cmd_nr < COMMANDS_CNT; cmd_nr++) {
            const char* short_name_ptr = strstr(COMMANDS[cmd_nr].short_name, *argv);
            const char* long_name_ptr  = strstr(COMMANDS[cmd_nr].long_name, *argv);

            if (short_name_ptr != nullptr) {
                known_cmd++;
                FindName(short_name_ptr, cmd_nr, &argv, &argc, flags);
            }
            else if (long_name_ptr != nullptr) {
                known_cmd++;
                FindName(long_name_ptr, cmd_nr, &argv, &argc, flags);
            }
        }
        if(!known_cmd) {
            return COMMAND_INPUT_ERROR;
        }
    }
    return ValidateInput(flags);
}

// ХУЙНЯ ПЕРЕДЕЛЫВАЙ: это не count
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

static void SetPrintHelpMode(flags_t* flags, const char* arg, int count) {
    (void) flags;
    (void) arg;
    (void) count;

    PrintHelp();
}

void PrintHelp() {
    for (int i = 0; i < COMMANDS_CNT; i++) {
        printf("%-4s %-10s %-10s \n", COMMANDS[i].short_name, COMMANDS[i].long_name, COMMANDS[i].description);
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

static errors_t FindName(const char* name_begin_ptr, int i, char** argv[], int* argc, flags_t* flags) {

    int count = 0;

    const char* symbol = COMMANDS[i].short_name;

    while ((symbol = strchr(symbol, '|')) != NULL && symbol < name_begin_ptr) {
        count++;
        symbol++;
    }

    if (COMMANDS[i].argument) {
        (*argv)++;
        if (!((*argc)--)) {
            return COMMAND_INPUT_ERROR;
        }
        COMMANDS[i].change_flag(flags, **argv, count); // ХУЙНЯ ПЕРЕДЕЛЫВАЙ: наверное стоит сделать через 1 вызов этой функции а не 2
    }
    else {
        COMMANDS[i].change_flag(flags, nullptr, count);
    }

    return NO_ERRORS;
}

static errors_t ValidateInput(flags_t* flags) {
    if (flags->mode_commands_counter        > 1 ||
        flags->method_commands_counter      > 1 ||
        flags->input_file_commands_counter  > 1 ||
        flags->output_file_commands_counter > 1) {

        PrintHelp();
        return COMMAND_INPUT_ERROR;
    }
    return NO_ERRORS;
}