#include "print-prompt.h"

static void _set_config_from_file(struct config_t *config) {
    char *config_file_path = CONFIG_FILE_PATH;
    char *config_file_content = $get_file_content(config_file_path);

    if (config_file_content == NULL) {
        $throw_error("_get_config_from_file : _read_json_file", "Failed to read config file");
    }

    $set_config_from_json(config, config_file_content);

    $free_config();
}

static char *_build_directory_module() {
    // get the current working directory
    size_t size = 256;
    char *cwd = malloc(size);
    if (cwd == NULL) {
        $throw_error("build_directory_module : malloc", "Failed to allocate memory");
    }

    // Get the current working directory
    while (getcwd(cwd, size) == NULL) {

        // If the error is ERANGE, it means the buffer was too small
        // and we need to allocate a larger buffer and try again

        if (errno != ERANGE) {
            free(cwd);
            $throw_error("build_directory_module : getcwd",
                         "Failed to get current working directory");
            return NULL;
        }
        size *= 2;
        cwd = realloc(cwd, size);
        if (cwd == NULL) {
            $throw_error("build_directory_module : realloc", "Failed to allocate memory");
        }
    }

    return cwd;
}

static char *_build_prompt() {

    char *cwd = _build_directory_module();
    if (cwd == NULL) {
        $throw_error("_build_prompt : malloc", "Failed to allocate memory");
    }

    char *prompt = malloc(256);

    if (prompt == NULL) {
        free(cwd);
        $throw_error("_build_prompt : malloc", "Failed to allocate memory");
    }

    snprintf(prompt, 256, "%s > $", cwd);
    free(cwd);
    return prompt;
}

char *print_prompt() {

    struct config_t config = $create_default_config();
    _set_config_from_file(&config);

    $debug_config(&config);

    // TODO: return the prompt

    return 0;
}
