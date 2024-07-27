#include "init-config.h"

static void _set_config_from_file(struct config_t *config) {
    char *config_file_path = CONFIG_FILE_PATH;
    char *config_file_content = $UTILS_get_file_content(config_file_path);

    if (config_file_content == NULL) {
        $UTILS_throw_error("_set_config_from_file : _read_json_file", "Failed to read config file");
    }

    $CONFIG_set_config_from_json(config, config_file_content);

    $CONFIG_free_config();
}

// This function loads the content of the config file into the shared memory segment
int init_config() {

    $MEMORY_create_segment($MEMORY_get_ipc_key(), SHARED_MEMORY_SEGMENT_SIZE, IPC_CREAT | 0600);

    char *config_file_content = $UTILS_get_file_content($GLOBAL_config_file_path);
    if (config_file_content == NULL) {
        $UTILS_throw_error("init_config : _get_file_content", "Failed to read config file");
    }

    $MEMORY_write_segment($MEMORY_get_ipc_key(), config_file_content);

    return 0;
}
