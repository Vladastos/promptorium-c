#ifndef CONFIG_MANAGEMENT_H
#define CONFIG_MANAGEMENT_H

#include "../common-modules.h"

// Getters and setters

struct module_t *$get_module_instance_by_name(char *name);

// Functions for container creation

struct promptorium_container_t
$create_promptorium_container(char *module_names[], int num_modules, char *container_name,
                              struct container_style_t container_style, char *modules_separator);

// Functions for initializing configuration with default values

struct config_t $create_default_config();

void $debug_config(struct config_t *config);

#endif