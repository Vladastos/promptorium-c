#include "utils.h"
#include "../error-management/error-management.h"
#include "definitions.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

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
    $log_debug(DEBUG_LEVEL_MAX, "debug_args", "Arguments: %d", argc);
    for (int i = 0; argv[i] != NULL; i++) {
        $log_debug(DEBUG_LEVEL_MAX, "debug_args", "Arg %d: %s", i, argv[i]);
    }
    return;
}

void $debug_config(struct config_t *config) {
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Version: %s", config->version);
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Global style:");
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Container start divider: %s",
               config->global_style->container_start_divider);
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Container end divider: %s",
               config->global_style->container_end_divider);
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Container padding: %s",
               config->global_style->container_padding);
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Container spacer: %s",
               config->global_style->container_spacer);
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Module separator: %s",
               config->global_style->module_separator);
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Module padding: %s",
               config->global_style->module_padding);
    $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Containers:");
    for (int i = 0; config->containers[i]->name != NULL; i++) {
        $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Container %d: %s", i,
                   config->containers[i]->name);
        $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Modules:");
        for (int j = 0; config->containers[i]->modules[j]->name != NULL; j++) {
            $log_debug(DEBUG_LEVEL_MEDIUM, "debug_config", "Module %d: %s", j,
                       config->containers[i]->modules[j]->name);
        }
    }
}
