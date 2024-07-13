#include "status-handling.h"

status_t init_status(char *name) {
    status_t status;
    status.code = STATUS_OK;
    status.function_name = name;
    status.message = "Ok";
    return status;
}

int handle_status(status_t *status) {
    switch (status->code) {
        case STATUS_OK:
            break;
        case STATUS_GENERIC_ERROR:
            printf("Error in function %s: %s\n", status->function_name, status->message);
            break;
        default:
            break;
    }

    return status->code;
}
