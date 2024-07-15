#include "init-config.h"

struct config get_default_config() {
    struct config default_config = {.SHOW_GIT_STATUS = 1,
                                    .SHOW_HOST = 1,
                                    .SHOW_HOME_ICON = 1,
                                    .SHOW_BOOKMARK_ICON = 1,
                                    .SHOW_EXIT_ICON = 1,
                                    .SHOW_TIME = 1};
    return default_config;
}

struct config get_config_from_file() {
    log_debug("get_config_from_file", "Getting default config");

    struct config default_config = get_default_config();

    log_debug("get_config_from_file", "Reading config from file");
    log_debug("get_config_from_file", CONFIG_FILE_PATH);
    FILE *fp = fopen(CONFIG_FILE_PATH, "r");

    if (fp == NULL) {
        on_error("read_config_from_file : fopen", "Failed to open config file");
    } else {
        // read the config
        char line[1024];
        while (fgets(line, 1024, fp) != NULL) {
            log_debug("read_config_from_file", line);
            // TODO: parse the config
        }
        // close the file
        fclose(fp);
    }

    return default_config;
}

int init_config() {

    log_debug("init_config", "Initializing config");

    // create the shared memory segment
    int shmid = create_shared_memory_segment(1024, IPC_CREAT | 0666);

    // attach the shared memory segment
    char *shm = attach_shared_memory_segment(shmid);

    // TODO: load configuration from file

    read_config_from_file();

    detach_shared_memory_segment(shm);

    return 0;
}
