#include "colors.h"

struct color_t COLOR_BLACK = {"black", "\033[30m", "\033[40m"};
struct color_t COLOR_RED = {"red", "\033[31m", "\033[41m"};
struct color_t COLOR_GREEN = {"green", "\033[32m", "\033[42m"};
struct color_t COLOR_YELLOW = {"yellow", "\033[33m", "\033[43m"};
struct color_t COLOR_BLUE = {"blue", "\033[34m", "\033[44m"};
struct color_t COLOR_MAGENTA = {"magenta", "\033[35m", "\033[45m"};
struct color_t COLOR_CYAN = {"cyan", "\033[36m", "\033[46m"};
struct color_t COLOR_WHITE = {"white", "\033[37m", "\033[47m"};
struct color_t COLOR_RESET = {"reset", "\033[0m", "\033[0m"};

struct color_t *$colors[] = {&COLOR_BLACK,   &COLOR_RED,  &COLOR_GREEN, &COLOR_YELLOW, &COLOR_BLUE,
                             &COLOR_MAGENTA, &COLOR_CYAN, &COLOR_WHITE, &COLOR_RESET};
int AVAILABLE_COLORS_LENGTH = sizeof($colors) / sizeof($colors[0]);

struct color_t *DEFAULT_PRIMARY_COLOR = &COLOR_BLUE;
struct color_t *DEFAULT_SECONDARY_COLOR = &COLOR_GREEN;
struct color_t *DEFAULT_TERTIARY_COLOR = &COLOR_MAGENTA;
struct color_t *DEFAULT_QUATERNARY_COLOR = &COLOR_CYAN;
struct color_t *DEFAULT_SUCCESS_COLOR = &COLOR_GREEN;
struct color_t *DEFAULT_WARNING_COLOR = &COLOR_YELLOW;
struct color_t *DEFAULT_ERROR_COLOR = &COLOR_RED;

struct color_t *DEFAULT_BACKGROUND_COLOR = &COLOR_BLACK;
struct color_t *DEFAULT_FOREGROUND_COLOR = &COLOR_WHITE;
