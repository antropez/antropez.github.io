#ifndef Q_ARRAY_COMMON_H
#define Q_ARRAY_COMMON_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include "../qarray.h"

#define STRING_COMPARE(x, y) \
    strcmp(x, y) == 0

#define STRING_SETTINGS char*, STRING_COMPARE,

struct StringArray {
    int logical_size;
    int physical_size;
    char **contents;
};

long extract_error_cb(void (*callback)(), size_t length, char *buffer) {
    int pipes[2] = {0};
    pid_t process_id = -1;

    memset(buffer, 0, length);

    pipe(pipes);
    process_id = fork();

    if(process_id == 0) {
        dup2(pipes[1], STDERR_FILENO);
        callback();
        exit(0);
    }

    return read(pipes[0], buffer, length);
}

#endif
