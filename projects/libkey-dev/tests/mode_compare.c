#include "common.h"

int main(void) {
    struct LibkeyMode mode_a = {0};
    struct LibkeyMode mode_b = {0};
    struct LibkeyMode mode_c = {0};
    struct LibkeyMode mode_d = {0};
    struct LibkeyMode mode_e = {0};

    strcat(mode_a.name, "foobar");
    strcat(mode_b.name, "foobar");
    strcat(mode_c.name, "spam");
    strcat(mode_d.name, "foobar");
    strcat(mode_e.name, "");

    assert(libkey_mode_compare(mode_a, mode_b) == 1);
    assert(libkey_mode_compare(mode_a, mode_c) == 0);
    assert(libkey_mode_compare(mode_d, mode_c) == 0);
    assert(libkey_mode_compare(mode_e, mode_c) == 0);

    return EXIT_SUCCESS;
}
