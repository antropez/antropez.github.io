/*
 * Functions to process key presses. The hardest part of this will be
 * handling generic keys.
*/

#define NCURSES_ENABLE_STDBOOL_H 0

#include <string.h>
#include <ncurses.h>

#include "libkey.h"

/*
 * Count the number of key sequences prefixed with a string.
 *
 * @param state: the state to check
 * @param prefix: the string to compare
 * @return: number of key sequences prefixed with the string
*/
int libkey_count_prefixes(struct LibkeyState *state, const char *prefix) {
    int prefixed = 0;
    unsigned int index = 0;

    for(index = 0; index < state->mode.logical_size; index++) {
        struct LibkeySequence sequence = state->mode.contents[index];
    }

    return prefixed;
}

void libkey_scan(struct LibkeyState *state) {
    int character = getch();
    size_t length = strlen(state->sequence);

    if(length == LIBKEY_SEQUENCE_NAME) {
        memset(state->sequence, 0, LIBKEY_SEQUENCE_NAME);

        return;
    }

    
}
