#include "print-prompt.h"

char *print_prompt() {

    struct config config;

    $log_debug(DEBUG_LEVEL_MAX, "get_prompt", "Reading config from shared memory");

    int ipc_key = $get_ipc_key();

    $memory_read_segment(ipc_key, &config);

    $debug_config(&config);

    // TODO: return the prompt

    return 0;
}