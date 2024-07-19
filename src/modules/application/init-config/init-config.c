#include "init-config.h"

static struct module_t *__get_default_modules() {

    struct module_style_t default_module_style = {};

    struct icon_style_t default_icon_style = {};

    struct module_t user = {.name = "user",
                            .icon = "",
                            .style = &default_module_style,
                            .icon_style = &default_icon_style};

    struct module_t cwd = {.name = "cwd",
                           .icon = "",
                           .style = &default_module_style,
                           .icon_style = &default_icon_style};

    struct module_t os_icon = {.name = "os_icon",
                               .icon = "⚙",
                               .style = &default_module_style,
                               .icon_style = &default_icon_style};

    struct module_t hostname = {.name = "hostname",
                                .icon = "󰇅",
                                .style = &default_module_style,
                                .icon_style = &default_icon_style};

    struct module_t git = {.name = "git",
                           .icon = "",
                           .style = &default_module_style,
                           .icon_style = &default_icon_style};

    struct module_t time = {.name = "time",
                            .icon = "",
                            .style = &default_module_style,
                            .icon_style = &default_icon_style};

    struct module_t exit_status = {.name = "exit_status",
                                   .icon = "",
                                   .style = &default_module_style,
                                   .icon_style = &default_icon_style};

    struct module_t modules_array[] = {user, cwd, os_icon, hostname, git, time, exit_status};

    struct module_t *modules = (struct module_t *)calloc(MAX_MODULES, sizeof(struct module_t));

    memcpy(modules, modules_array, sizeof(modules_array));

    return modules;
};

static struct module_t *__get_module_by_name(char *name, struct module_t *modules) {

    for (int i = 0; i < MAX_MODULES; i++) {
        if (strcmp(modules[i].name, name) == 0) {
            return &modules[i];
        }
    }
    return NULL;
}

static struct global_style_t __get_default_global_style() {
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

    return default_global_style;
}

static struct container_style_t __get_default_container_style() {

    struct container_style_t default_container_style = {
        .background_color = DEFAULT_PRIMARY_COLOR,
        .foreground_color = DEFAULT_BACKGROUND_COLOR,
        .separator = DEFAULT_MODULE_SEPARATOR,
        .start_divider = DEFAULT_CONTAINER_START_DIVIDER,
        .end_divider = DEFAULT_CONTAINER_END_DIVIDER};
    return default_container_style;
}

static struct config_t _get_default_config() {

    struct module_t *modules = __get_default_modules();

    struct global_style_t default_global_style = __get_default_global_style();

    struct container_style_t default_container_style = __get_default_container_style();

    struct module_t *user_container_modules = {__get_module_by_name("user", modules),
                                               __get_module_by_name("hostname", modules)};

    struct module_t *cwd_container_modules = {__get_module_by_name("cwd", modules),
                                              __get_module_by_name("git", modules)};

    struct module_t *exit_container_modules = {__get_module_by_name("time", modules),
                                               __get_module_by_name("exit_status", modules)};

    struct promptorium_container_t user_container = {.name = "user_container",
                                                     .modules = user_container_modules,
                                                     .style = &default_container_style};

    struct promptorium_container_t cwd_container = {.name = "cwd_container",
                                                    .modules = cwd_container_modules,
                                                    .style = &default_container_style};

    struct promptorium_container_t exit_container = {.name = "exit_container",
                                                     .modules = exit_container_modules,
                                                     .style = &default_container_style};

    struct promptorium_container_t containers[] = {user_container, cwd_container,
                                                   exit_container};

    struct config_t default_config = {
        .version = PROMPTORIUM_VERSION,
        .containers = containers,
        .global_style = &default_global_style,
        .modules = modules,

    };

    return default_config;
}

static void __debug_config_file(char *config_file_content) {
    return;
    if ($debug_level < DEBUG_LEVEL_MAX) {
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

    $debug_config(&default_config);

    _get_config_from_file();

    $memory_create_segment($get_ipc_key(), sizeof(struct config_t), IPC_CREAT | 0600);

    $memory_write_segment($get_ipc_key(), &default_config);

    return 0;
}
