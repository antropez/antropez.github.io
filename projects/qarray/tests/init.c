#include "common.h"

int main(void) {
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);
    
    assert(array->logical_size == 0);
    assert(array->physical_size == QARRAY_INITIAL_SIZE);
    assert(array->contents != NULL);

    return EXIT_SUCCESS;
}
