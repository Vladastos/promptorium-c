#include "utils.h"
#include "../error-management/error-management.h"
#include "definitions.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

char *$strtrim(char *str) {
    char *end;
    while (isspace(*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

void $debug_args(int argc, char *argv[]) {
    $log_debug(DEBUG_LEVEL_MAX, "$debug_args", "Arguments: %d", argc);
    for (int i = 0; argv[i] != NULL; i++) {
        $log_debug(DEBUG_LEVEL_MAX, "$debug_args", "Arg %d: %s", i, argv[i]);
    }
    return;
}
