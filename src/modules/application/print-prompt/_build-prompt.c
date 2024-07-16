#include "_build-prompt.h"

char *_build_prompt() {

    char *cwd = _build_directory_module();
    if (cwd == NULL) {
        throw_error("build_prompt : malloc", "Failed to allocate memory");
    }
    char *prompt = malloc(256);
    if (prompt == NULL) {
        free(cwd);
        throw_error("build_prompt : malloc", "Failed to allocate memory");
    }
    snprintf(prompt, 256, "%s > $", cwd);
    free(cwd);
    return prompt;
}

char *_build_directory_module() {
    // get the current working directory
    size_t size = 256;
    char *cwd = malloc(size);
    if (cwd == NULL) {
        throw_error("build_directory_module : malloc", "Failed to allocate memory");
    }

    // Get the current working directory
    while (getcwd(cwd, size) == NULL) {

        // If the error is ERANGE, it means the buffer was too small
        // and we need to allocate a larger buffer and try again

        if (errno != ERANGE) {
            free(cwd);
            throw_error("build_directory_module : getcwd",
                        "Failed to get current working directory");
            return NULL;
        }
        size *= 2;
        cwd = realloc(cwd, size);
        if (cwd == NULL) {
            throw_error("build_directory_module : realloc", "Failed to allocate memory");
        }
    }

    return cwd;
}