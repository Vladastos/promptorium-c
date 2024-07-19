#include "init-config.h"

static struct config_t _get_default_config() {

    struct global_style_t default_global_style = {
        .container_start_divider = DEFAULT_CONTAINER_START_DIVIDER,
        .container_end_divider = DEFAULT_CONTAINER_END_DIVIDER,
        .container_padding = DEFAULT_CONTAINER_PADDING,
        .container_spacer = DEFAULT_CONTAINER_SPACER,
        .module_separator = DEFAULT_MODULE_SEPARATOR,
        .module_padding = DEFAULT_MODULE_PADDING,
        .primary_color = DEFAULT_PRIMARY_COLOR,
        .secondary_color = DEFAULT_SECONDARY_COLOR,
        .tertiary_color = DEFAULT_TERTIARY_COLOR,
        .quaternary_color = DEFAULT_QUATERNARY_COLOR,
        .success_color = DEFAULT_SUCCESS_COLOR,
        .warning_color = DEFAULT_WARNING_COLOR,
        .error_color = DEFAULT_ERROR_COLOR};
    struct config_t default_config = {
        .version = PROMPTORIUM_VERSION,
        .global_style = &default_global_style,

    };
    return default_config;
}

static void __debug_config_file(char *config_file_content) {
    if ($debug_level < DEBUG_LEVEL_MAX) {
        return;
    }
    $log_debug(DEBUG_LEVEL_MAX, "__debug_config_file", "Config file content:");
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
    __debug_config_file(config_file_content);
    if (config_file_content == NULL) {
        $throw_error("_get_config_from_file : _read_json_file", "Failed to read config file");
    }
    free(config_file_content);
}

int init_config() {

    struct config_t default_config = _get_default_config();

    _get_config_from_file();

    $memory_create_segment($get_ipc_key(), sizeof(struct config_t), IPC_CREAT | 0600);

    $memory_write_segment($get_ipc_key(), &default_config);

    return 0;
}
