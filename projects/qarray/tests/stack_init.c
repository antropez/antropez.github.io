#include "stack_common.h"

int main(void) {
    char *strings[10] = {0};
    struct StringArray array = qarray_init(array, 10, strings);
    
    assert(array.logical_size == 0);
    assert(array.physical_size == 10);
    assert(array.contents == strings);

    return EXIT_SUCCESS;
}
