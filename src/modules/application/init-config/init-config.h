#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H

#include "../../common/common-modules.h"

int init_config();

int read_config_from_file();

struct config get_default_config();

#endif