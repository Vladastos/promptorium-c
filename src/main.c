#include "main.h"

static void _MAIN_exit_handler() {

    // free all unallocated memory
    $CONFIG_free_config();

    // calculate program execution time
    int elapsed_time = (int)(clock() * 1000 / CLOCKS_PER_SEC);
    $LOG_debug(DEBUG_LEVEL_MAX, "_MAIN_exit_handler", "Program execution time: %d ms", elapsed_time);
}

int main(int argc, char *argv[]) {

    atexit(_MAIN_exit_handler);

    return $APPLICATION_run(argc, argv);
}
