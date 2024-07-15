#ifndef STATUS_HANDLING_H
#define STATUS_HANDLING_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void on_error(char *function_name, char *message);

#endif