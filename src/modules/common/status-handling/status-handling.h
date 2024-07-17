#ifndef STATUS_HANDLING_H
#define STATUS_HANDLING_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"

void $throw_error(char *function_name, char *message);

#endif