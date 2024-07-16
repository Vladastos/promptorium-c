#include "main.h"
#include "modules/common/utils/definitions.h"

int parse_args(int argc, char *argv[]) {

    if (argc == 1) {
        print_help();
        return 0;
    }
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "debug") == 0) {

            debug_mode = 1;

            log_debug("parse_args", "Starting in debug mode");
            continue;
        }

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }

        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            print_version("promptorium", PROMPTORIUM_VERSION);
            return 0;
        }

        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--init") == 0) {
            init_config();
            return 0;
        }

        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cleanup") == 0) {
            cleanup_shared_memory_segment();
            return 0;
        }

        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--prompt") == 0) {
            print_prompt();
            return 0;
        }

        if (strcmp(argv[i], "--") == 0) {
            break;
        }
    }
    log_debug("parse_args", "Invalid arguments");
    print_help();
    return 1;
}
int main(int argc, char *argv[]) { return parse_args(argc, argv); }
