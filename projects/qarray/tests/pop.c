#include "common.h"

void error_out_of_bounds_a(void) {
    char *location = NULL;
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    location = qarray_pop(array, -1, location)
}

void error_out_of_bounds_b(void) {
    char *location = NULL;
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    location = qarray_pop(array, 2, location)
}

void error_out_of_bounds_c(void) {
    char *location = NULL;
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    location = qarray_pop(array, 1234, location)
}

int main(void) {
    char *string = NULL;
    char buffer[1024] = {0};
    struct StringArray *array = qarray_init(array, STRING_SETTINGS);

    qarray_insert(array, 0, "foo");
    qarray_insert(array, 1, "bar");
    qarray_insert(array, 2, "baz");
    qarray_insert(array, 3, "tuna");
    qarray_insert(array, 4, "spam");

    assert(string == NULL);

    extract_error_cb(error_out_of_bounds_a, 1024, buffer);
    assert(strcmp(buffer, "qarray_pop: attempt to pop index -1, out of bounds of array 'array'. (tests/pop.c:7)\n") == 0);

    extract_error_cb(error_out_of_bounds_b, 1024, buffer);
    assert(strcmp(buffer, "qarray_pop: attempt to pop index 2, out of bounds of array 'array'. (tests/pop.c:14)\n") == 0);

    extract_error_cb(error_out_of_bounds_c, 1024, buffer);
    assert(strcmp(buffer, "qarray_pop: attempt to pop index 1234, out of bounds of array 'array'. (tests/pop.c:21)\n") == 0);

    string = qarray_pop(array, 0, string);
    assert(strcmp(string, "foo") == 0);
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "baz") == 0);
    assert(strcmp(array->contents[2], "tuna") == 0);
    assert(strcmp(array->contents[3], "spam") == 0);
    assert(array->logical_size == 4);
    assert(array->physical_size == QARRAY_INITIAL_SIZE);

    string = qarray_pop(array, 3, string);
    assert(strcmp(string, "spam") == 0);
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "baz") == 0);
    assert(strcmp(array->contents[2], "tuna") == 0);
    assert(array->logical_size == 3);
    assert(array->physical_size == QARRAY_INITIAL_SIZE);

    string = qarray_pop(array, 1, string);
    assert(strcmp(string, "baz") == 0);
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(strcmp(array->contents[1], "tuna") == 0);
    assert(array->logical_size == 2);
    assert(array->physical_size == QARRAY_INITIAL_SIZE);

    string = qarray_pop(array, 1, string);
    assert(strcmp(string, "tuna") == 0);
    assert(strcmp(array->contents[0], "bar") == 0);
    assert(array->logical_size == 1);
    assert(array->physical_size == QARRAY_INITIAL_SIZE);

    string = qarray_pop(array, 0, string);
    assert(strcmp(string, "bar") == 0);
    assert(array->logical_size == 0);
    assert(array->physical_size == QARRAY_INITIAL_SIZE);

    return EXIT_SUCCESS;
}
