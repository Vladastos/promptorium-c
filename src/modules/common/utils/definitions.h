#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PROMPTORIUM_VERSION "0.0.3"

// Debug and logging constants

#define DEBUG_LEVEL_OFF 0
#define DEBUG_LEVEL_MIN 1
#define DEBUG_LEVEL_MEDIUM 2
#define DEBUG_LEVEL_MAX 3

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_DEBUG 3

#define LOG_FILE_NAME "promptorium.log"
#define LOG_FILE_DIR "/home/vlad/Documents/promptorium-c/shell"
#define LOG_FILE_PATH LOG_FILE_DIR "/" LOG_FILE_NAME

#define IPC_KEY_VARIABLE_NAME "PROMPTORIUM_IPC_KEY"

#define CONFIG_FILE_NAME "promptorium.conf.json"
#define CONFIG_FILE_DIR "/home/vlad/Documents/promptorium-c/conf"
#define CONFIG_FILE_PATH CONFIG_FILE_DIR "/" CONFIG_FILE_NAME

//
// Style constants and config
//

#define MAX_MODULES 10
#define MAX_CONTAINERS 10
#define AVAILABLE_MODULES \
    {"os_icon", "username", "hostname", "cwd", "git", "time", "exit_status"}
#define AVAILABLE_MODULES_LENGTH 7

// Defaults styles

#define DEFAULT_CONTAINER_START_DIVIDER ""
#define DEFAULT_CONTAINER_END_DIVIDER ""
#define DEFAULT_CONTAINER_PADDING " "
#define DEFAULT_CONTAINER_SPACER "─"
#define DEFAULT_MODULE_SEPARATOR ""
#define DEFAULT_MODULE_PADDING " "

struct color_t {
    char *foreground_code;
    char *background_code;
};

struct global_style_t {
    char *container_start_divider;
    char *container_end_divider;
    char *container_padding;
    char *container_spacer;
    char *module_separator;
    char *module_padding;
    struct color_t *primary_color;
    struct color_t *secondary_color;
    struct color_t *tertiary_color;
    struct color_t *quaternary_color;
    struct color_t *success_color;
    struct color_t *warning_color;
    struct color_t *error_color;
};

struct module_style_t {
    struct color_t *background_color;
    struct color_t *foreground_color;
};

struct icon_style_t {
    struct color_t *background_color;
    struct color_t *foreground_color;
    char *separator;
};

struct module_t {
    char *name;
    char *icon;
    struct module_style_t *style;
    struct icon_style_t *icon_style;
};

struct container_style_t {
    struct color_t *background_color;
    struct color_t *foreground_color;
    char *separator;
    char *start_divider;
    char *end_divider;
};

struct promptorium_container_t {
    char *name;
    struct container_style_t *style;
    struct module_t *modules[MAX_MODULES];
    char *modules_separator;
};

struct config_t {
    char *version;
    struct global_style_t *global_style;
    struct promptorium_container_t *containers[MAX_CONTAINERS];
    struct module_t *modules[AVAILABLE_MODULES_LENGTH];
};

#endif
