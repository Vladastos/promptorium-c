#include "load-config.h"

int load_config(status_t *status) {
    //create a shared memory segment
    key_t key = ftok("/tmp", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        status->code = STATUS_GENERIC_ERROR;
        status->function_name = "load_config:shmget";
        status->message = "Failed to create shared memory segment";
        return -1;
    }

    //attach the shared memory segment
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        status->code = STATUS_GENERIC_ERROR;
        status->function_name = "load_config:shmat";
        status->message = "Failed to attach shared memory segment";
        return -1;
    }

    //write to the shared memory segment
    strcat (shm, "Hello, world!\n");

    printf("data: %s", shm);
    printf("key: %d", key);
    //detach the shared memory segment
    if (shmdt(shm) == -1) {
        status->code = STATUS_GENERIC_ERROR;
        status->function_name = "load_config:shmdt";
        status->message = "Failed to detach shared memory segment";
        return -1;
    }
    // return the key to the shared memory segment
    return key;
    
}