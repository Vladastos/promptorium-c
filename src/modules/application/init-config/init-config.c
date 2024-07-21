#include "init-config.h"

static void _debug_config_file(char *config_file_content) {
    return;
    if ($debug_level < DEBUG_LEVEL_MAX) {
    }
    $log_debug(DEBUG_LEVEL_MAX, "_debug_config_file", "Config file content:");
    printf("Config file content: %s\n", config_file_content);
}

static char *__read_json_file(char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    $log_debug(DEBUG_LEVEL_MEDIUM, "__read_json_file", "File length: %ld", length);
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

static void _get_config_from_file() {
    char *config_file_path = CONFIG_FILE_PATH;
    char *config_file_content = __read_json_file(config_file_path);
    _debug_config_file(config_file_content);
    if (config_file_content == NULL) {
        $throw_error("_get_config_from_file : _read_json_file", "Failed to read config file");
    }
    free(config_file_content);
}

int init_config() {

    struct config_t default_config = $create_default_config();

    $debug_config(&default_config);

    _get_config_from_file();

    $memory_create_segment($get_ipc_key(), sizeof(struct config_t), IPC_CREAT | 0600);

    $memory_write_segment($get_ipc_key(), &default_config);

    return 0;
}
