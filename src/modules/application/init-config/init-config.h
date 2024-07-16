#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H

#include "../../common/common-modules.h"

int init_config();

void _get_config_from_file(struct config *config);

void _parse_config_line(char *line, struct config *config);

struct config _get_default_config();

#endif