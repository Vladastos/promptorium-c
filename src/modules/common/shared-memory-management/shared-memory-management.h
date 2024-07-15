#ifndef SHARED_MEMORY_MANAGEMENT_H
#define SHARED_MEMORY_MANAGEMENT_H

#include "../common-modules.h"

int create_shared_memory_segment(int size, int permissions);

char *attach_shared_memory_segment(int shmid);

int detach_shared_memory_segment(char *shm);

int write_to_shared_memory_segment(char *shm, char *data);

int cleanup_shared_memory_segment();

#endif