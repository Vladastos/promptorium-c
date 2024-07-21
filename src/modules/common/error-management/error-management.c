#include <errno.h>

#include "error-management.h"

void $throw_error(const char *function_name, char *message, ...) {
    va_list args;
    va_start(args, message);
    $log_error(function_name, message, args);
    if (errno != 0) {
        $log_error(function_name, strerror(errno), args);
    }
    va_end(args);
    exit(1);
}

void $at_exit_handler() {
    // print a formatted string indicating the number of milliseconds it took to execute the
    // program
    int elapsed_time = (int)(clock() * 1000 / CLOCKS_PER_SEC);
    $log_debug(DEBUG_LEVEL_MAX, "$at_exit_handler", "Program execution time: %d ms", elapsed_time);
}
