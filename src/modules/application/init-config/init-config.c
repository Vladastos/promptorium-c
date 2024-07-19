#include "init-config.h"

static struct config_t _get_default_config() {
    struct config_t default_config = {.SHOW_GIT_STATUS = 1,
                                      .SHOW_HOST = 1,
                                      .SHOW_HOME_ICON = 1,
                                      .SHOW_BOOKMARK_ICON = 1,
                                      .SHOW_EXIT_ICON = 1,
                                      .SHOW_TIME = 1};
    return default_config;
}

static void _parse_config_line(char *line, struct config_t *config) {

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

static void _get_config_from_file(struct config_t *default_config) {
    FILE *fp = fopen(CONFIG_FILE_PATH, "r");

    if (fp == NULL) {
        $throw_error("read_config_from_file : fopen", "Failed to open config file");
    } else {
        // read the config
        char line[1024];
        while (fgets(line, 1024, fp) != NULL) {
            _parse_config_line(line, default_config);
        }
        // close the file
        fclose(fp);
    }

    $debug_config(default_config);

    return;
}

static char *read_json_file(char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = malloc(length + 1);
    if (buffer == NULL) {
        fclose(fp);
        return NULL;
    }
    fread(buffer, 1, length, fp);
    fclose(fp);
    buffer[length] = '\0';
    return buffer;
}

int init_config() {

    struct config_t default_config = _get_default_config();

    _get_config_from_file(&default_config);

    $memory_create_segment($get_ipc_key(), sizeof(struct config_t), IPC_CREAT | 0600);

    $memory_write_segment($get_ipc_key(), &default_config);

    return 0;
}
