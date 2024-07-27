#ifndef SHARED_MEMORY_MANAGEMENT_H
#define SHARED_MEMORY_MANAGEMENT_H

#include "../common-modules.h"
#include "../utils/definitions.h"

int $MEMORY_get_ipc_key();

int $MEMORY_write_segment(int ipc_key, char *config_file_content);

int $MEMORY_read_segment(int ipc_key, char *config_file_content);

void $MEMORY_create_segment(int ipc_key, int ipc_size, int permissions);

int $MEMORY_clear_segment();

#endif