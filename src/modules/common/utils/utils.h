#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#include "../common-modules.h"
#include "../utils/definitions.h"

extern int $debug_level;

extern char *$log_file_path;

int $get_ipc_key();

char *$strtrim(char *s);

char *$get_file_content(char *file_path);

void $debug_args(int argc, char *argv[]);

#endif
