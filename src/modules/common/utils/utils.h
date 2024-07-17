#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#include "../common-modules.h"
#include "definitions.h"

extern int $debug_level;

extern char *$log_file_path;

int $get_ipc_key();

int $log_message(int log_level, char *message, va_list args);

int $log_info(char *message, ...);

int $log_error(char *function_name, char *message, ...);

int $log_warning(char *message, ...);

int $log_debug(int level, char *function_name, char *message, ...);

char *$strtrim(char *s);

void $debug_args(int argc, char *argv[]);

void $debug_config(struct config *config);

#endif
