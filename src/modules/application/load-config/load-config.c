#include "load-config.h"

int get_key() {
    char *key = getenv("PROMPTORIUM_IPC_KEY");
    if (key == NULL) {
        on_error("load-config - get_key : getenv", "Failed to get shared memory key from environment variable");
    }

    //convert the string to an integer
    int int_key = atoi(key);
    if (int_key == -1) {
        on_error("load-config - get_key : atoi", "Failed to convert string to integer");
    }
    return int_key;
}

int load_config() {
    //get the shared memory key from the environment variable
    int key = get_key();

    //create the shared memory segment
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        on_error("load_config : shmget", "Failed to create shared memory segment");
    }

    //attach the shared memory segment
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        on_error("load_config : shmat", "Failed to attach shared memory segment");
    }

    // TODO: load configuration from file

    //write to the shared memory segment
    strcat (shm, "Hello, world!\n");

    printf("Configuration loaded\n");
    printf("data: %s\n", shm);
    

    //detach the shared memory segment
    if (shmdt(shm) == -1) {
        on_error("load_config - shmdt", "Failed to detach shared memory segment");
    }

    return 0;
    
}