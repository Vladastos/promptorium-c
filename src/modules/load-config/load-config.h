#ifndef CREATE_DAEMON_H
#define CREATE_DAEMON_H

#include "../status-handling/status-handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>

int load_config();

int get_key();

#endif