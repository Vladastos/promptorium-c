#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "modules/common/common-modules.h"
#include "modules/application/application-modules.h"

#define VERSION "0.0.2"

int main(int argc, char *argv[]);