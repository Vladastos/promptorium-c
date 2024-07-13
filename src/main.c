#include "main.h"

int parse_args(int argc, char *argv[], status_t *status) {
    if (argc < 2) {
        print_help();
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }

        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            print_version("promtporium", VERSION);
            return 0;
        }
        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--init") == 0) {
            load_config(status);
            return 0;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    status_t status = init_status("parse_args");
    int ret = parse_args(argc, argv, &status);
    handle_status(&status);

    return ret;
}