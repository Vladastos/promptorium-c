#include "prompt.h"

static char *_PROMPT_build_prompt(char* prompt, struct config_t config) {

    // TODO: Implement this
}
void $PROMPT_print() {

    struct config_t config = $CONFIG_create_default_config();

    $CONFIG_set_config_from_file(&config);

    $CONFIG_debug_config(&config);
    
    char *prompt = malloc(256);
    if (prompt == NULL) {
        $UTILS_throw_error("$PROMPT_print : malloc", "Failed to allocate memory");
    }

    _PROMPT_build_prompt(prompt , config);
}
