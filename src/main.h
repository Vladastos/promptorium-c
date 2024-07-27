#ifndef MAIN_H
#define MAIN_H
#include "modules/application/application.h"
#include "modules/common/common-modules.h"
#include "modules/common/utils/definitions.h"

int $GLOBAL_debug_level = DEBUG_LEVEL_OFF;

char *$GLOBAL_log_file_path = LOG_FILE_PATH;

char *$GLOBAL_config_file_path = CONFIG_FILE_PATH;

int main(int argc, char *argv[]);

#endif
