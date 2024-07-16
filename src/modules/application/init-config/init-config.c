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

void get_config_from_file(struct config *default_config) {

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

    return;
}

int init_config() {

    log_debug("init_config", "Initializing config");

    struct config default_config = get_default_config();

    log_debug("init_config", "Getting key variable");
    int key = get_key_variable();

    log_debug("init_config", "Creating shared memory segment");
    // create the shared memory segment
    int shmid = create_shared_memory_segment(key, 1024, IPC_CREAT | 0666);

    log_debug("init_config", "Attaching shared memory segment");
    // attach the shared memory segment
    char *shm = attach_shared_memory_segment(shmid);

    // TODO: load configuration from file

    log_debug("get_config_from_file", "Reading config from file");
    get_config_from_file(&default_config);

    log_debug("init_config", "Writing config to shared memory segment");
    // write the config to the shared memory segment
    write_config_to_shared_memory_segment(shm, &default_config);

    log_debug("init_config", "Detaching shared memory segment");
    detach_shared_memory_segment(shm);

    return 0;
}
