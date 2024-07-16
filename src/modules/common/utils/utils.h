#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#include "../common-modules.h"
#include "definitions.h"

extern int $debug_mode;

extern char *$log_file_path;

int $get_ipc_key();

int $log_message(int level, const char *message);

int $log_info(char *message);

int $log_error(char *function_name, char *message);

int $log_warning(char *message);

int $log_debug(char *function_name, char *message);

char *$strtrim(char *s);

void $debug_config(struct config *config);

#endif
