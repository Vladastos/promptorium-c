#include "print-help.h"
int print_help() {
    printf("Usage: promtporium [options]\n");
    printf("Options:\n");
    printf("  -h, --help       Print this help message\n");
    printf("  -v, --version    Print the version\n");
    printf("  -i, --init       Load config into shared memory\n");
    printf("  -c, --cleanup    Clean up the shared memory\n");
    return 0;
}