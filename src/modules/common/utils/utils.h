#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#include "../common-modules.h"
#include "../utils/definitions.h"

extern int $GLOBAL_debug_level;

extern char *$GLOBAL_log_file_path;

extern char *$GLOBAL_config_file_path;

char *$UTILS_get_file_content(char *file_path);

void $UTILS_debug_args(int argc, char *argv[]);

void $UTILS_throw_error(char *function_name, char *message, ...);

#endif
