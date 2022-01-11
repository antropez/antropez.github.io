#include "stack_common.h"

void error_full(void) {
    char *strings[3] = {0};
    struct StringArray array = qarray_init(array, 3, strings);

    qarray_insert(&array, 0, "foo");
    qarray_insert(&array, 1, "bar");
    qarray_insert(&array, 2, "baz");
    qarray_insert(&array, 3, "tuna");
}

void error_out_of_bounds_a(void) {
    char *strings[3] = {0};
    struct StringArray array = qarray_init(array, 3, strings);

    qarray_insert(&array, -1, "foo");
}

void error_out_of_bounds_b(void) {
    char *strings[3] = {0};
    struct StringArray array = qarray_init(array, 3, strings);

    qarray_insert(&array, 2, "foo");
}

void error_out_of_bounds_c(void) {
    char *strings[3] = {0};
    struct StringArray array = qarray_init(array, 3, strings);

    qarray_insert(&array, 1234, "foo");
}

int main(void) {
    char buffer[1024] = {0};
    
    extract_error_cb(error_full, 1024, buffer);
    assert(strcmp(buffer, "qarray_insert: attempt to insert value '\"tuna\"' into full array '&array'. (tests/stack_insert.c:10)\n") == 0);

    extract_error_cb(error_out_of_bounds_a, 1024, buffer);
    assert(strcmp(buffer, "qarray_insert: attempt to insert at index -1, out of bounds of array '&array'. (tests/stack_insert.c:17)\n") == 0);

    extract_error_cb(error_out_of_bounds_b, 1024, buffer);
    assert(strcmp(buffer, "qarray_insert: attempt to insert at index 2, out of bounds of array '&array'. (tests/stack_insert.c:24)\n") == 0);

    extract_error_cb(error_out_of_bounds_c, 1024, buffer);
    assert(strcmp(buffer, "qarray_insert: attempt to insert at index 1234, out of bounds of array '&array'. (tests/stack_insert.c:31)\n") == 0);

    return EXIT_SUCCESS; 
}
