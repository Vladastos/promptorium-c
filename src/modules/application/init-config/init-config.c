#include "init-config.h"

static void _debug_config_file(char *config_file_content) {
    return;
    if ($debug_level < DEBUG_LEVEL_MAX) {
    }
    $log_debug(DEBUG_LEVEL_MAX, "_debug_config_file", "Config file content:");
    printf("Config file content: %s\n", config_file_content);
}

static void _set_config_from_file(struct config_t *config) {
    char *config_file_path = CONFIG_FILE_PATH;
    char *config_file_content = $get_file_content(config_file_path);

    if (config_file_content == NULL) {
        $throw_error("_get_config_from_file : _read_json_file", "Failed to read config file");
    }

    $set_config_from_json(config, config_file_content);

    _debug_config_file(config_file_content);

    $free_config();
}

// This function loads the content of the config file into the shared memory segment
int init_config() {

    $memory_create_segment($get_ipc_key(), SHARED_MEMORY_SEGMENT_SIZE, IPC_CREAT | 0600);

    char *config_file_content = $get_file_content(CONFIG_FILE_PATH);
    if (config_file_content == NULL) {
        $throw_error("init_config : _get_file_content", "Failed to read config file");
    }

    $memory_write_segment($get_ipc_key(), config_file_content);

    return 0;
}
