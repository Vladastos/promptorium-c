#ifndef CONFIG_MANAGEMENT_H
#define CONFIG_MANAGEMENT_H

#include "../common-modules.h"

// Getters and setters

struct config_t *$get_config();

void $set_config(struct config_t *new_config);

struct module_t **$get_modules();

void $set_modules(struct module_t *new_modules[]);

struct module_t *$get_module_by_name(char *name);

void $set_module_by_name(struct module_t *new_module, char *name);

struct promptorium_container_t **$get_containers();

void $set_containers(struct promptorium_container_t *new_containers[]);

// Functions for container creation

struct promptorium_container_t
$create_promptorium_container(char *module_names[], int num_modules, char *container_name,
                              struct container_style_t container_style, char *modules_separator);

// Functions for initializing configuration with default values

struct config_t $create_default_config();

void $debug_config(struct config_t *config);

#endif