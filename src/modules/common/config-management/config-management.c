#include "config-management.h"

/*

    This module manages the global configuration.
    It is responsible for the following:
        - Initializing the configuration to default values
        - Loading the configuration from a file
        - granting access to the modules and the config singletons

*/

// Initializing singletons
struct config_t $config = {NULL};

struct module_t $modules[AVAILABLE_MODULES_LENGTH] = {NULL};

struct promptorium_container_t $containers[MAX_CONTAINERS] = {NULL};

// Getters

struct module_t *$get_module_instance_by_name(char *name) {
    if (name == NULL) {
        $throw_error(__func__, "name is NULL");
    }

    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if (strcmp($modules[i].name, name) == 0) {
            return &$modules[i];
        }
    }
    return NULL;
}

// Functions for container creation

struct promptorium_container_t
$create_promptorium_container(char *module_names[], int num_modules, char *container_name,
                              struct container_style_t container_style, char *modules_separator) {
    struct promptorium_container_t promptorium_container = {NULL};

    promptorium_container.name = container_name;
    promptorium_container.style = container_style;
    promptorium_container.modules_separator = modules_separator;
    for (int i = 0; i < num_modules; i++) {
        promptorium_container.modules[i] = $get_module_instance_by_name(module_names[i]);
    }
    return promptorium_container;
}

// Functions for initializing configuration with default values

static struct global_style_t _create_default_global_style() {
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

static struct container_style_t _create_default_container_style() {

    struct container_style_t default_container_style = {
        .background_color = DEFAULT_PRIMARY_COLOR,
        .foreground_color = DEFAULT_BACKGROUND_COLOR,
        .separator = DEFAULT_MODULE_SEPARATOR,
        .start_divider = DEFAULT_CONTAINER_START_DIVIDER,
        .end_divider = DEFAULT_CONTAINER_END_DIVIDER};
    return default_container_style;
};

static struct promptorium_container_t *_create_default_containers() {
    struct promptorium_container_t default_containers[MAX_CONTAINERS] = {NULL};

    return default_containers;
}

static struct module_t _create_os_icon_module() {

    struct module_t os_icon = {
        .name = "os_icon",
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_BACKGROUND_COLOR,
                                         .foreground_color = DEFAULT_PRIMARY_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_BACKGROUND_COLOR,
                                            .foreground_color = DEFAULT_PRIMARY_COLOR,
                                            .separator = ""}};
    return os_icon;
};

static struct module_t _create_user_module() {

    struct module_t user = {
        .name = "user",
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                         .foreground_color = DEFAULT_BACKGROUND_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                            .foreground_color = DEFAULT_BACKGROUND_COLOR,
                                            .separator = ""}};
    return user;
};

static struct module_t _create_hostname_module() {

    struct module_t hostname = {
        .name = "hostname",
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                         .foreground_color = DEFAULT_BACKGROUND_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                            .foreground_color = DEFAULT_BACKGROUND_COLOR,
                                            .separator = ""}};
    return hostname;
};

static struct module_t _create_cwd_module() {

    struct module_t cwd = {
        .name = "cwd",
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                         .foreground_color = DEFAULT_BACKGROUND_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                            .foreground_color = DEFAULT_BACKGROUND_COLOR,
                                            .separator = ""}};
    return cwd;
};

static struct module_t _create_git_module() {

    struct module_t git = {
        .name = "git",
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                         .foreground_color = DEFAULT_BACKGROUND_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                            .foreground_color = DEFAULT_BACKGROUND_COLOR,
                                            .separator = ""}};
    return git;
};

static struct module_t _create_time_module() {

    struct module_t time = {
        .name = "time",
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                         .foreground_color = DEFAULT_BACKGROUND_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                            .foreground_color = DEFAULT_BACKGROUND_COLOR,
                                            .separator = ""}};
    return time;
};

static struct module_t _create_exit_status_module() {

    struct module_t exit_status = {
        .name = "exit_status",
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                         .foreground_color = DEFAULT_BACKGROUND_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                            .foreground_color = DEFAULT_BACKGROUND_COLOR,
                                            .separator = ""}};
    return exit_status;
};

static void _initialize_default_modules() {

    $log_debug(DEBUG_LEVEL_MEDIUM, "_initialize_default_modules", "Initializing default modules");

    $modules[0] = _create_os_icon_module();
    $modules[1] = _create_user_module();
    $modules[2] = _create_hostname_module();
    $modules[3] = _create_cwd_module();
    $modules[4] = _create_git_module();
    $modules[5] = _create_time_module();
    $modules[6] = _create_exit_status_module();
}

struct config_t $create_default_config() {

    _initialize_default_modules();

    struct config_t default_config = {.version = PROMPTORIUM_VERSION,
                                      .global_style = _create_default_global_style(),
                                      .modules = {NULL},
                                      .containers = {NULL}};
    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if ($modules[i].name != NULL) {
            default_config.modules[i] = $modules[i];
        }
    }

    return default_config;
}

// Debug functions

void $debug_config(struct config_t *config) {
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Version: %s", config->version);
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Global style:");
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Container start divider: %s",
               config->global_style.container_end_divider);
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Container end divider: %s",
               config->global_style.container_end_divider);
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Container padding: %s",
               config->global_style.container_padding);
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Container spacer: %s",
               config->global_style.container_spacer);
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Module separator: %s",
               config->global_style.module_separator);
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Module padding: %s",
               config->global_style.module_padding);

    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Modules:");
    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if (config->modules[i].name != NULL) {
            $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Module %d: %s", i,
                       config->modules[i].name);
            $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Icon: %s", config->modules[i].icon);
        }
    }

    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Containers:");
    for (int i = 0; i < MAX_CONTAINERS; i++) {
        if (config->containers[i].name != NULL) {
            $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Container %d: %s", i,
                       config->containers[i].name);
        }
    }
    return;
}
