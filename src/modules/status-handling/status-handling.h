#ifndef STATUS_HANDLING_H
#define STATUS_HANDLING_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void on_error(char *function_name, char *message);

#endif