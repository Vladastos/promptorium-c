#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PROMPTORIUM_VERSION "0.0.2"

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

#define CONFIG_FILE_NAME "promptorium.conf"
#define CONFIG_FILE_DIR "/home/vlad/Documents/promptorium-c/conf"
#define CONFIG_FILE_PATH CONFIG_FILE_DIR "/" CONFIG_FILE_NAME

// Structures
struct config_t {
    int SHOW_GIT_STATUS;
    int SHOW_HOST;
    int SHOW_HOME_ICON;
    int SHOW_BOOKMARK_ICON;
    int SHOW_EXIT_ICON;
    int SHOW_TIME;
    int SHOW_DATE;
    int GIT_AUTO_FETCH;
};

#endif
