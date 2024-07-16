#ifndef SHARED_MEMORY_MANAGEMENT_H
#define SHARED_MEMORY_MANAGEMENT_H

#include "../common-modules.h"
#include "../utils/definitions.h"

int create_shared_memory_segment(int key, int size, int permissions);

char *attach_shared_memory_segment(int key);

int detach_shared_memory_segment(char *shm);

int write_config_to_shared_memory_segment(char *shm, struct config *config);

int read_config_from_shared_memory_segment(char *shm, struct config *config);

int cleanup_shared_memory_segment();

#endif