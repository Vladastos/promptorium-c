#ifndef MAIN_H
#define MAIN_H
#include "modules/application/application.h"
#include "modules/common/common-modules.h"
#include "modules/common/utils/definitions.h"

int $debug_mode = DEBUG_MODE;

char *$log_file_path = LOG_FILE_PATH;

int main(int argc, char *argv[]);

#endif
