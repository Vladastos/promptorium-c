#include "create-default-config.h"

/*
    This module creates the default configuration for the init-config module.

    It returns a struct config_t with the default configuration.

    The logic behind the promptorium configuration is the following:

    1. Create the default modules

        There are 7 modules: os_icon, user, hostname, cwd, git, time, exit_status
        Each module has its own style and icon style.

        If the user defines a module that is not in the list, it is ignored.

        Containers can only hold pointers to modules.

    2. Create the default containers

        A container is an aggregate of modules.

        The user can define up to 10 containers in the configuration, each with its own style.
        The default containers are: user_container, cwd_container


    3. Create the default config

        The default config has 7 modules and 2 containers.

*/

/*

    Logic for creating the default modules

*/
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

static struct module_t *_create_default_modules() {

    struct module_t *modules = malloc(sizeof(struct module_t) * AVAILABLE_MODULES_LENGTH);

    modules[0] = _create_os_icon_module();
    modules[1] = _create_user_module();
    modules[2] = _create_hostname_module();
    modules[3] = _create_cwd_module();
    modules[4] = _create_git_module();
    modules[5] = _create_time_module();
    modules[6] = _create_exit_status_module();

    return modules;
};

// Get a module by name
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

static void ___debug_modules(struct module_t *modules) {
    for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
        if (modules[i].name != NULL) {
            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Module: %s", modules[i].name);
            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Module icon: %s", modules[i].icon);
            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Module style:");
            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Background color: %s",
                       modules[i].style.background_color->background_code);
            printf("%s", COLOR_RESET.background_code);
            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Foreground color: %s",
                       modules[i].style.foreground_color->background_code);
            printf("%s", COLOR_RESET.background_code);
            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Icon style:");
            printf("%s", COLOR_RESET.background_code);
            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Background color: %s",
                       modules[i].icon_style.background_color->background_code);
            printf("%s", COLOR_RESET.background_code);

            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Foreground color: %s",
                       modules[i].icon_style.foreground_color->background_code);
            printf("%s", COLOR_RESET.background_code);

            $log_debug(DEBUG_LEVEL_MEDIUM, "___debug_modules", "Icon style separator: %s",
                       modules[i].icon_style.separator);
            printf("%s", COLOR_RESET.background_code);
        }
    }
}

/*

    Logic for creating the default containers

*/

static struct promptorium_container_t *
_initialize_promptorium_container(struct module_t *modules, char *module_names[], int num_modules,
                                  char *container_name, struct container_style_t container_style,
                                  char *modules_separator) {
    struct promptorium_container_t *promptorium_container =
        malloc(sizeof(struct promptorium_container_t));

    promptorium_container->name = container_name;
    promptorium_container->style = container_style;
    promptorium_container->modules_separator = modules_separator;
    for (int i = 0; i < num_modules; i++) {
        promptorium_container->modules[i] = _get_module_by_name(module_names[i], modules);
    }
    return promptorium_container;
}
struct config_t create_default_config() {

    // $log_debug(DEBUG_LEVEL_MEDIUM, "create_default_config", "Creating default modules");

    // struct module_t *modules = _create_default_modules();

    // $log_debug(DEBUG_LEVEL_MEDIUM, "create_default_config", "Default modules created");

    // $log_debug(DEBUG_LEVEL_MEDIUM, "create_default_config", "Creating default containers");

    // struct promptorium_container_t *containers = _create_default_promptorium_containers();

    // $log_debug(DEBUG_LEVEL_MEDIUM, "create_default_config", "Default containers created");

    struct config_t default_config = {.version = PROMPTORIUM_VERSION,
                                      .global_style = _create_default_global_style()};

    // for (int i = 0; i < AVAILABLE_MODULES_LENGTH; i++) {
    //     $log_debug(DEBUG_LEVEL_MAX, "create_default_config", "Module: %s", modules[i].name);
    //     $log_debug(DEBUG_LEVEL_MAX, "create_default_config", "Module icon: %s", modules[i].icon);
    //     default_config.modules[i] = modules[i];
    // }

    // for (int i = 0; i < MAX_CONTAINERS; i++) {
    //     $log_debug(DEBUG_LEVEL_MAX, "create_default_config", "Container: %s",
    //     containers[i].name); default_config.containers[i] = containers[i];
    // }

    // $log_debug(DEBUG_LEVEL_MEDIUM, "create_default_config", "Default config created");

    return default_config;
}