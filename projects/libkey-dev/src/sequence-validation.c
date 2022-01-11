/*
 * Functions that validate a key sequence against a mode. Generic key words (represented
 * in-string as a -1, or with the string "\xff") act as a 'fallback' character. If a key
 * is pressed that does not match the prefix of any key sequences, and there exists a
 * key sequence with the same prefix (minus the new character), then that key sequence is
 * invoked.
*/

#define NCURSES_ENABLE_STDBOOL_H 0
#include "libkey.h"

void libkey_sequence_validate(struct LibkeyMode mode, const char *sequence) {

}
