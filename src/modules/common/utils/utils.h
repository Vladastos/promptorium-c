#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#include "../common-modules.h"
#include "definitions.h"

extern int $debug_level;

extern char *$log_file_path;

int $get_ipc_key();

char *$strtrim(char *s);

void $debug_args(int argc, char *argv[]);

void $debug_config(struct config_t *config);

#endif
