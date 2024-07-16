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
    $log_message(LOG_LEVEL_DEBUG, key);
    if (key == NULL) {
        throw_error("$get_ipc_key : getenv",
                    "Failed to get shared memory key from environment variable");
    }
    int key_int = atoi(key);
    if (key_int == 0) {
        throw_error("$get_ipc_key : atoi",
                    "Failed to convert shared memory key from environment variable");
    }
    return key_int;
}

int $log_message(int level, const char *message) {

    extern int $debug_mode;

    char *log_level;
    switch (level) {
        case LOG_LEVEL_INFO:
            log_level = "INFO";
            break;
        case LOG_LEVEL_ERROR:
            log_level = "ERROR";
            break;
        case LOG_LEVEL_WARNING:
            log_level = "WARNING";
            break;
        case LOG_LEVEL_DEBUG:
            if ($debug_mode == 0) {
                return 0;
            }
            log_level = "DEBUG";
            break;
        default:
            log_level = "UNKNOWN";
            break;
    }
    // get date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[80];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm);
    printf("[ %s ] [ %s ] %s \n", date, log_level, message);
    // TODO: log to syslog

    FILE *log_file = fopen($log_file_path, "a");
    if (log_file == NULL) {
        exit(1);
    }
    fprintf(log_file, "[ %s ] [ %s ] %s \n", date, log_level, message);
    fclose(log_file);

    return 0;
}

int $log_info(char *message) { return $log_message(LOG_LEVEL_INFO, message); }

int $log_error(char *function_name, char *message) {
    // if(message == NULL || function_name == NULL) {
    // 	return 1;
    // }
    // char *message_string = malloc(strlen(function_name) + strlen(message) + 2);
    // if (message_string == NULL) {
    //     return 1;
    // }
    // sprintf(message_string, "%s: %s", function_name, message);
    // int result = $log_message(LOG_LEVEL_ERROR, message_string);
    // free(message_string);
    return $log_message(LOG_LEVEL_ERROR, message);
}

int $log_warning(char *message) { return $log_message(LOG_LEVEL_WARNING, message); }

int $log_debug(char *function_name, char *message) {
    // if(message == NULL || function_name == NULL) {
    // 	return 1;
    // }
    // char *message_string = malloc(strlen(function_name) + strlen(message) + 2);
    // if (message_string == NULL) {
    //     return 1;
    // }
    // sprintf(message_string, "%s: %s", function_name, message);
    // int result = $log_message(LOG_LEVEL_DEBUG, message_string);
    // free(message_string);
    return $log_message(LOG_LEVEL_DEBUG, message);
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

void $debug_config(struct config *config) {
    if (!$debug_mode) {
        return;
    }

    $log_debug("_debug_config", "Config after parsing: ");

    printf("SHOW_GIT_STATUS: %d\n", config->SHOW_GIT_STATUS);
    printf("SHOW_HOST: %d\n", config->SHOW_HOST);
    printf("SHOW_HOME_ICON: %d\n", config->SHOW_HOME_ICON);
    printf("SHOW_BOOKMARK_ICON: %d\n", config->SHOW_BOOKMARK_ICON);
    printf("SHOW_EXIT_ICON: %d\n", config->SHOW_EXIT_ICON);
    printf("SHOW_TIME: %d\n", config->SHOW_TIME);
}