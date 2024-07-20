#include "create-default-config.h"
static struct module_t *_create_default_modules() {

    struct module_t *modules =
        (struct module_t *)calloc(AVAILABLE_MODULES_LENGTH, sizeof(struct module_t));

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

    modules[0] = user;
    modules[1] = cwd;
    modules[2] = os_icon;
    modules[3] = hostname;
    modules[4] = git;
    modules[5] = time;
    modules[6] = exit_status;
    return modules;
};

static struct module_t *_get_module_by_name(char *name, struct module_t *modules) {

    for (int i = 0; i < MAX_MODULES; i++) {
        if (strcmp(modules[i].name, name) == 0) {
            $log_debug(DEBUG_LEVEL_MAX, "_get_module_by_name", "Module: %s", modules[i].name);
            $log_debug(DEBUG_LEVEL_MAX, "_get_module_by_name", "Module icon: %s", modules[i].icon);
            return &modules[i];
        }
    }
    return NULL;
}

static struct global_style_t *_create_default_global_style() {
    struct global_style_t *default_global_style =
        (struct global_style_t *)calloc(1, sizeof(struct global_style_t));
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
}

static struct promptorium_container_t *
_create_default_containers(struct module_t *modules,
                           struct container_style_t *default_container_style) {

    struct promptorium_container_t *containers = (struct promptorium_container_t *)calloc(
        MAX_CONTAINERS, sizeof(struct promptorium_container_t));

    struct module_t *user_container_modules = {_get_module_by_name("user", modules),
                                               _get_module_by_name("hostname", modules)};

    struct module_t *cwd_container_modules = {_get_module_by_name("cwd", modules),
                                              _get_module_by_name("git", modules)};

    struct module_t *exit_container_modules = {_get_module_by_name("time", modules),
                                               _get_module_by_name("exit_status", modules)};

    struct promptorium_container_t user_container = {.name = "user_container",
                                                     .modules = user_container_modules,
                                                     .style = default_container_style};

    struct promptorium_container_t cwd_container = {.name = "cwd_container",
                                                    .modules = cwd_container_modules,
                                                    .style = default_container_style};

    struct promptorium_container_t exit_container = {.name = "exit_container",
                                                     .modules = exit_container_modules,
                                                     .style = default_container_style};

    containers[0] = user_container;
    containers[1] = cwd_container;
    containers[2] = exit_container;

    return containers;
}

static struct config_t _create_default_config() {

    struct module_t *modules = _create_default_modules();

    struct global_style_t *default_global_style = _create_default_global_style();

    struct container_style_t default_container_style = _create_default_container_style();

    struct promptorium_container_t *default_containers =
        _create_default_containers(modules, &default_container_style);

    struct config_t default_config = {.global_style = default_global_style,
                                      .containers = default_containers,
                                      .modules = modules};

    return default_config;
}

struct config_t create_default_config() {

    $log_debug(DEBUG_LEVEL_MEDIUM, "create_default_config", "Creating default config");

    return _create_default_config();
}