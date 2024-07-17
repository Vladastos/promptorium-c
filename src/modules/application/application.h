#ifndef APPLICATION_H
#define APPLICATION_H

#include "../common/common-modules.h"
#include "init-config/init-config.h"
#include "print-prompt/print-prompt.h"

int run_application(int argc, char *argv[]);

void _print_version();

void _print_help();

void _parse_command(int argc, char *argv[]);

int _parse_global_args(int argc, char *argv[]);

int _parse_application_args(int argc, char *argv[]);

void __debug_args(int argc, char *argv[]);

#endif
