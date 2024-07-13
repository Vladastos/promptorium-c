#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "modules/status-handling/status-handling.h"
#include "modules/print-help/print-help.h"
#include "modules/print-version/print-version.h"
#include "modules/load-config/load-config.h"

#define VERSION "0.0.1"

int main(int argc, char *argv[]);