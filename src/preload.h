#ifndef PRELAOD_H
#define PRELAOD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tape {
    uint8_t *data;
    size_t size;
} Tape;

void init_tape(Tape *t, size_t initSize);
void __tape_resize__(Tape *t, size_t *len);
void fill_tape(Tape *t, size_t initSize, char *filename);
void tape_free(Tape *t);

#endif /* PRELAOD_H */
