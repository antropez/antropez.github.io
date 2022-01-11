/*
 * A macro-based M4 array implementation.
 *
 * The settings macro is written as:
 * type;compare?;free?;stack;
 *
 * Where ? means that the argument can be ignored, and should be written as void.
 * stack is true or false.
*/

#ifndef DM4_ARRAY_H
#define DM4_ARRAY_H

#ifndef DM4_ARRAY_EXIT_CODE
#define DM4_ARRAY_EXIT_CODE EXIT_FAILURE
#endif

#ifndef DM4_ARRAY_INITIAL_SIZE
#define DM4_ARRAY_INITIAL_SIZE 5
#endif

#ifndef DM4_ARRAY_NEXT_SIZE
#define DM4_ARRAY_NEXT_SIZE 5
#endif

define(`LIBKEY_MODE_ARRAY', `struct LibkeyMode;libkey_mode_compare;void;true;')
define(`LIBKEY_SEQUENCE_ARRAY', `struct LibkeyMode;libkey_sequence_compare;void;true;')

define(`m4_index_list', `ifelse(eval($2 > 0), 1, `$0(substr($1, eval(index($1, ;) + 1)), decr($2))', ifelse(eval($2 < 0), 1,,substr($1, 0, index($1, ;))))')

define(`m4_stringify', ` ifelse(substr($1, 0, 1), ", $1, "$1")')

define(`m4_compare', `
    ifelse($1, char*, (strcmp(($2), ($3)) == 0), ($2) == ($3))
')

define(`m4_else', `,')

define(`dm4_array_define', `
struct $1 {
    unsigned int logical_size;
    unsigned int physical_size;
    m4_index_list($2, 0)*contents;
}')

/*
 * Initialize a new array. If the second argument is filled, it is assumed
 * that the third is also filled. If so, then it will generate with code for
 * a stack array.
 *
 * $1: the array to initialize into
 * $2: the length of the block
 * #3: the stack array
*/
define(`dm4_array_init', `
    ifelse($2,,
    malloc(sizeof(*($1)));
    ($1)->logical_size = 0;
    ($1)->physical_size = DM4_ARRAY_INITIAL_SIZE;
    ($1)->contents = malloc(sizeof(*($1)->contents) * DM4_ARRAY_INITIAL_SIZE),

    {0};
    ($1).contents = ($3);
    ($1).logical_size = 0;
    ($1).physical_size = ($2))')

/*
 * Releases an array from memory. if the FREE function is not specified
 * in the array's settings, then the code for freeing the array's contents
 * is not generated. If the stack flag is ticked in the array settings, then
 * the structure freeing functionality is not generated.
 *
 * $1: the array to free
 * $2: the array settings
*/
define(`dm4_array_free', `
   ifelse(m4_index_list($2, 2),void,,{
        
        unsigned int __dm4_array_free_index = 0;

        for(__dm4_array_free_index = 0; __dm4_array_free_index < ($1)->logical_size; __dm4_array_free_index++) {
            m4_index_list($2, 2)(($1)->contents[__dm4_array_free_index]);
        }
    })

    ifelse(m4_index_list($2, 3), true,,
    free(($1)->contents);
    free(($1)))')

/*
 * Appends a value into the array. If the STACK option is set to true, and
 * the array is FULL, then an error is rasied and the program exits with the
 * value assigned to DM4_ARRAY_EXIT_CODE.
 *
 * $1: the array to append to
 * $2: the value to append
 * $3: the array settings
*/
define(`dm4_array_append', `
    if(($1)->logical_size == ($1)->physical_size) {
        ifelse(m4_index_list($3, 3), false, /* Should this macro behave like a stack array? */
            ($1)->physical_size = ($1)->physical_size + DM4_ARRAY_NEXT_SIZE;
            ($1)->contents = realloc(($1)->contents, sizeof(*(($1)->contents)) * ($1)->physical_size);
        m4_else
            fprintf(stderr, "array_append: attempt to append value \"%s\" into full array.\n", m4_stringify($2));
            exit(DM4_ARRAY_EXIT_CODE);
        )
    }

    ($1)->contents[($1)->logical_size] = ($2);
    ($1)->logical_size++
')

/*
 * Insert a value into an array at an index in the array. If the STACK
 * option is true, and the array is FULL, then an error is raised and the
 * program exits with the value assigned to DM4_ARRAY_EXIT_CODE. If the
 * index provided is out of the bounds of the array, then the above occurs.
 *
 * $1: the array to append to
 * $2: the index to insert into
 * $3: the value to insert
 * $4: the array settings
*/
define(`dm4_array_insert', `
    if((($2) < 0) || (($2) > (($1))->logical_size)) { /* Out of bounds error */
        fprintf(stderr, "array_insert: attempt to insert \"%s\" out of the bounds of array \"%s\".\n", m4_stringify($3), m4_stringify($1));
        exit(DM4_ARRAY_EXIT_CODE);
    }

    if((($1))->logical_size == (($1))->physical_size) {
        ifelse(m4_index_list($4, 3), false, /* Should this macro behave like a stack array? */
            ($1)->physical_size = ($1)->physical_size + DM4_ARRAY_NEXT_SIZE;
            ($1)->contents = realloc(($1)->contents, sizeof(*(($1)->contents)) * ($1)->physical_size);
        m4_else
            fprintf(stderr, "array_insert: attempt to insert value \"%s\" into full array \"%s\".\n", m4_stringify($3), m4_stringify($1));
            exit(DM4_ARRAY_EXIT_CODE);
        )
    }

    memmove(($1)->contents + ($2 + 1), (($1)->contents) + $2, sizeof(*(($1)->contents)) * ((($1)->logical_size) - $2));
    ($1)->contents[$2] = $3;
    ($1)->logical_size++
')

/*
 * Pops an element at an index in an array and returns it. If the index
 * is out of bounds, an error will be raised and the program will be exited
 * with the value assigned to DM4_ARRAY_EXIT_CODE.
 *
 * If the third parameter, the location, is not given, then the value will be
 * popped from the array without returning it.
 *
 * $1: the array to pop from
 * $2: the index to pop
 * $3: the location to put the value into (optional)
*/
define(`dm4_array_pop', `
    ifelse($3, `', , ($3);)

    if((($2) < 0) || (($2) >= (($1))->logical_size)) { /* Out of bounds error */
        fprintf(stderr, "array_pop: attempt to pop index %i, which is out of the bounds of array \"%s\".\n", $2, m4_stringify($1));
        exit(DM4_ARRAY_EXIT_CODE);
    }

    ifelse($3, `', , ($3) = ($1)->contents[($2)];)
    memmove(($1)->contents + ($2), ($1)->contents + ($2 + 1), sizeof(*(($1)->contents)) * ((($1)->logical_size) - $2));
    ($1)->logical_size--
')

/*
 * Searches an array for a value, and removes it if it is found. If it
 * is not found, an error is rasied. If the comparison function is
 * not provided, and the type is a C primitive like a string or integer,
 * then a default comparison is performed. If the type is not a primitive,
 * and there is no comparison function provided, it will default to x == y,
 * which may or may not result in a compiler warning.
 *
 * $1: the array to remove from
 * $2: the value to remove
 * $3: the array settings
*/
define(`dm4_array_remove', `
do {
    int __dm4_array_remove_found = 0;
    size_t __dm4_array_remove_index = 0;

    for(__dm4_array_remove_index = 0; __dm4_array_remove_index < ($1)->logical_size; __dm4_array_remove_index++) {
        ifelse(m4_index_list($3, 1), void,
            if(m4_compare(m4_index_list($3, 0), ($1)->contents[__dm4_array_remove_index], $2) == 0) {
                continue;
            }
            ,
            if(m4_index_list($3, 1)(($1)->contents[__dm4_array_remove_index], $2) == 0) {
                continue;
            }
        )

        memmove(($1)->contents + (__dm4_array_remove_index), ($1)->contents + (__dm4_array_remove_index + 1), sizeof(*(($1)->contents)) * ((($1)->logical_size) - __dm4_array_remove_index));
        ($1)->logical_size--;
        __dm4_array_remove_found = 1;
    }

    if(__dm4_array_remove_found == 0) {
        fprintf(stderr, "array_remove: attempt to remove value \"%s\" which does not appear in array \"%s\".\n", m4_stringify($2), m4_stringify($1));
        exit(DM4_ARRAY_EXIT_CODE);
    }
} while(0)
')

/*
 * Searches an array for a value, and returns its index if it is found.
 * If it is not found, then -1 is returned. If the comparison function is
 * not provided, and the type is a C primitive like a string or integer,
 * then a default comparison is performed. If the type is not a primitive,
 * and there is no comparison function provided, it will default to x == y,
 * which may or may not result in a compiler warning.
 *
 * $1: the array to search
 * $2: the value to find
 * $3: the location to store the result
 * $4: the array settings
*/
define(`dm4_array_find', `
    -1;

    do {
        size_t __dm4_array_search_index = 0;

        for(__dm4_array_search_index = 0; __dm4_array_search_index < ($1)->logical_size; __dm4_array_search_index++) {
            ifelse(m4_index_list($4, 1), void,
                if(m4_compare(m4_index_list($4, 0), ($1)->contents[__dm4_array_search_index], $2) == 0) {
                    continue;
                }
                ,
                if(m4_index_list($4, 1)(($1)->contents[__dm4_array_search_index], $2) == 0) {
                    continue;
                }
            )

            ($3) = (int) __dm4_array_search_index;
            break;
        }
    } while(0)
')

#endif
