#include "print-prompt.h"

static char *_build_directory_module() {
    // get the current working directory
    size_t size = 256;
    char *cwd = malloc(size);
    if (cwd == NULL) {
        $UTILS_throw_error("build_directory_module : malloc", "Failed to allocate memory");
    }

    // Get the current working directory
    while (getcwd(cwd, size) == NULL) {

        // If the error is ERANGE, it means the buffer was too small
        // and we need to allocate a larger buffer and try again

        if (errno != ERANGE) {
            free(cwd);
            $UTILS_throw_error("build_directory_module : getcwd",
                               "Failed to get current working directory");
            return NULL;
        }
        size *= 2;
        cwd = realloc(cwd, size);
        if (cwd == NULL) {
            $UTILS_throw_error("build_directory_module : realloc", "Failed to allocate memory");
        }
    }

    return cwd;
}

static char *_build_prompt() {

    char *cwd = _build_directory_module();
    if (cwd == NULL) {
        $UTILS_throw_error("_build_prompt : malloc", "Failed to allocate memory");
    }

    char *prompt = malloc(256);

    if (prompt == NULL) {
        free(cwd);
        $UTILS_throw_error("_build_prompt : malloc", "Failed to allocate memory");
    }

    snprintf(prompt, 256, "%s > $", cwd);
    free(cwd);
    return prompt;
}

char *print_prompt() {

    struct config_t config = $CONFIG_create_default_config();

    $CONFIG_set_config_from_file(&config);

    $CONFIG_debug_config(&config);
    
    char* prompt;



    return 0;
}
