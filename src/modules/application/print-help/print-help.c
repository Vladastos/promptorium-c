#include "print-help.h"
int print_help() {
    printf("Usage: promptorium <command> [options]\n");
    printf("Commands:\n");
    printf("  debug            Start in debug mode\n");
    printf("Options:\n");
    printf("  -h, --help       Print this help message\n");
    printf("  -v, --version    Print the version\n");
    printf("  -i, --init       Load config into shared memory\n");
    printf("  -c, --cleanup    Clean up the shared memory\n");
    printf("  -p, --prompt     Print the prompt\n");
    printf("  --               End of options\n");
    return 0;
}