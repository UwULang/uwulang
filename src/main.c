/* 
* UwULang, an esoteric programming language with emojis
* More info on https://github.com/UwULang/uwulang 
* Author: @Zeyu-Li 
* License: MIT
*/ 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <argp.h>

#include "preload.h"

// program version
#define VERSION         "0.1.1"

#define STACK_SIZE      512

#define STACK_PUSH(A)   (STACK[SP++] = A)
#define STACK_POP()     (STACK[--SP])
#define STACK_EMPTY()   (SP == 0)
#define STACK_FULL()    (SP == STACK_SIZE)

static char DOC[] = "UwULang, an esoteric programming language with emojis";
const char *argp_program_version = VERSION;

static unsigned short STACK[STACK_SIZE];
static unsigned int SP = 0;

struct Block {
    unsigned char value;
    struct Block* next;
    struct Block* parent;
};

struct Block* next(struct Block* curr) {
    if (curr->next != NULL) {
        return curr->next;
    } else {
        curr->next = (struct Block*)malloc(sizeof (struct Block));
        // init next block
        curr->next->value = 0;
        curr->next->next = NULL;
        curr->next->parent = curr;
        // if next cannot be alloc
        if (curr->next == NULL) 
            return NULL;
        else 
            return curr->next;
    }
}

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

int event_loop(int charCounter, unsigned char code[]) {
    // Use current time as seed for random generator
    srand(time(0));
    
    struct Block UwU = {0, NULL, NULL};

    struct Block* head = &UwU;
    struct Block* curr = &UwU;

    int jump_table[32768] = {0};
    int counter = 0;
    // hash map for pre-complied [] blocks
    for (int i = 0; i < charCounter / 4 + 1; i++) {
        if (code[counter] == 240 && code[counter+1] == 159 && code[counter+2] == 152 && code[counter+3] == 146) {
            STACK_PUSH(i);
        } else if (code[counter] == 240 && code[counter+1] == 159 && code[counter+2] == 152 && code[counter+3] == 161) {
            int start = STACK_POP();
            jump_table[start] = i;
            jump_table[i] = start;
        }
        counter+=4;
    }

    int ptr = 0;
    int codePtr = 0;
    int currChar, nextChar;
    while (code[ptr] != EOF && code[ptr] != '\0') {
        // if not emoji continue
        if (code[ptr] != 240) {
            ptr++;
            continue;
        }
        ptr++;
        if (code[ptr] != 159) {
            ptr++;
            continue;
        }
        ptr++;

        currChar = code[ptr];
        nextChar = code[ptr+1];

        if (currChar == 145 && nextChar == 134) {
            if (curr->value < 255) curr->value++;
            else curr->value = 0;
        }
        else if (currChar == 145 && nextChar == 135) {
            if (curr->value > 0) curr->value--;
            else curr->value = 255;
        }
        else if (currChar == 165 && nextChar == 186) {
            putchar(curr->value);
            // printf("%c", curr->value);
        }
        else if (currChar == 152 && nextChar == 179) curr->value = getchar();
        else if (currChar == 145 && nextChar == 137) curr = next(curr);
        else if (currChar == 145 && nextChar == 136) {
            // if parent exists return parent, otherwise return current
            curr = curr->parent ? curr->parent : curr;
        } else if (currChar == 165 && nextChar == 180) {
            // if parent exists return parent, otherwise return current
            curr->value = rand() % 128;
        } else if (currChar == 152 && nextChar == 146 && curr->value == 0) {
            codePtr = jump_table[codePtr];
            ptr = codePtr * 4 + 2; // get hashed value
        } else if (currChar == 152 && nextChar == 161 && curr->value != 0) {
            // 😡 ]
            codePtr = jump_table[codePtr];
            ptr = codePtr * 4 + 2; // get hashed value
        }

        ptr+=2;
        codePtr++;
    }

    // dealloc from head
    if (head->next != NULL) {
        struct Block* deletePtr = head->next;
        while ((deletePtr = deletePtr->next)) {
            free(deletePtr->parent);
        }
        free(deletePtr);
    }
    // since struct is statically defined, no need to dealloc

    return 0;
}

int file_entry(char* filename) {
    // inital way
    unsigned char code[32768] = {0};

    int charCounter = 0;
    FILE *fp;
    // open file
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error in opening file!\n");
        return 1;
    }
    fscanf(fp, "%[^=]=%[^;]; ", code);
    charCounter = strlen((char*)code);
    fclose(fp);
    event_loop(charCounter, code);
    return 0;
}

void cin_entry() {
    while (1) {                
        unsigned char code[32768] = {0};

        unsigned char currInputChar;
        int charCounter = 0;
        printf("> ");
        while ((currInputChar = getchar()) != EOF && currInputChar != '\n') {
            code[charCounter] = currInputChar;
            charCounter++;
        }
        event_loop(charCounter, code);
    }
}

int preload_entry(char* filename) {
    Tape t;
    size_t initTapeSize = 8; // 8 bytes
    init_tape(&t, initTapeSize);
    fill_tape(&t, initTapeSize, filename);

    // start loop below
    event_loop(t.size, t.data);

    tape_free(&t);
    return 0;
}

static int parse_opt(int key, char *arg, struct argp_state *state) {
    switch (key) {
        case 'v': 
            printf("UwULang %s\n", VERSION);
            break;
        // get from file
        case 'f':
        case 'l':
            // print arg
            // printf("File: %s\n", arg);
            if (file_entry(arg)) {
                return 1;
            }
            break;
        case 'p':
            if (preload_entry(arg)) {
                return 1;
            }
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num == 0) {
                // First argument is provided
                file_entry(arg);
            } else {
                // Too many arguments
                printf("Too many arguments provided\n");
            }
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 1) {
                // No arguments provided, use default
                cin_entry();
            }
            break;
    }
    return 0;
}

/// Main takes in either a single file with file extension uwu
/// or if no args are present will run interpreted on the command line
int main(int argc, char *argv[]) {
    // no buffer when printing
    setbuf(stdout, NULL);

    // if no flags
    // if (argc == 1) {
    //     cin_entry(argv[0]);
    //     return 0;
    // }
    
    struct argp_option options[] = {
        { "file", 'f', "FILE", 0, ".uwu input file"},
        { "filename", 'l', "FILE", 0, ""},
        { "preload", 'p', "FILE", 0, ""},
        { 0 }
    };
    struct argp argp = { options, parse_opt, 0, DOC };
    return argp_parse(&argp, argc, argv, 0, 0, 0); 
}
