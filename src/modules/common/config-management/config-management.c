#include "config-management.h"

/*

    This module manages the global configuration.
    It is responsible for the following:
        - Initializing the configuration to default values
        - Loading the configuration from a file

*/

// Initializing global variables
struct module_t $modules[AVAILABLE_MODULES_LENGTH] = {NULL};

struct promptorium_container_t $containers[MAX_CONTAINERS] = {NULL};

// Getters

struct module_t *$CONFIG_get_module_instance_by_name(char *name) {
    if (name == NULL) {
        $UTILS_throw_error("$CONFIG_get_module_instance_by_name", "name is NULL");
    }

    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if (strcmp($modules[i].name, name) == 0) {
            return &$modules[i];
        }
    }
    return NULL;
}

// Functions for container creation

struct promptorium_container_t $CONFIG_create_container(char *module_names[], int num_modules,
                                                        char *container_name,
                                                        struct container_style_t container_style,
                                                        char *modules_separator) {
    struct promptorium_container_t promptorium_container = {NULL};

    promptorium_container.name = container_name;
    promptorium_container.style = container_style;
    promptorium_container.modules_separator = modules_separator;
    for (int i = 0; i < num_modules; i++) {
        promptorium_container.modules[i] = $CONFIG_get_module_instance_by_name(module_names[i]);
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

static struct module_t _create_module(char *name, char *icon, struct module_style_t style,
                                      struct icon_style_t icon_style) {

    struct module_t module = {.name = name, .icon = icon, .style = style, .icon_style = icon_style};
    return module;
}

static struct module_t _create_os_icon_module() {

    struct module_t os_icon = {
        .name = "os_icon",
        .icon = "⚙",
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
        .icon = "󰇅",
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
        .icon = "",
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
        .icon = "",
        .style = (struct module_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                         .foreground_color = DEFAULT_BACKGROUND_COLOR},
        .icon_style = (struct icon_style_t){.background_color = DEFAULT_PRIMARY_COLOR,
                                            .foreground_color = DEFAULT_BACKGROUND_COLOR,
                                            .separator = ""}};
    return exit_status;
};

static void _initialize_default_modules() {

    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_initialize_default_modules", "Initializing default modules");

    $modules[0] = _create_os_icon_module();
    $modules[1] = _create_user_module();
    $modules[2] = _create_hostname_module();
    $modules[3] = _create_cwd_module();
    $modules[4] = _create_git_module();
    $modules[5] = _create_time_module();
    $modules[6] = _create_exit_status_module();
}

static void _initialize_default_containers() {
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_initialize_default_containers",
               "Initializing default containers");

    struct container_style_t default_container_style = _create_default_container_style();

    char *user_modules[] = {"user", "hostname"};
    char *cwd_modules[] = {"cwd", "git"};
    char *time_modules[] = {"time"};

    $containers[0] = $CONFIG_create_container(user_modules, 2, "user", default_container_style,
                                              DEFAULT_MODULE_SEPARATOR);
    $containers[1] = $CONFIG_create_container(cwd_modules, 2, "cwd", default_container_style,
                                              DEFAULT_MODULE_SEPARATOR);
    $containers[2] = $CONFIG_create_container(time_modules, 1, "time", default_container_style,
                                              DEFAULT_MODULE_SEPARATOR);
};

struct config_t $CONFIG_create_default_config() {

    _initialize_default_modules();

    _initialize_default_containers();

    struct config_t default_config = {.version = PROMPTORIUM_VERSION,
                                      .global_style = _create_default_global_style(),
                                      .modules = {NULL},
                                      .containers = {NULL}};
    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if ($modules[i].name != NULL) {
            default_config.modules[i] = $modules[i];
        }
    }

    for (int i = 0; i < MAX_CONTAINERS; i++) {
        if ($containers[i].name != NULL) {
            default_config.containers[i] = $containers[i];
        }
    }

    return default_config;
}

// Config file functions

static void _set_global_color(struct color_t *color, char *color_name) {

    for (int i = 0; i < AVAILABLE_COLORS_LENGTH; i++) {
        if (strcmp(color_name, $colors[i]->name) == 0) {
            color->background_code = $colors[i]->background_code;
            color->foreground_code = $colors[i]->foreground_code;
            color->name = $colors[i]->name;
            return;
        }
    }

    $LOG_debug(DEBUG_LEVEL_MIN, "_set_global_color", "Invalid color name: %s", color_name);
}

static void _parse_global_style(struct config_t *config, cJSON *style) {

    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_parse_global_style", "Parsing global style");

    // Set dividers and padding
    cJSON *container_start_divider = cJSON_GetObjectItem(style, "container_start_divider");
    cJSON *container_end_divider = cJSON_GetObjectItem(style, "container_end_divider");
    cJSON *container_padding = cJSON_GetObjectItem(style, "container_padding");
    cJSON *container_spacer = cJSON_GetObjectItem(style, "container_spacer");
    cJSON *module_separator = cJSON_GetObjectItem(style, "module_separator");
    cJSON *module_padding = cJSON_GetObjectItem(style, "module_padding");

    if (container_start_divider != NULL) {
        config->global_style.container_start_divider = strdup(container_start_divider->valuestring);
    }
    if (container_end_divider != NULL) {
        config->global_style.container_end_divider = strdup(container_end_divider->valuestring);
    }
    if (container_padding != NULL) {
        config->global_style.container_padding = strdup(container_padding->valuestring);
    }
    if (container_spacer != NULL) {
        config->global_style.container_spacer = strdup(container_spacer->valuestring);
    }
    if (module_separator != NULL) {
        config->global_style.module_separator = strdup(module_separator->valuestring);
    }
    if (module_padding != NULL) {
        config->global_style.module_padding = strdup(module_padding->valuestring);
    }

    // Set colors
    cJSON *primary_color = cJSON_GetObjectItem(style, "primary_color");
    cJSON *secondary_color = cJSON_GetObjectItem(style, "secondary_color");
    cJSON *tertiary_color = cJSON_GetObjectItem(style, "tertiary_color");
    cJSON *quaternary_color = cJSON_GetObjectItem(style, "quaternary_color");
    cJSON *success_color = cJSON_GetObjectItem(style, "success_color");
    cJSON *warning_color = cJSON_GetObjectItem(style, "warning_color");
    cJSON *error_color = cJSON_GetObjectItem(style, "error_color");

    if (primary_color != NULL) {
        _set_global_color(config->global_style.primary_color, primary_color->valuestring);
    }
    if (secondary_color != NULL) {
        _set_global_color(config->global_style.secondary_color, secondary_color->valuestring);
    }
    if (tertiary_color != NULL) {
        _set_global_color(config->global_style.tertiary_color, tertiary_color->valuestring);
    }
    if (quaternary_color != NULL) {
        _set_global_color(config->global_style.quaternary_color, quaternary_color->valuestring);
    }
    if (success_color != NULL) {
        _set_global_color(config->global_style.success_color, success_color->valuestring);
    }
    if (warning_color != NULL) {
        _set_global_color(config->global_style.warning_color, warning_color->valuestring);
    }
    if (error_color != NULL) {
        _set_global_color(config->global_style.error_color, error_color->valuestring);
    }
}

// Module functions

static void _set_module_color(struct color_t **color, char *color_name, struct config_t *config) {
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_set_module_color", "Setting module color: %s", color_name);
    for (int i = 0; i < AVAILABLE_COLORS_LENGTH; i++) {
        if (strcmp(color_name, $colors[i]->name) == 0) {
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "_set_module_color", "Found color: %s", color_name);
            *color = $colors[i];
            return;
        }
    }
    // Check if the color is "primary","secondary","tertiary","quaternary" or "none"

    if (strcmp(color_name, "primary") == 0) {
        *color = config->global_style.primary_color;
        return;
    } else if (strcmp(color_name, "secondary") == 0) {
        *color = config->global_style.secondary_color;
        return;
    } else if (strcmp(color_name, "tertiary") == 0) {
        *color = config->global_style.tertiary_color;
        return;
    } else if (strcmp(color_name, "quaternary") == 0) {
        *color = config->global_style.quaternary_color;
        return;
    } else if (strcmp(color_name, "none") == 0) {
        *color = &COLOR_RESET;
        return;
    }

    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_set_module_color", "Invalid color name: %s", color_name);
}

static void _parse_module_style(struct module_t *module, cJSON *style, struct config_t *config) {

    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_parse_module_style", "Parsing module style");

    cJSON *background_color = cJSON_GetObjectItem(style, "background_color");
    if (background_color != NULL) {
        $LOG_debug(DEBUG_LEVEL_MAX, "_parse_module_style", "Setting %s background color to %s",
                   module->name, background_color->valuestring);
        _set_module_color(&module->style.background_color, background_color->valuestring, config);
    }

    cJSON *foreground_color = cJSON_GetObjectItem(style, "foreground_color");
    if (foreground_color != NULL) {
        $LOG_debug(DEBUG_LEVEL_MAX, "_parse_module_style", "Setting %s foreground color to %s",
                   module->name, foreground_color->valuestring);
        _set_module_color(&module->style.foreground_color, foreground_color->valuestring, config);
    }
}

static void _parse_icon_style(struct module_t *module, cJSON *icon_style, struct config_t *config) {

    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_parse_icon_style", "Parsing icon style");

    cJSON *background_color = cJSON_GetObjectItem(icon_style, "background_color");
    if (background_color != NULL) {
        _set_module_color(&module->icon_style.background_color, background_color->valuestring,
                          config);
    }

    cJSON *foreground_color = cJSON_GetObjectItem(icon_style, "foreground_color");
    if (foreground_color != NULL) {
        _set_module_color(&module->icon_style.foreground_color, foreground_color->valuestring,
                          config);
    }

    cJSON *separator = cJSON_GetObjectItem(icon_style, "separator");
    if (separator != NULL) {
        $LOG_debug(DEBUG_LEVEL_MAX, "_parse_icon_style", "Setting %s separator to %s", module->name,
                   separator->valuestring);
        module->icon_style.separator = strdup(separator->valuestring);
    }
}

static void _parse_module(struct module_t *module, cJSON *module_json, struct config_t *config) {
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_parse_module", "Parsing module: %s", module_json->string);

    // Set icon
    char *icon = cJSON_GetObjectItem(module_json, "icon")->valuestring;
    if (icon != NULL) {
        module->icon = strdup(icon);
    }

    // Set style
    cJSON *style = cJSON_GetObjectItem(module_json, "style");
    if (style != NULL) {
        _parse_module_style(module, style, config);
    }
    // Set icon style
    cJSON *icon_style = cJSON_GetObjectItem(module_json, "icon_style");
    if (icon_style != NULL) {
        _parse_icon_style(module, icon_style, config);
    }
}
static void _parse_modules(struct config_t *config, cJSON *modules) {

    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {

        cJSON *module = cJSON_GetObjectItem(modules, config->modules[i].name);
        if (module != NULL) {
            _parse_module(&config->modules[i], module, config);
        }
    }
}

static void _parse_containers(struct config_t *config, cJSON *containers) {
    // TODO
}

static void _parse_config_json(struct config_t *config, char *config_file_content) {
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "_parse_config_json", "Parsing config from JSON");
    cJSON *json = cJSON_Parse(config_file_content);
    if (json == NULL) {
        $UTILS_throw_error("_parse_config_json : cJSON_Parse", "Failed to parse JSON");
    }

    // Parse version
    config->version = strdup(cJSON_GetObjectItem(json, "version")->valuestring);

    // Parse global style
    cJSON *global_style = cJSON_GetObjectItem(json, "style");
    if (global_style != NULL) {
        _parse_global_style(config, global_style);
    }

    // Parse modules
    // This operations have to be done after the global style is parsed because the global colors
    // are needed

    cJSON *modules = cJSON_GetObjectItem(json, "modules");
    _parse_modules(config, modules);

    // Parse containers

    cJSON *containers = cJSON_GetObjectItem(json, "containers");
    _parse_containers(config, containers);

    cJSON_Delete(json);
}

void $CONFIG_set_config_from_json(struct config_t *config, char *config_file_content) {
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_set_config_from_json", "Setting config from JSON");
    _parse_config_json(config, config_file_content);
}

void $CONFIG_free_config() {
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_free_config", "Freeing config");
    // TODO: Free config
}

void $CONFIG_set_config_from_file(struct config_t *config) {
    char *config_file_content = $UTILS_get_file_content($GLOBAL_config_file_path);

    if (config_file_content == NULL) {
        $UTILS_throw_error("_get_config_from_file : _read_json_file", "Failed to read config file");
    }

    $CONFIG_set_config_from_json(config, config_file_content);

    $CONFIG_free_config();
}

// Debug functions

void $CONFIG_debug_config(struct config_t *config) {
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Version: %s", config->version);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Global style:");
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Container start divider: %s",
               config->global_style.container_start_divider);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Container end divider: %s",
               config->global_style.container_end_divider);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Container padding: %s",
               config->global_style.container_padding);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Container spacer: %s",
               config->global_style.container_spacer);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Module separator: %s",
               config->global_style.module_separator);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Module padding: %s",
               config->global_style.module_padding);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Primary color: %s",
               config->global_style.primary_color->name);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Secondary color: %s",
               config->global_style.secondary_color->name);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Tertiary color: %s",
               config->global_style.tertiary_color->name);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Quaternary color: %s",
               config->global_style.quaternary_color->name);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Success color: %s",
               config->global_style.success_color->name);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Warning color: %s",
               config->global_style.warning_color->name);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Error color: %s",
               config->global_style.error_color->name);

    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Modules:");
    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if (config->modules[i].name != NULL) {
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Module %d: %s", i,
                       config->modules[i].name);
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Icon: %s",
                       config->modules[i].icon);
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Background color: %s",
                       config->modules[i].style.background_color->name);
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Foreground color: %s",
                       config->modules[i].style.foreground_color->name);
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Icon background color: %s",
                       config->modules[i].icon_style.background_color->name);
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Icon foreground color: %s",
                       config->modules[i].icon_style.foreground_color->name);
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Icon separator: %s",
                       config->modules[i].icon_style.separator);
        }
    }

    $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Containers:");
    for (int i = 0; i < MAX_CONTAINERS; i++) {
        if (config->containers[i].name != NULL) {
            $LOG_debug(DEBUG_LEVEL_MEDIUM, "$CONFIG_debug_config", "Container %d: %s", i,
                       config->containers[i].name);
        }
    }
    return;
}
