#include "application.h"

static void _print_help() {
    printf("Usage: promptorium <command> [options]\n");
    printf("Commands:\n");
    printf("  init             Load (or reload) config into shared memory\n");
    printf("  prompt           Print the prompt\n");
    printf("  cleanup          Clean up the shared memory\n");
    printf("Options:\n");
    printf("  -h, --help       Print this help message\n");
    printf("  -v, --version    Print the version\n");
    printf("  -d[1-3], --debug-[1-3]      Start in debug mode\n");
    return;
}

static void _print_version() {
    printf("promptorium version : %s \n", PROMPTORIUM_VERSION);
    return;
}

static void _parse_command(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "init") == 0) {
            init_config(argc, argv);
            exit(0);
        }

        if (strcmp(argv[i], "prompt") == 0) {
            print_prompt();
            exit(0);
        }

        if (strcmp(argv[i], "cleanup") == 0) {
            cleanup();
            exit(0);
        }

        _print_help();
        $throw_error(__func__, "Command %s not found", argv[1]);
    }

    return;
}

static int _parse_global_args(int argc, char *argv[]) {

    // parse the global command line arguments and remove them from the argument list
    // return the new number of arguments

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0 ||
            strcmp(argv[i], "-d1") == 0 || strcmp(argv[i], "--debug-1") == 0) {
            $debug_level = DEBUG_LEVEL_MIN;
            $log_debug(DEBUG_LEVEL_MIN, "_parse_global_args", "Starting in debug mode");

            // remove the flag from the argument list
            memmove(&argv[i], &argv[i + 1], (argc - i) * sizeof(char *));
            argv[argc - 1] = NULL;

            argc -= 1;
            continue;
        }

        if (strcmp(argv[i], "-d2") == 0 || strcmp(argv[i], "--debug-2") == 0) {
            $debug_level = DEBUG_LEVEL_MEDIUM;
            $log_debug(DEBUG_LEVEL_MIN, "_parse_global_args", "Starting in medium debug mode");
        }

        if (strcmp(argv[i], "-d3") == 0 || strcmp(argv[i], "--debug-3") == 0) {
            $debug_level = DEBUG_LEVEL_MAX;
            $log_debug(DEBUG_LEVEL_MIN, "_parse_global_args", "Starting in deep debug mode");

            // remove the flag from the argument list
            memmove(&argv[i], &argv[i + 1], (argc - i) * sizeof(char *));
            argv[argc - 1] = NULL;

            argc -= 1;
            continue;
        }
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            _print_help();
            exit(0);
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            _print_version();
            exit(0);
        }
    }
    $debug_args(argc, argv);

    return argc;
}

int run_application(int argc, char *argv[]) {

    if (argc == 1) {
        printf("promptorium : no command provided\n");
        printf("Try 'promptorium --help' for more information\n");
        return 1;
    }

    // parse the global command line arguments before parsing the command and its arguments
    argc = _parse_global_args(argc, argv);

    _parse_command(argc, argv);

    $throw_error(__func__, "Command %s not found", argv[1]);

    return 0;
}
