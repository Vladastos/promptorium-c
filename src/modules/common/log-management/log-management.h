
#ifndef LOG_MANAGEMENT_H
#define LOG_MANAGEMENT_H

#include "../common-modules.h"
#include "../utils/definitions.h"

int $LOG_message(int log_level, char *message, va_list args);

int $LOG_info(char *message, ...);

int $LOG_error(char *function_name, char *message, va_list args);

int $LOG_warning(char *message, ...);

int $LOG_debug(int level, char *function_name, char *message, ...);

#endif