#include "application.h"


int run_application(int argc, char *argv[]) {

    if (argc == 1) {
        _print_help();
        return 0;
    }

    // parse the global command line arguments before parsing the command and its arguments
    argc = _parse_global_args(argc, argv);
    
    _parse_command(argc, argv);
    
    // if no command is found
    
    return _parse_application_args(argc, argv);;
}

void _parse_command(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "init") == 0) {
            init_config(argc, argv);
            return;
        }

        if (strcmp(argv[i], "prompt") == 0) {
            print_prompt();
            return;
        }

        if (strcmp(argv[i], "cleanup") == 0) {
            $memory_cleanup_segment();
            return;
        }

    }
    return;
}

int _parse_global_args(int argc, char *argv[]) {

    // parse the global command line arguments and remove them from the argument list
    // return the new number of arguments

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            $debug_mode = 1;
            $log_debug("parse_args", "Starting in debug mode");

            // remove the flag from the argument list
            memmove(&argv[i], &argv[i + 1], (argc - i) * sizeof(char *));
            argv[argc - 1] = NULL;

            argc -= 1;
            continue;
        }
    }

    __debug_args(argc, argv);

    return argc;
}

int _parse_application_args(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            _print_help();
            return 0;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            _print_version();
            return 0;
        } else {
            $log_debug("parse_args", "Unknown argument ");
            $log_debug("parse_args", argv[i]);
            return 1;
        }

    }

    return 0;
}

void _print_version(){
	printf("promptorium version : %s \n",PROMPTORIUM_VERSION);
    return;
}


void _print_help() {
    printf("Usage: promptorium <command> [options]\n");
    printf("Commands:\n");
    printf("  init             Load config into shared memory\n");
    printf("  prompt           Print the prompt\n");
    printf("  cleanup          Clean up the shared memory\n");
    printf("Options:\n");
    printf("  -h, --help       Print this help message\n");
    printf("  -v, --version    Print the version\n");
    printf("  -d, --debug      Start in debug mode\n");
    return ;
}


void __debug_args(int argc, char *argv[]) {
    $log_debug("debug_args", "Debugging args");
    printf("argc : %d\n", argc);
    $log_debug("debug_args", "argv : ");
    for (int i = 0; argv[i] != NULL; i++) {
        $log_debug("debug_args", argv[i]);
    }
    printf("\n");
    return;

}
