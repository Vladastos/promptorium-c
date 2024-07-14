#include "status-handling.h"

void on_error(char *function_name, char *message) {
    fprintf(stderr, "%s: %s\n", function_name, message);
    perror("Error ");
    exit(1);
}
