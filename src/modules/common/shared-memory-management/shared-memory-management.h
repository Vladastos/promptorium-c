#ifndef SHARED_MEMORY_MANAGEMENT_H
#define SHARED_MEMORY_MANAGEMENT_H

#include "../common-modules.h"
#include "../utils/definitions.h"

int write_config_to_shared_memory_segment(int ipc_key, struct config *config);

int read_config_from_shared_memory_segment(int ipc_key, struct config *config);

void create_shared_memory_segment(int ipc_key, int ipc_size, int permissions);

int cleanup_shared_memory_segment();

char *attach_shared_memory_segment(int ipc_key);

int detach_shared_memory_segment(char *shm);

#endif