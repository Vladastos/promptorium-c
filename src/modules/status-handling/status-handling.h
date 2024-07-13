#ifndef STATUS_HANDLING_H
#define STATUS_HANDLING_H

#include <stdio.h>

#define STATUS_OK 0
#define STATUS_GENERIC_ERROR 1

typedef struct {
    int code;
    char *function_name;
    char *message;
} status_t;

status_t init_status(char *name);

int handle_status(status_t *status);

#endif