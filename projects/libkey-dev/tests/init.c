#include "common.h"

int main(void) {
    struct LibkeyMode modes[10] = {0};
    struct LibkeyState state = libkey_init(10, modes);

    assert(state.logical_size == 0);
    assert(state.physical_size == 10);
    assert(state.contents == modes);
    assert(state.mode.name[0] == '\0');
    assert(state.mode.logical_size == 0);
    assert(state.mode.physical_size == 0);
    assert(state.mode.contents == NULL);

    return EXIT_SUCCESS;
}
