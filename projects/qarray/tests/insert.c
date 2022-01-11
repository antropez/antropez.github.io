#include "common.h"

void error_out_of_bounds(void) {
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    qarray_insert(array, -1, "foo");
}

void error_out_of_bounds_2(void) {
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    qarray_insert(array, 2, "foo");
}

void error_out_of_bounds_3(void) {
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    qarray_insert(array, 1234, "foo");
}


int main(void) {
    char buffer[1024] = {0};
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    extract_error_cb(error_out_of_bounds, 1024, buffer);
    assert(strcmp(buffer, "qarray_insert: attempt to insert at index -1, out of bounds of array 'array'. (tests/insert.c:6)\n") == 0);

    extract_error_cb(error_out_of_bounds_2, 1024, buffer);
    assert(strcmp(buffer, "qarray_insert: attempt to insert at index 2, out of bounds of array 'array'. (tests/insert.c:12)\n") == 0);

    extract_error_cb(error_out_of_bounds_3, 1024, buffer);
    assert(strcmp(buffer, "qarray_insert: attempt to insert at index 1234, out of bounds of array 'array'. (tests/insert.c:18)\n") == 0);

    qarray_insert(array, 0, "foo");
    assert(strcmp(array->contents[0], "foo") == 0);
    assert(array->logical_size == 1);
    assert(array->physical_size == 5);

    qarray_insert(array, 0, "bar");
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "foo") == 0);
    assert(array->logical_size == 2);
    assert(array->physical_size == 5);

    qarray_insert(array, 1, "baz");
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "baz") == 0);
    assert(strcmp(array->contents[2], "foo") == 0);
    assert(array->logical_size == 3);
    assert(array->physical_size == 5);

    qarray_insert(array, 2, "thud");
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "baz") == 0);
    assert(strcmp(array->contents[2], "thud") == 0);
    assert(strcmp(array->contents[3], "foo") == 0);
    assert(array->logical_size == 4);
    assert(array->physical_size == 5);

    qarray_insert(array, 1, "spam");
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "spam") == 0);
    assert(strcmp(array->contents[2], "baz") == 0);
    assert(strcmp(array->contents[3], "thud") == 0);
    assert(strcmp(array->contents[4], "foo") == 0);
    assert(array->logical_size == 5);
    assert(array->physical_size == 5);

    qarray_insert(array, 2, "tuna");
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "spam") == 0);
    assert(strcmp(array->contents[2], "tuna") == 0);
    assert(strcmp(array->contents[3], "baz") == 0);
    assert(strcmp(array->contents[4], "thud") == 0);
    assert(strcmp(array->contents[5], "foo") == 0);
    assert(array->logical_size == 6);
    assert(array->physical_size == 10);

    return EXIT_SUCCESS;
}
