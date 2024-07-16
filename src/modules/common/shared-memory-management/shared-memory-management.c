#include "shared-memory-management.h"

void create_shared_memory_segment(int ipc_key, int size, int permissions) {

    // create the shared memory segment
    log_debug("create_shared_memory_segment", "Creating shared memory segment");
    int shmid = shmget(ipc_key, size, permissions | IPC_CREAT);
    if (shmid == -1) {
        throw_error("create_shared_memory_segment : shmget",
                 "Failed to create shared memory segment");
    }
    return;
}

int write_config_to_shared_memory_segment(int ipc_key, struct config *config) {
    // write to the shared memory segment

    char *shm = _attach_shared_memory_segment(ipc_key);

    // write the config to the shared memory segment
    log_debug("write_config_to_shared_memory_segment", "Writing config to shared memory segment");
    
    memcpy(shm, config, sizeof(struct config));

    // detach the shared memory segment
    _detach_shared_memory_segment(shm);

    return 0;
}

int read_config_from_shared_memory_segment(int ipc_key, struct config *config) {

    char *shm = _attach_shared_memory_segment(ipc_key);

    // read from the shared memory segment
    log_debug("read_config_from_shared_memory_segment", "Reading config from shared memory segment");
    
    memcpy(config, shm, sizeof(struct config));

    // detach the shared memory segment
    _detach_shared_memory_segment(shm);

    return 0;
}

int cleanup_shared_memory_segment() {
    // get the shared memory ipc_key from the environment variable
    int ipc_key = get_ipc_key();
    // get the shared memory segment id
    int shmid = shmget(ipc_key, 0, 0);
    log_debug("cleanup_shared_memory", "Cleaning up shared memory segment");
    if (shmid == -1) {
        throw_error("cleanup_shared_memory : shmget", "Failed to get shared memory segment");
    }
    // destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        throw_error("cleanup_shared_memory : shmctl", "Failed to destroy shared memory segment");
    }
    return 0;
}
char *_attach_shared_memory_segment(int ipc_key) {
    // attach the shared memory segment
    log_debug("attach_shared_memory_segment", "Attaching shared memory segment");

    int shmid = shmget(ipc_key, 0, 0);
    if (shmid == -1) {
        throw_error("attach_shared_memory_segment : shmget",
                 "Failed to attach shared memory segment");
    }
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        throw_error("attach_shared_memory_segment : shmat",
                 "Failed to attach shared memory segment");
    }
    return shm;
}

int _detach_shared_memory_segment(char *shm) {
    // detach the shared memory segment
    log_debug("detach_shared_memory_segment", "Detaching shared memory segment");
    if (shmdt(shm) == -1) {
        throw_error("detach_shared_memory : shmdt", "Failed to detach shared memory segment");
    }
    return 0;
}
