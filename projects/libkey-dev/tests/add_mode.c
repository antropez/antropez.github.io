#include "common.h"

void error_mode_exists(void) {
    struct LibkeyMode modes[10] = {0};
    struct LibkeySequence sequences[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);

    libkey_add_mode(&state, "normal", 10, sequences);
    libkey_add_mode(&state, "normal", 10, sequences);
}

void error_mode_too_long(void) {
    struct LibkeyMode modes[10] = {0};
    struct LibkeySequence sequences[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);

    libkey_add_mode(&state, "foo bar baz tuna spam thud quz qaaz", 10, sequences);
}

int main(void) {
    char buffer[1024] = {0};
    struct LibkeyMode modes[10] = {0};
    struct LibkeySequence sequences[10] = {0};
    struct LibkeySequence sequences_2[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);

    libkey_add_mode(&state, "normal", 10, sequences);
    assert(strcmp(state.contents[0].name, "normal") == 0);
    assert(state.logical_size == 1);
    assert(state.physical_size == 10);

    extract_error_cb(error_mode_exists, 1023, buffer);
    assert(strcmp(buffer, "libkey_add_mode: attempt to add a mode 'normal' that is already defined.\n") == 0);

    extract_error_cb(error_mode_too_long, 1023, buffer);
    assert(strcmp(buffer, "libkey_add_mode: mode name 'foo bar baz tuna spam thud quz qaaz' is too long. maximum 32 characters.\n") == 0);

    libkey_add_mode(&state, "insert", 10, sequences_2);
    assert(strcmp(state.contents[1].name, "insert") == 0);
    assert(state.logical_size == 2);
    assert(state.physical_size == 10);

    return EXIT_SUCCESS;
}
