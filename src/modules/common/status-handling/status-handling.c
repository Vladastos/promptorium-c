#include <errno.h>

#include "status-handling.h"

void $throw_error(char *function_name, char *message) {
    $log_error(function_name, message);
    if (errno != 0) {
        $log_error(function_name, strerror(errno));
    }
    exit(1);
}
