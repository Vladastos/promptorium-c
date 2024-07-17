#include "utils.h"
#include "../status-handling/status-handling.h"
#include "definitions.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int $get_ipc_key() {
    char *key = getenv(IPC_KEY_VARIABLE_NAME);
    $log_debug(DEBUG_LEVEL_MAX, "$get_ipc_key", "Getting IPC key from environment variable");
    $log_debug(DEBUG_LEVEL_MAX, "$get_ipc_key", "IPC key: %s", key);
    if (key == NULL) {
        $throw_error("$get_ipc_key : getenv",
                    "Failed to get shared memory key from environment variable");
    }
    int key_int = atoi(key);
    if (key_int == 0) {
        $throw_error("$get_ipc_key : atoi",
                    "Failed to convert shared memory key from environment variable");
    }
    return key_int;
}

int $log_message(int log_level, char *message, va_list args) {

    char *log_level_string;
    switch (log_level) {
        case LOG_LEVEL_INFO:
            log_level_string = "INFO";
            break;
        case LOG_LEVEL_ERROR:
            log_level_string = "ERROR";
            break;
        case LOG_LEVEL_WARNING:
            log_level_string = "WARNING";
            break;
        case LOG_LEVEL_DEBUG:
            log_level_string = "DEBUG";
            break;
        default:
            log_level_string = "UNKNOWN";
            break;
    }
    // assemble message
    // TODO: assemble message
    char assembled_message[256];
    vsnprintf(assembled_message, 256, message, args);
    va_end(args);

    // get date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[80];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm);
    printf("[ %s ] [ %s ] %s \n", date, log_level_string, assembled_message);
    
    // TODO: log to syslog

    // log to file
    FILE *log_file = fopen($log_file_path, "a");
    if (log_file == NULL) {
        exit(1);
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

int $log_error(char *function_name, char *message, ...) {
    va_list args;
    va_start(args, message);
    char assembled_message[256];
    sprintf(assembled_message, "%s : %s", function_name, message);
    va_end(args);
    return $log_message(LOG_LEVEL_ERROR, assembled_message, args);
}

int $log_warning(char *message, ...) {
    va_list args;
    va_start(args, message);
    va_end(args);
    return $log_message(LOG_LEVEL_WARNING, message, args); 
}

int $log_debug( int level, char *function_name, char *message, ...) {

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
    $log_debug(DEBUG_LEVEL_MAX,"debug_args", "Arguments: %d", argc);
    for (int i = 0; argv[i] != NULL; i++) {
        $log_debug(DEBUG_LEVEL_MAX,"debug_args", "Arg %d: %s", i, argv[i]);
    }
    printf("\n");
    return;
}


void $debug_config(struct config *config) {

    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "Config after parsing: ");
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_GIT_STATUS: %d", config->SHOW_GIT_STATUS);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_HOST: %d", config->SHOW_HOST);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_HOME_ICON: %d", config->SHOW_HOME_ICON);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_BOOKMARK_ICON: %d", config->SHOW_BOOKMARK_ICON);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_EXIT_ICON: %d", config->SHOW_EXIT_ICON);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_TIME: %d", config->SHOW_TIME);
}