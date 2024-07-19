#ifndef COMMON_H
#define COMMON_H

#include <ctype.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <json-c/json.h>
#include <time.h>
#include <unistd.h>

#include "error-management/error-management.h"
#include "log-management/log-management.h"
#include "shared-memory-management/shared-memory-management.h"
#include "utils/definitions.h"
#include "utils/utils.h"

#endif
