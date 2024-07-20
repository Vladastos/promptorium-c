#include "cleanup.h"

int cleanup() {
    $memory_cleanup_segment();
    return 0;
}