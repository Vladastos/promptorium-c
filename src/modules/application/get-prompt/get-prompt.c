#include "get-prompt.h"

char *get_prompt() {
    struct config config;

    log_debug("get_prompt", "Reading config from shared memory");
    int ipc_key = get_key_variable();
    read_config_from_shared_memory_segment(ipc_key, &config);

    return "$ \n";
}