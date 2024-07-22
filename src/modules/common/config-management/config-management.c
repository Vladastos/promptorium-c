#include "config-management.h"

/*

    This module manages the global configuration.
    It is responsible for the following:
        - Initializing the configuration to default values
        - Loading the configuration from a file

*/

// Initializing global variables
struct config_t $config = {NULL};

struct module_t $modules[AVAILABLE_MODULES_LENGTH] = {NULL};

struct promptorium_container_t $containers[MAX_CONTAINERS] = {NULL};

// Getters

struct module_t *$get_module_instance_by_name(char *name) {
    if (name == NULL) {
        $throw_error("$get_module_instance_by_name", "name is NULL");
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

    $log_debug(DEBUG_LEVEL_MEDIUM, "_initialize_default_modules", "Initializing default modules");

    $modules[0] = _create_os_icon_module();
    $modules[1] = _create_user_module();
    $modules[2] = _create_hostname_module();
    $modules[3] = _create_cwd_module();
    $modules[4] = _create_git_module();
    $modules[5] = _create_time_module();
    $modules[6] = _create_exit_status_module();
}

static void _initialize_default_containers() {
    $log_debug(DEBUG_LEVEL_MEDIUM, "_initialize_default_containers",
               "Initializing default containers");

    struct container_style_t default_container_style = _create_default_container_style();

    char *user_modules[] = {"user", "hostname"};
    char *cwd_modules[] = {"cwd", "git"};
    char *time_modules[] = {"time"};

    $containers[0] = $create_promptorium_container(user_modules, 2, "user", default_container_style,
                                                   DEFAULT_MODULE_SEPARATOR);
    $containers[1] = $create_promptorium_container(cwd_modules, 2, "cwd", default_container_style,
                                                   DEFAULT_MODULE_SEPARATOR);
    $containers[2] = $create_promptorium_container(time_modules, 1, "time", default_container_style,
                                                   DEFAULT_MODULE_SEPARATOR);
};

struct config_t $create_default_config() {

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

    $log_debug(DEBUG_LEVEL_MAX, "_set_global_color", "Setting color: %s", color_name);

    if (strcmp(color_name, "green") == 0) {
        color->background_code = COLOR_GREEN.background_code;
        color->foreground_code = COLOR_GREEN.foreground_code;
        return;
    } else if (strcmp(color_name, "red") == 0) {
        color->background_code = COLOR_RED.background_code;
        color->foreground_code = COLOR_RED.foreground_code;
        return;
    } else if (strcmp(color_name, "yellow") == 0) {
        color->background_code = COLOR_YELLOW.background_code;
        color->foreground_code = COLOR_YELLOW.foreground_code;
        return;
    } else if (strcmp(color_name, "blue") == 0) {
        color->background_code = COLOR_BLUE.background_code;
        color->foreground_code = COLOR_BLUE.foreground_code;
        return;
    } else if (strcmp(color_name, "magenta") == 0) {
        color->background_code = COLOR_MAGENTA.background_code;
        color->foreground_code = COLOR_MAGENTA.foreground_code;
        return;
    } else if (strcmp(color_name, "cyan") == 0) {
        color->background_code = COLOR_CYAN.background_code;
        color->foreground_code = COLOR_CYAN.foreground_code;
        return;
    } else if (strcmp(color_name, "white") == 0) {
        color->background_code = COLOR_WHITE.background_code;
        color->foreground_code = COLOR_WHITE.foreground_code;
        return;
    } else if (strcmp(color_name, "black") == 0) {
        color->background_code = COLOR_BLACK.background_code;
        color->foreground_code = COLOR_BLACK.foreground_code;
        return;
    }

    $log_debug(DEBUG_LEVEL_MIN, "_set_global_color", "Invalid color name: %s", color_name);
}

static void _parse_global_style(struct config_t *config, cJSON *style) {

    $log_debug(DEBUG_LEVEL_MEDIUM, "_parse_global_style", "Parsing global style");

    // Set dividers and padding
    cJSON *container_start_divider = cJSON_GetObjectItem(style, "container_start_divider");
    cJSON *container_end_divider = cJSON_GetObjectItem(style, "container_end_divider");
    cJSON *container_padding = cJSON_GetObjectItem(style, "container_padding");
    cJSON *container_spacer = cJSON_GetObjectItem(style, "container_spacer");
    cJSON *module_separator = cJSON_GetObjectItem(style, "module_separator");
    cJSON *module_padding = cJSON_GetObjectItem(style, "module_padding");

    if (container_start_divider != NULL) {
        config->global_style.container_start_divider = container_start_divider->valuestring;
    }
    if (container_end_divider != NULL) {
        config->global_style.container_end_divider = container_end_divider->valuestring;
    }
    if (container_padding != NULL) {
        config->global_style.container_padding = container_padding->valuestring;
    }
    if (container_spacer != NULL) {
        config->global_style.container_spacer = container_spacer->valuestring;
    }
    if (module_separator != NULL) {
        config->global_style.module_separator = module_separator->valuestring;
    }
    if (module_padding != NULL) {
        config->global_style.module_padding = module_padding->valuestring;
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

static void _parse_config_json(struct config_t *config, char *config_file_content) {
    $log_debug(DEBUG_LEVEL_MEDIUM, "_parse_config_json", "Parsing config from JSON");
    cJSON *json = cJSON_Parse(config_file_content);
    if (json == NULL) {
        $throw_error("_parse_config_json : cJSON_Parse", "Failed to parse JSON");
    }

    // Parse version
    config->version = cJSON_GetObjectItem(json, "version")->valuestring;

    // Parse global style
    cJSON *global_style = cJSON_GetObjectItem(json, "style");
    if (global_style != NULL) {
        _parse_global_style(config, global_style);
    }

    cJSON_Delete(json);
}

void $set_config_from_json(struct config_t *config, char *config_file_content) {
    $log_debug(DEBUG_LEVEL_MEDIUM, "$set_config_from_json", "Setting config from JSON");
    _parse_config_json(config, config_file_content);
}

// Debug functions

void $debug_config(struct config_t *config) {
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Version: %s", config->version);
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Global style:");
    $log_debug(DEBUG_LEVEL_MEDIUM, "$debug_config", "Container start divider: %s",
               config->global_style.container_start_divider);
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
