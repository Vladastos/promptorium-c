#include "utils.h"
#include "definitions.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

void $UTILS_debug_args(int argc, char *argv[]) {
    $LOG_debug(DEBUG_LEVEL_MAX, "$UTILS_debug_args", "Arguments: %d", argc);
    for (int i = 0; argv[i] != NULL; i++) {
        $LOG_debug(DEBUG_LEVEL_MAX, "$UTILS_debug_args", "Arg %d: %s", i, argv[i]);
    }
    return;
}

char *$UTILS_get_file_content(char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    $LOG_debug(DEBUG_LEVEL_MEDIUM, "__read_json_file", "File length: %ld", length);
    char *buffer = malloc(length + 1);
    if (buffer == NULL) {
        fclose(fp);
        return NULL;
    }
    fread(buffer, 1, length, fp);
    fclose(fp);
    buffer[length] = '\0';
    return buffer;
}

void $UTILS_throw_error(char *function_name, char *message, ...) {
    va_list args;
    va_start(args, message);
    $LOG_error(function_name, message, args);
    if (errno != 0) {
        $LOG_error(function_name, strerror(errno), args);
    }
    va_end(args);
    exit(1);
}