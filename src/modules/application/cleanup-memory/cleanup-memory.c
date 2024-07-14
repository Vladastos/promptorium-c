#include "cleanup-memory.h"

int get_ipc_key() {
    char *key = getenv("PROMPTORIUM_IPC_KEY");
    if (key == NULL) {
        on_error("cleanup-memory - get_key : getenv", "Failed to get shared memory key from environment variable");
    }
    //convert the string to an integer
    int int_key = atoi(key);
    if (int_key == -1) {
        on_error("cleanup-memory - get_key : atoi", "Failed to convert string to integer");
    }
    return int_key;
}

int cleanup_memory_with_key(int key) {

    //get the shared memory segment id
    int shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        on_error("cleanup-memory - shmget", "Failed to get shared memory segment");
    }

    // destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        on_error("cleanup-memory - shmctl", "Failed to destroy shared memory segment");
    }
    return 0;
}
int cleanup_memory() {
    int key = get_ipc_key();
    return cleanup_memory_with_key(key);
}