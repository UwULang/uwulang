#ifndef PRELAOD_H
#define PRELAOD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tape {
    uint8_t *data;
    size_t size;
} Tape;

void init_tape(Tape *t, size_t initSize) {
    t->data = (uint8_t *) malloc(initSize * sizeof(uint8_t));
    t->size = 0;
}

void __tape_resize__(Tape *t, size_t *len) { /* should be used by dev only */
    uint8_t *resize = (uint8_t *) realloc(t->data, (size_t) 16 * sizeof(uint8_t));
    if (resize == NULL) {
        printf("Memory reallocation failed, exiting. . .\n");
        free(resize);
        exit(EXIT_FAILURE);
    }

    t->data = resize;
    *len += 16;
    free(resize);
}

void fill_tape(Tape *t, size_t initSize, char *filename) {
   FILE *fp;
   uint8_t b0, b1, b2, b3; /* b for byte */
   size_t len = initSize;

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Preload: Error opening file!\n");
        exit(EXIT_FAILURE);
    }

    do { /* kind of troll solution, but it works */
        if (t->size >= len)
            __tape_resize__(t, &len);
        
        b0 = fgetc(fp);

        if (feof(fp)) /* lol */
            break;        
        
        if (b0 == 0xf0) {
            b1 = fgetc(fp);
            b2 = fgetc(fp);
            b3 = fgetc(fp);

            t->data[t->size] = b0;
            t->data[t->size + 1] = b1;
            t->data[t->size + 2] = b2;
            t->data[t->size + 3] = b3;

            t->size += 4;
            len += 4;
        }
    } while(1);

    //fclose(fp);
}

void tape_free(Tape *t) {
    free(t->data);
    t->data = NULL;
    t->size = 0;
}

#endif /* PRELAOD_H */
