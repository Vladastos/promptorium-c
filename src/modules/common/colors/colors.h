#ifndef COLORS_H
#define COLORS_H

#include "../utils/definitions.h"

extern struct color_t COLOR_BLACK;
extern struct color_t COLOR_RED;
extern struct color_t COLOR_GREEN;
extern struct color_t COLOR_YELLOW;
extern struct color_t COLOR_BLUE;
extern struct color_t COLOR_MAGENTA;
extern struct color_t COLOR_CYAN;
extern struct color_t COLOR_WHITE;
extern struct color_t COLOR_RESET;

extern struct color_t *$colors[];
extern int AVAILABLE_COLORS_LENGTH;

extern struct color_t *DEFAULT_PRIMARY_COLOR;
extern struct color_t *DEFAULT_SECONDARY_COLOR;
extern struct color_t *DEFAULT_TERTIARY_COLOR;
extern struct color_t *DEFAULT_QUATERNARY_COLOR;
extern struct color_t *DEFAULT_SUCCESS_COLOR;
extern struct color_t *DEFAULT_WARNING_COLOR;
extern struct color_t *DEFAULT_ERROR_COLOR;
extern struct color_t *DEFAULT_BACKGROUND_COLOR;
extern struct color_t *DEFAULT_FOREGROUND_COLOR;

#endif
