#include "config-management.h"

/*

    This module manages the global configuration.
    It is responsible for the following:
        - Initializing the configuration to default values
        - Loading the configuration from a file
        - granting access to the modules and the config singletons

*/

// Initializing singletons

static struct module_t *modules[AVAILABLE_MODULES_LENGTH] = {NULL};

static struct promptorium_container_t *containers[MAX_CONTAINERS] = {NULL};

// Getters and setters

struct config_t *$get_config() {
    static struct config_t *config = NULL;
    return config;
}

void $set_config(struct config_t *new_config) {
    if (new_config == NULL) {
        $throw_error(__func__, "new_config is NULL");
    }

    struct config_t *config = $get_config();
    config = new_config;
}

struct module_t **$get_modules() { return modules; }

void $set_modules(struct module_t *new_modules[]) {
    if (new_modules == NULL) {
        $throw_error(__func__, "new_modules is NULL");
    }

    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        modules[i] = new_modules[i];
    }
}

struct module_t *$get_module_by_name(char *name) {
    if (name == NULL) {
        $throw_error(__func__, "name is NULL");
    }

    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if (strcmp(modules[i]->name, name) == 0) {
            return modules[i];
        }
    }
    return NULL;
}

void $set_module_by_name(struct module_t *new_module, char *name) {
    if (new_module == NULL) {
        $throw_error(__func__, "new_module is NULL");
    }

    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if (strcmp(modules[i]->name, name) == 0) {
            modules[i] = new_module;
        }
    }
};

struct promptorium_container_t **$get_containers() { return containers; }

void $set_containers(struct promptorium_container_t *new_containers[]) {
    if (new_containers == NULL) {
        $throw_error(__func__, "new_containers is NULL");
    }

    for (int i = 0; i < MAX_CONTAINERS; i++) {
        containers[i] = new_containers[i];
    }
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
        promptorium_container.modules[i] = $get_module_by_name(module_names[i]);
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

static struct promptorium_container_t **_create_default_containers() {
    struct promptorium_container_t *default_containers[MAX_CONTAINERS] = {NULL};
    

    return default_containers;
}

struct config_t $create_default_config() {

    struct module_t **modules = $get_modules();

    struct promptorium_container_t **containers = $get_containers();

    struct config_t default_config = {.version = PROMPTORIUM_VERSION,
                                      .global_style = _create_default_global_style()};

    for (int i = 0; i < MAX_CONTAINERS; i++) {
        default_config.containers[i] = containers[i];
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
        $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Module %d: %s", i,
                   config->modules[i].name);
    }
    return;
}
