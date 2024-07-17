#include "utils.h"
#include "../error-management/error-management.h"
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

void $debug_config(struct config_t *config) {

    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "Config after parsing: ");
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_GIT_STATUS: %d", config->SHOW_GIT_STATUS);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_HOST: %d", config->SHOW_HOST);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_HOME_ICON: %d", config->SHOW_HOME_ICON);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_BOOKMARK_ICON: %d", config->SHOW_BOOKMARK_ICON);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_EXIT_ICON: %d", config->SHOW_EXIT_ICON);
    $log_debug(DEBUG_LEVEL_MAX,"_debug_config", "SHOW_TIME: %d", config->SHOW_TIME);
}