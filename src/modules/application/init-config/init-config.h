#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H

#include "../../common/common-modules.h"

int init_config();

void _get_config_from_file(struct config_t *config);

void _parse_config_line(char *line, struct config_t *config);

struct config_t _get_default_config();

#endif