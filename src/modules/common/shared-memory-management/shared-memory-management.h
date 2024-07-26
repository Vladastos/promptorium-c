#ifndef SHARED_MEMORY_MANAGEMENT_H
#define SHARED_MEMORY_MANAGEMENT_H

#include "../common-modules.h"
#include "../utils/definitions.h"

int $get_ipc_key();

int $memory_write_segment(int ipc_key, char *config_file_content);

int $memory_read_segment(int ipc_key, char *config_file_content);

void $memory_create_segment(int ipc_key, int ipc_size, int permissions);

int $memory_cleanup_segment();

#endif