#include "shared-memory-management.h"

// Create a shared memory segment and return its id
int create_shared_memory_segment(int key, int size, int permissions) {
    // get the shared memory key from the environment variable
    // create the shared memory segment
    log_debug("create_shared_memory_segment", "Creating shared memory segment");
    int shmid = shmget(key, size, permissions | IPC_CREAT);
    if (shmid == -1) {
        on_error("create_shared_memory_segment : shmget",
                 "Failed to create shared memory segment");
    }
    return shmid;
}

char *attach_shared_memory_segment(int key) {
    // attach the shared memory segment
    log_debug("attach_shared_memory_segment", "Attaching shared memory segment");

    int shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        on_error("attach_shared_memory_segment : shmget",
                 "Failed to attach shared memory segment");
    }
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        on_error("attach_shared_memory_segment : shmat",
                 "Failed to attach shared memory segment");
    }
    return shm;
}

int detach_shared_memory_segment(char *shm) {
    // detach the shared memory segment
    if (shmdt(shm) == -1) {
        on_error("detach_shared_memory : shmdt", "Failed to detach shared memory segment");
    }
    return 0;
}

int write_config_to_shared_memory_segment(char *shm, struct config *config) {
    // write to the shared memory segment
    memcpy(shm, config, sizeof(struct config));
    return 0;
}

int read_config_from_shared_memory_segment(char *shm, struct config *config) {
    // read from the shared memory segment
    memcpy(config, shm, sizeof(struct config));
    return 0;
}

int cleanup_shared_memory_segment() {
    // get the shared memory key from the environment variable
    int key = get_key_variable();
    // get the shared memory segment id
    int shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        on_error("cleanup_shared_memory : shmget", "Failed to get shared memory segment");
    }
    // destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        on_error("cleanup_shared_memory : shmctl", "Failed to destroy shared memory segment");
    }
    return 0;
}
