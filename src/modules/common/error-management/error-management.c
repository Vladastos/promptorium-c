#include <errno.h>

#include "error-management.h"

void $throw_error(char *function_name, char *message, ...) {
    va_list args;
    va_start(args, message);
    $log_error(function_name, message, args);
    if (errno != 0) {
        $log_error(function_name, strerror(errno), args);
    }
    va_end(args);
    exit(1);
}
