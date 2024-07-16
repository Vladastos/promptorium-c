#include "init-config.h"

struct config _get_default_config() {
    struct config default_config = {.SHOW_GIT_STATUS = 1,
                                    .SHOW_HOST = 1,
                                    .SHOW_HOME_ICON = 1,
                                    .SHOW_BOOKMARK_ICON = 1,
                                    .SHOW_EXIT_ICON = 1,
                                    .SHOW_TIME = 1};
    return default_config;
}

void _get_config_from_file(struct config *default_config) {

    $log_debug("get_config_from_file", CONFIG_FILE_PATH);
    FILE *fp = fopen(CONFIG_FILE_PATH, "r");

    if (fp == NULL) {
        throw_error("read_config_from_file : fopen", "Failed to open config file");
    } else {
        // read the config
        char line[1024];
        while (fgets(line, 1024, fp) != NULL) {
            // TODO: parse the config
            _parse_config_line(line, default_config);
        }
        // close the file
        fclose(fp);
    }

    $debug_config(default_config);

    return;
}

void _parse_config_line(char *line, struct config *config) {

    char *key = strtok(line, "=");
    char *value = strtok(NULL, "\n");

    if (key == NULL || value == NULL) {
        return;
    }

    key = $strtrim(key);
    value = $strtrim(value);
    if (strcmp(key, "SHOW_GIT_STATUS") == 0) {
        if (strcmp(value, "0") == 0) {
            config->SHOW_GIT_STATUS = 0;
        }
    } else if (strcmp(key, "SHOW_HOST") == 0) {
        if (strcmp(value, "0") == 0) {
            config->SHOW_HOST = 0;
        }
    } else if (strcmp(key, "SHOW_HOME_ICON") == 0) {
        if (strcmp(value, "0") == 0) {
            config->SHOW_HOME_ICON = 0;
        }
    } else if (strcmp(key, "SHOW_BOOKMARK_ICON") == 0) {
        if (strcmp(value, "0") == 0) {
            config->SHOW_BOOKMARK_ICON = 0;
        }
    } else if (strcmp(key, "SHOW_EXIT_ICON") == 0) {
        if (strcmp(value, "0") == 0) {
            config->SHOW_EXIT_ICON = 0;
        }
    } else if (strcmp(key, "SHOW_TIME") == 0) {
        if (strcmp(value, "0") == 0) {
            config->SHOW_TIME = 0;
        }
    }

    return;
}

int init_config() {

    $log_debug("init_config", "Initializing config");

    struct config default_config = _get_default_config();

    $log_debug("get_config_from_file", "Reading config from file");

    // TODO: load configuration from file
    _get_config_from_file(&default_config);

    $log_debug("init_config", "Creating shared memory segment");

    $memory_create_segment($get_ipc_key(), sizeof(struct config), IPC_CREAT | IPC_EXCL | 0600);

    // write the config to the shared memory segment

    $log_debug("init_config", "Writing config to shared memory segment");

    $memory_write_segment($get_ipc_key(), &default_config);

    return 0;
}
