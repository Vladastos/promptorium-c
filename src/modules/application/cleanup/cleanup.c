#include "cleanup.h"

int cleanup() {
    $MEMORY_clear_segment();
    return 0;
}