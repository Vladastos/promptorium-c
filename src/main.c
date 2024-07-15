#include "main.h"
#include "modules/common/utils/definitions.h"

int parse_args(int argc, char *argv[]) {
    log_debug("parse_args", "Parsing arguments");
    if (argc == 1) {
        print_help();
        return 0;
    }
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }

        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            print_version("promtporium", PROMPTORIUM_VERSION);
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

        if (strcmp(argv[i], "--") == 0) {
            break;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    parse_args(argc, argv);
    return 0;
}
