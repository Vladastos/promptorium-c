#include "log-management.h"

static char *_get_level_string(int level) {

    switch (level) {
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_ERROR:
            return "ERROR";
        case LOG_LEVEL_WARNING:
            return "WARNING";
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        default:
            return "UNKNOWN";
    }
}

int $log_message(int log_level, char *message, va_list args) {

    char *log_level_string = _get_level_string(log_level);
    char assembled_message[256];
    vsnprintf(assembled_message, 256, message, args);
    va_end(args);

    // get date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[80];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm);
    if ($debug_level >= DEBUG_LEVEL_MIN) {
        printf("[ %s ] [ %s ] %s \n", date, log_level_string, assembled_message);
    } else {
        printf("%s\n", message);
    }

    // TODO: log to syslog

    // log to file
    FILE *log_file = fopen($log_file_path, "a");
    if (log_file == NULL) {
        return -1;
    }
    fprintf(log_file, "[ %s ] [ %s ] %s \n", date, log_level_string, assembled_message);
    fclose(log_file);
    return 0;
}

int $log_info(char *message, ...) {
    va_list args;
    va_start(args, message);
    va_end(args);

    return $log_message(LOG_LEVEL_INFO, message, args);
}

int $log_error(char *function_name, char *message, va_list args) {

    char assembled_message[256];
    if ($debug_level >= DEBUG_LEVEL_MIN) {
        sprintf(assembled_message, "%s : %s", function_name, message);
    } else {
        sprintf(assembled_message, "promptorium : %s", message);
    }

    int result = 0;
    result = $log_message(LOG_LEVEL_ERROR, assembled_message, args);

    va_end(args);
    return result;
}

int $log_warning(char *message, ...) {
    va_list args;
    va_start(args, message);
    va_end(args);
    return $log_message(LOG_LEVEL_WARNING, message, args);
}

int $log_debug(int level, char *function_name, char *message, ...) {

    extern int $debug_level;
    int result = 0;
    if ($debug_level < level) {
        return 0;
    }

    // prepend function name to message
    char assembled_message[256];
    sprintf(assembled_message, "%s : %s", function_name, message);
    va_list args;
    va_start(args, message);

    result = $log_message(LOG_LEVEL_DEBUG, assembled_message, args);

    va_end(args);

    return result;
}
