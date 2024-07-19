
#ifndef LOG_MANAGEMENT_H
#define LOG_MANAGEMENT_H

#include "../common-modules.h"
#include "../definitions.h"

int $log_message(int log_level, char *message, va_list args);

int $log_info(char *message, ...);

int $log_error(char *function_name, char *message, va_list args);

int $log_warning(char *message, ...);

int $log_debug(int level, char *function_name, char *message, ...);

#endif