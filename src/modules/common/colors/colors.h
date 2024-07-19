#ifndef COLORS_H
#define COLORS_H

#include "definitions.h"

static struct color_t COLOR_BLACK = {"\033[30m", "\033[40m"};
static struct color_t COLOR_RED = {"\033[31m", "\033[41m"};
static struct color_t COLOR_GREEN = {"\033[32m", "\033[42m"};
static struct color_t COLOR_YELLOW = {"\033[33m", "\033[43m"};
static struct color_t COLOR_BLUE = {"\033[34m", "\033[44m"};
static struct color_t COLOR_MAGENTA = {"\033[35m", "\033[45m"};
static struct color_t COLOR_CYAN = {"\033[36m", "\033[46m"};
static struct color_t COLOR_WHITE = {"\033[37m", "\033[47m"};
static struct color_t COLOR_RESET = {"\033[0m", "\033[0m"};

static struct color_t *DEFAULT_PRIMARY_COLOR = &COLOR_BLUE;
static struct color_t *DEFAULT_SECONDARY_COLOR = &COLOR_GREEN;
static struct color_t *DEFAULT_TERTIARY_COLOR = &COLOR_MAGENTA;
static struct color_t *DEFAULT_QUATERNARY_COLOR = &COLOR_CYAN;
static struct color_t *DEFAULT_SUCCESS_COLOR = &COLOR_GREEN;
static struct color_t *DEFAULT_WARNING_COLOR = &COLOR_YELLOW;
static struct color_t *DEFAULT_ERROR_COLOR = &COLOR_RED;
#endif
