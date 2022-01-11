#include "common.h"

int main(void) {
    struct LibkeyMode modes[10] = {0};
    struct LibkeySequence sequences_a[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);

    assert(libkey_mode_exists(&state, "insert") == 0);
    assert(libkey_mode_exists(&state, "normal") == 0);

    libkey_add_mode(&state, "insert", 10, sequences_a);
    assert(libkey_mode_exists(&state, "insert") == 1);
    assert(libkey_mode_exists(&state, "normal") == 0);

    libkey_add_mode(&state, "normal", 10, sequences_a);
    assert(libkey_mode_exists(&state, "insert") == 1);
    assert(libkey_mode_exists(&state, "normal") == 1);

    return EXIT_SUCCESS;
}
