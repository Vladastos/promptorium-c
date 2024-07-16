#include "get-prompt.h"

char *get_prompt() {
    struct config config;

    log_debug("get_prompt", "Reading config from shared memory");
    char *shm = attach_shared_memory_segment(get_key_variable());
    read_config_from_shared_memory_segment(shm, &config);
    detach_shared_memory_segment(shm);

    return "$ \n";
}