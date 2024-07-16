#ifndef SHARED_MEMORY_MANAGEMENT_H
#define SHARED_MEMORY_MANAGEMENT_H

#include "../common-modules.h"
#include "../utils/definitions.h"

int $memory_write_segment(int ipc_key, struct config *config);

int $memory_read_segment(int ipc_key, struct config *config);

void $memory_create_segment(int ipc_key, int ipc_size, int permissions);

int $memory_cleanup_segment();

char *_memory_attach_segment(int ipc_key);

int _memory_detach_segment(char *shm);

#endif