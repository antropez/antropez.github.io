#ifndef Q_ARRAY_H
#define Q_ARRAY_H

#ifndef QARRAY_INITIAL_SIZE
#define QARRAY_INITIAL_SIZE 5
#endif

#ifndef QARRAY_RESIZE
#define QARRAY_RESIZE(current_size) \
    current_size + 5
#endif

/* qarray_init */
#ifndef QARRAY_STACKFUL
#define __qarray_init(qarray, _type, _compare, _free)             \
    calloc(1, sizeof(*qarray));                                   \
    (qarray)->physical_size = QARRAY_INITIAL_SIZE;                  \
    (qarray)->contents = calloc(QARRAY_INITIAL_SIZE, sizeof(_type))

#define qarray_init(qarray, settings) \
    __qarray_init(qarray, settings)
#else
#define qarray_init(qarray, length, block) \
    {0};                                                             \
    qarray.physical_size = length;                                   \
    qarray.contents = block
#endif

/* qarray_insert */
#ifndef QARRAY_STACKFUL
#define __qarray_insert_handle_full(qarray, index, value)                                                            \
    (qarray)->physical_size = QARRAY_RESIZE((qarray)->physical_size);                                                \
    (qarray)->contents = realloc((qarray)->contents, sizeof(*(qarray)->contents) * (size_t) (qarray)->physical_size)
#else
#define __qarray_insert_handle_full(qarray, index, value)                                                                                \
    fprintf(stderr, "qarray_insert: attempt to insert value '%s' into full array '%s'. (%s:%i)\n", #value, #qarray, __FILE__, __LINE__); \
    exit(EXIT_FAILURE)
#endif

#define qarray_insert(qarray, index, value)                                                                                                          \
    if((qarray)->logical_size == (qarray)->physical_size) {                                                                                          \
        __qarray_insert_handle_full(qarray, index, value);                                                                                           \
    }                                                                                                                                                \
                                                                                                                                                     \
    if(index < 0 || index > (qarray)->logical_size) {                                                                                                \
        fprintf(stderr, "qarray_insert: attempt to insert at index %i, out of bounds of array '%s'. (%s:%i)\n", index, #qarray, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                                                                                                          \
    }                                                                                                                                                \
                                                                                                                                                     \
    memmove((qarray)->contents + index + 1, (qarray)->contents + index, sizeof(*(qarray)->contents) * (size_t) ((qarray)->logical_size - index));    \
    (qarray)->contents[index] = value;                                                                                                               \
    (qarray)->logical_size++

/* qarray_pop */
#define qarray_pop(qarray, index, location)                                                                                                       \
    location;                                                                                                                                     \
                                                                                                                                                  \
    if(index < 0 || index >= (qarray)->logical_size) {                                                                                            \
        fprintf(stderr, "qarray_pop: attempt to pop index %i, out of bounds of array '%s'. (%s:%i)\n", index, #qarray, __FILE__, __LINE__);       \
        exit(EXIT_FAILURE);                                                                                                                       \
    }                                                                                                                                             \
                                                                                                                                                  \
    (location) = (qarray)->contents[(index)];                                                                                                     \
    memmove((qarray)->contents + index, (qarray)->contents + index + 1, sizeof(*(qarray)->contents) * (size_t) ((qarray)->logical_size - index)); \
    (qarray)->logical_size--

#endif
