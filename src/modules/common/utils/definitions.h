#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PROMPTORIUM_VERSION "0.0.2"

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_DEBUG 3

#define CONFIG_FILE_NAME "promptorium.conf"
#define CONFIG_FILE_DIR "/home/vlad/Documents/promptorium-c/conf"
#define CONFIG_FILE_PATH CONFIG_FILE_DIR "/" CONFIG_FILE_NAME

struct config {
    int SHOW_GIT_STATUS;
    int SHOW_HOST;
    int SHOW_HOME_ICON;
    int SHOW_BOOKMARK_ICON;
    int SHOW_EXIT_ICON;
    int SHOW_TIME;
};

#endif