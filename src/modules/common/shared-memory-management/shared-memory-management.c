#include "shared-memory-management.h"

void $memory_create_segment(int ipc_key, int size, int permissions) {

    // create the shared memory segment
    $log_debug( DEBUG_LEVEL_MAX,"$memory_create_segment", "Creating shared memory segment");
    int shmid = shmget(ipc_key, size, permissions | IPC_CREAT);
    if (shmid == -1) {
        $throw_error("$memory_create_segment : shmget",
                    "Failed to create shared memory segment");
    }
    return;
}

int $memory_write_segment(int ipc_key, struct config_t *config) {
    // write to the shared memory segment

    char *shm = _memory_attach_segment(ipc_key);

    // write the config to the shared memory segment
    $log_debug(DEBUG_LEVEL_MAX,"$memory_write_segment", "Writing config to shared memory segment");

    memcpy(shm, config, sizeof(struct config_t));

    // detach the shared memory segment
    _memory_detach_segment(shm);

    return 0;
}

int $memory_read_segment(int ipc_key, struct config_t *config) {

    char *shm = _memory_attach_segment(ipc_key);

    // read from the shared memory segment
    $log_debug(DEBUG_LEVEL_MAX,"$memory_read_segment", "Reading config from shared memory segment");

    memcpy(config, shm, sizeof(struct config_t));

    // detach the shared memory segment
    _memory_detach_segment(shm);

    return 0;
}

int $memory_cleanup_segment() {
    // get the shared memory ipc_key from the environment variable
    int ipc_key = $get_ipc_key();
    // get the shared memory segment id
    int shmid = shmget(ipc_key, 0, 0);
    $log_debug(DEBUG_LEVEL_MAX,"cleanup_shared_memory", "Cleaning up shared memory segment");
    if (shmid == -1) {
        $throw_error("cleanup_shared_memory : shmget", "Failed to get shared memory segment");
    }
    // destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        $throw_error("cleanup_shared_memory : shmctl",
                    "Failed to destroy shared memory segment");
    }
    return 0;
}

char *_memory_attach_segment(int ipc_key) {
    // attach the shared memory segment
    $log_debug(DEBUG_LEVEL_MAX,"attach_shared_memory_segment", "Attaching shared memory segment");

    int shmid = shmget(ipc_key, 0, 0);
    if (shmid == -1) {
        $throw_error("attach_shared_memory_segment : shmget",
                    "Failed to attach shared memory segment");
    }
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        $throw_error("attach_shared_memory_segment : shmat",
                    "Failed to attach shared memory segment");
    }
    return shm;
}

int _memory_detach_segment(char *shm) {
    // detach the shared memory segment
    $log_debug(DEBUG_LEVEL_MAX,"detach_shared_memory_segment", "Detaching shared memory segment");
    if (shmdt(shm) == -1) {
        $throw_error("detach_shared_memory : shmdt", "Failed to detach shared memory segment");
    }
    return 0;
}
