#define NCURSES_ENABLE_STDBOOL_H 0
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "libkey.h"
include(dm4array.m4)

struct LibkeyState libkey_init(size_t length, struct LibkeyMode *modes) {
    struct LibkeyState new_state = {0};

    new_state.physical_size = length;
    new_state.contents = modes;

    return new_state;
}

struct LibkeyMode *libkey_add_mode(struct LibkeyState *state, const char *name, size_t length, struct LibkeySequence *sequences) {
    int exists = libkey_mode_exists(state, name);
    struct LibkeyMode new_mode = {0};

    if(strlen(name) > LIBKEY_MODE_NAME)
        libkey_error("libkey_add_mode: mode name '%s' is too long. maximum %i characters.\n", name, LIBKEY_MODE_NAME);

    if(exists == 1)
        libkey_error("libkey_add_mode: attempt to add a mode '%s' that is already defined.\n", name);

    strncat(new_mode.name, name, LIBKEY_MODE_NAME);
    new_mode.physical_size = length;
    new_mode.contents = sequences;

    dm4_array_append(state, new_mode, LIBKEY_MODE_ARRAY);

    return state->contents + (state->logical_size - 1);
}

struct LibkeySequence *libkey_add_sequence(struct LibkeyMode *mode, const char *sequence, LibkeySequenceCallback callback) {
    int exists = libkey_sequence_exists(mode, sequence);    
    struct LibkeySequence new_sequence = {0};

    if(strlen(sequence) > LIBKEY_SEQUENCE_NAME)
        libkey_error("libkey_add_sequence: sequence '%s' is too long. maximum %i characters.\n", sequence, LIBKEY_SEQUENCE_NAME);

    if(exists == 1)
        libkey_error("libkey_add_sequence: attempt to add a sequence '%s' that is already defined.\n", sequence);

    strncat(new_sequence.sequence, sequence, LIBKEY_SEQUENCE_NAME);
    new_sequence.callback = callback;

    dm4_array_append(mode, new_sequence, LIBKEY_SEQUENCE_ARRAY);

    return mode->contents + (mode->logical_size - 1);
}

int libkey_mode_exists(struct LibkeyState *state, const char *name) {
    int exists = 0;
    struct LibkeyMode comparison_mode = {0};

    strncat(comparison_mode.name, name, LIBKEY_MODE_NAME);
    exists = dm4_array_find(state, comparison_mode, exists, LIBKEY_MODE_ARRAY);

    return exists != -1;
}

int libkey_sequence_exists(struct LibkeyMode *mode, const char *sequence) {
    int exists = 0;
    struct LibkeySequence comparison_sequence = {0};

    strncat(comparison_sequence.sequence, sequence, LIBKEY_SEQUENCE_NAME);
    exists = dm4_array_find(mode, comparison_sequence, exists, LIBKEY_SEQUENCE_ARRAY);

    return exists != -1;
}

int libkey_mode_compare(struct LibkeyMode mode_a, struct LibkeyMode mode_b) {
    return strcmp(mode_a.name, mode_b.name) == 0;
}

int libkey_sequence_compare(struct LibkeySequence sequence_a, struct LibkeySequence sequence_b) {
    return strcmp(sequence_a.sequence, sequence_b.sequence) == 0;
}

void libkey_error(const char *format, ...) {
    va_list specifiers = {0};

    va_start(specifiers, format);
    vfprintf(stderr, format, specifiers);
    va_end(specifiers);

    exit(EXIT_FAILURE);
}
