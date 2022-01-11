#include "common.h"

void dummy_callback(struct LibkeyState *state, int count, const char *arguments) {
    (void) state;
    (void) count;
    (void) arguments;
}

void error_too_long(void) {
    struct LibkeyMode modes[10] = {0};
    struct LibkeySequence insert_sequences[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);
    struct LibkeyMode *insert_mode = libkey_add_mode(&state, "insert", 10, insert_sequences);

    libkey_add_sequence(insert_mode, "foo bar baz tuna spam thud quz quuz", NULL);
}

void error_already_exists(void) {
    struct LibkeyMode modes[10] = {0};
    struct LibkeySequence insert_sequences[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);
    struct LibkeyMode *insert_mode = libkey_add_mode(&state, "insert", 10, insert_sequences);

    libkey_add_sequence(insert_mode, "dd", NULL);
    libkey_add_sequence(insert_mode, "dd", NULL);
}

int main(void) {
    char buffer[1024] = {0};
    struct LibkeyMode modes[10] = {0};
    struct LibkeySequence insert_sequences[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);
    struct LibkeyMode *insert_mode = libkey_add_mode(&state, "insert", 10, insert_sequences);

    extract_error_cb(error_too_long, 1024, buffer);
    assert(strcmp(buffer, "libkey_add_sequence: sequence 'foo bar baz tuna spam thud quz quuz' is too long. maximum 32 characters.\n") == 0);

    extract_error_cb(error_already_exists, 1024, buffer);
    assert(strcmp(buffer, "libkey_add_sequence: attempt to add a sequence 'dd' that is already defined.\n") == 0);

    assert(libkey_add_sequence(insert_mode, "dd", dummy_callback) != NULL);
    assert(strcmp(insert_mode->contents[0].sequence, "dd") == 0);
    assert(insert_mode->logical_size == 1);
    assert(insert_mode->physical_size == 10);
    assert(insert_mode->contents[0].callback == dummy_callback);

    assert(libkey_add_sequence(insert_mode, "cc", dummy_callback) != NULL);
    assert(strcmp(insert_mode->contents[0].sequence, "dd") == 0);
    assert(strcmp(insert_mode->contents[1].sequence, "cc") == 0);
    assert(insert_mode->contents[0].callback == dummy_callback);
    assert(insert_mode->contents[1].callback == dummy_callback);
    assert(insert_mode->logical_size == 2);
    assert(insert_mode->physical_size == 10);

    return EXIT_SUCCESS;
}
