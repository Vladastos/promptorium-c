#include "shared-memory-management.h"

int $MEMORY_get_ipc_key() {
    char *key = getenv(IPC_KEY_VARIABLE_NAME);
    $LOG_debug(DEBUG_LEVEL_MAX, "$MEMORY_get_ipc_key", "Getting IPC key from environment variable");
    $LOG_debug(DEBUG_LEVEL_MAX, "$MEMORY_get_ipc_key", "IPC key: %s", key);
    if (key == NULL) {
        $UTILS_throw_error("$MEMORY_get_ipc_key : getenv",
                           "Failed to get shared memory key from environment variable");
    }
    int key_int = atoi(key);
    if (key_int == 0) {
        $UTILS_throw_error("$MEMORY_get_ipc_key : atoi",
                           "Failed to convert shared memory key from environment variable");
    }
    return key_int;
}

static int _MEMORY_detach_segment(char *shm) {
    // detach the shared memory segment
    $LOG_debug(DEBUG_LEVEL_MAX, "detach_shared_memory_segment", "Detaching shared memory segment");
    if (shmdt(shm) == -1) {
        $UTILS_throw_error("detach_shared_memory : shmdt",
                           "Failed to detach shared memory segment");
    }
    return 0;
}

static char *_MEMORY_attach_segment(int ipc_key) {
    // attach the shared memory segment
    $LOG_debug(DEBUG_LEVEL_MAX, "attach_shared_memory_segment", "Attaching shared memory segment");

    int shmid = shmget(ipc_key, 0, 0);
    if (shmid == -1) {
        $UTILS_throw_error("attach_shared_memory_segment : shmget",
                           "Failed to attach shared memory segment");
    }
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        $UTILS_throw_error("attach_shared_memory_segment : shmat",
                           "Failed to attach shared memory segment");
    }
    return shm;
}

void $MEMORY_create_segment(int ipc_key, int size, int permissions) {

    // create the shared memory segment
    $LOG_debug(DEBUG_LEVEL_MAX, "$MEMORY_create_segment", "Creating shared memory segment");
    int shmid = shmget(ipc_key, size, permissions | IPC_CREAT);
    if (shmid == -1) {
        $UTILS_throw_error("$MEMORY_create_segment : shmget",
                           "Failed to create shared memory segment");
    }
    return;
}

int $MEMORY_write_segment(int ipc_key, char *config_file_content) {
    // write to the shared memory segment

    char *shm = _MEMORY_attach_segment(ipc_key);

    // write the config to the shared memory segment
    $LOG_debug(DEBUG_LEVEL_MAX, "$MEMORY_write_segment", "Writing config to shared memory segment");

    memcpy(shm, config_file_content, SHARED_MEMORY_SEGMENT_SIZE);
    // detach the shared memory segment
    _MEMORY_detach_segment(shm);

    return 0;
}

int $MEMORY_read_segment(int ipc_key, char *config_file_content) {

    char *shm = _MEMORY_attach_segment(ipc_key);

    // read from the shared memory segment
    $LOG_debug(DEBUG_LEVEL_MAX, "$MEMORY_read_segment",
               "Reading config from shared memory segment");

    memcpy(config_file_content, shm, SHARED_MEMORY_SEGMENT_SIZE);

    // detach the shared memory segment
    _MEMORY_detach_segment(shm);

    return 0;
}

int $MEMORY_clear_segment() {
    // get the shared memory ipc_key from the environment variable
    int ipc_key = $MEMORY_get_ipc_key();
    // get the shared memory segment id
    int shmid = shmget(ipc_key, 0, 0);
    $LOG_debug(DEBUG_LEVEL_MAX, "$MEMORY_clear_segment", "Cleaning up shared memory segment");
    if (shmid == -1) {
        $UTILS_throw_error("$MEMORY_clear_segment : shmget", "Failed to get shared memory segment");
    }
    // destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        $UTILS_throw_error("$MEMORY_clear_segment : shmctl",
                           "Failed to destroy shared memory segment");
    }
    return 0;
}
