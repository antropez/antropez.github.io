#ifndef LIB_KEY_H
#define LIB_KEY_H

#include <stddef.h>

#define LIBKEY_MODE_NAME        32
#define LIBKEY_SEQUENCE_NAME    32

struct LibkeyState;

/*
 * A function that can be called when a key sequence has been typed.
*/
typedef void (*LibkeySequenceCallback)(struct LibkeyState *state, int count, const char *arguments);

/*
 * A possible chain of keys that invokes a callback once the
 * chain has been typed.
 *
 * @field sequence: the keys that need to be pressed
 * @field callback: the function to invoke
*/
struct LibkeySequence {
    char sequence[LIBKEY_SEQUENCE_NAME + 1];
    LibkeySequenceCallback callback;
};

/*
 * A mode, which contains a unique identifier, the name, and
 * an array of keyboard sequences which can be executed while
 * the mode is selected.
 *
 * @field name: the name of the mode
 * @field logical_size: the number of sequences in the array
 * @field physical_size: the maximum number of sequences
 * @field contents: the array of key sequences
*/
struct LibkeyMode {
    char name[LIBKEY_MODE_NAME + 1];
    size_t logical_size;
    size_t physical_size;
    struct LibkeySequence *contents;
};

/*
 * The state container for libkey. Contains all modes, and is the
 * main part of the keybinding system
 *
 * @field sequence: the typed sequence
 * @field mode: the selected mode
 * @field logical_size: the number of modes in the array
 * @field physical_size: the maximum number of modes
 * @field contents: the array of modes
*/
struct LibkeyState {
    char sequence[LIBKEY_MODE_NAME + 1];
    struct LibkeyMode mode;
    size_t logical_size;
    size_t physical_size;
    struct LibkeyMode *contents;
};

/*
 * Initializes a new state container with an array of modes that
 * will be filled up.
 *
 * @param length: the maximum length of the mode array
 * @param modes: the stack array to use for the modes
 * @return: the new state container
*/
struct LibkeyState libkey_init(size_t length, struct LibkeyMode *modes);

/*
 * Adds a new mode into a state's mode array with a name, and an
 * array of slots to hold key sequences bound to the mode. If a
 * mode with the same name is found, an error is rasied and the
 * program exits.
 *
 * @param state: the state container to add the mode to
 * @param name: the name of the mode
 * @param length: the maximum length of the mode array
 * @param modes: the stack array to use for the modes
 * @return: pointer to the new mode
*/
struct LibkeyMode *libkey_add_mode(struct LibkeyState *state, const char *name, size_t length, struct LibkeySequence *sequences);

/*
 * Adds a new key sequence into the mode's sequence array. If the
 * sequence is already in the mode, or the sequence is larger than
 * LIBKEY_SEQUENCE_NAME, then an error is raised and the program
 * exists.
 *
 * @param mode: the mode to add the sequence to
 * @param sequence: the key sequence to add into the mode
 * @param callback: the function to call if the sequence is typed
 * @return: pointer to the new sequence
*/
struct LibkeySequence *libkey_add_sequence(struct LibkeyMode *mode, const char *sequence, LibkeySequenceCallback callback);

/*
 * Determines if a mode is registered into a state container.
 *
 * @param state: the state to check
 * @param name: the name of the mode to search for
 * @return: 1 if it exists, 0 if it does not
*/
int libkey_mode_exists(struct LibkeyState *state, const char *name);

/*
 * Determines if a sequence is registered into a mode.
 *
 * @param mode: the mode to check
 * @param sequence: the sequence to search for
 * @return: 1 if it exists, 0 if it does not
*/
int libkey_sequence_exists(struct LibkeyMode *mode, const char *sequence);

/*
 * Compares two modes using their names.
 *
 * @param mode_a: the first mode to compare
 * @param mode_b: the second mode to compare
 * @return: 1 if they are the same, 0 if they are not
*/
int libkey_mode_compare(struct LibkeyMode mode_a, struct LibkeyMode mode_b);

/*
 * Compares two sequences using their sequences.
 *
 * @param sequence_a: the first sequence to compare
 * @param sequence_b: the second sequence to compare
 * @return: 1 if they are the same, 0 if they are not
*/
int libkey_sequence_compare(struct LibkeySequence sequence_a, struct LibkeySequence sequence_b);

/*
 * Verify that a key sequence is legal within the context
 * of a provided mode. If it is not, an error is raised and
 * the program exists.
 *
 * @param mode: the mode to check the key sequence against
*  @param sequence: the key sequence to check
*/
void libkey_sequence_validate(struct LibkeyMode mode, const char *sequence);

/*
 * Raises a formatted error message, and exits the program with EXIT_FAILURE.
 *
 * @param format: the format string to use
*/
void libkey_error(const char *format, ...);

#endif
