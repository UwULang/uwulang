/* 
* UwULang (MIT)
*/ 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define STACK_SIZE      512

#define STACK_PUSH(A)   (STACK[SP++] = A)
#define STACK_POP()     (STACK[--SP])
#define STACK_EMPTY()   (SP == 0)
#define STACK_FULL()    (SP == STACK_SIZE)

static unsigned short STACK[STACK_SIZE];
static unsigned int SP = 0;

struct Block {
    unsigned char value;
    struct Block* next;
    struct Block* parent;
} UwU = {0, NULL, NULL};

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

/// Main takes in either a single file with file extension uwu
/// or if no args are present will run interperted on the command line
int main(int argc, char *argv[]) {
    struct Block* head = &UwU;
    struct Block* curr = &UwU;
    // Use current time as seed for random generator
    srand(time(0));

    // inital way
    unsigned char code[32768] = {0};

    unsigned char currInputChar;
    int initCounter = 0;
    int charCounter = 0;
    while ((currInputChar = getchar()) != EOF && currInputChar != '\n') {
        code[initCounter] = currInputChar;
        charCounter++;
        initCounter++;
    }
    // FILE *fptr;
    // // get from cin or file
    // if (argc == 1) {
    //     while ((currInputChar = getchar()) != EOF && currInputChar != '\n') {
    //         *inputCounter = currInputChar;
    //         inputCounter++;
    //         counter++;
    //     }
    // } else {
    //     // open file
    //     printf("%s", argv[1]);
    //     fptr = fprintf(argv[1],"%c", code);
    //     fclose(fptr);
    // }

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
    while (code[ptr] != EOF && code[ptr] != '\n' && code[ptr] != '\0') {
        // printf("%d: %d %d %d %d\n", ptr, code[ptr], code[ptr + 1], code[ptr + 2], code[ptr + 3]);
        // if not emoji continue
        if (code[ptr] != 240) {
            ptr++;
            continue;
        }
        ptr++;
        if (code[ptr] != 159) {
            if (code[ptr] == '\n') break;
            ptr++;
            continue;
        }
        ptr++;
        // printf("%d", *pc);
        currChar = code[ptr];
        nextChar = code[ptr+1];
        // printf("%d", curr.value);
        if (currChar == 145 && nextChar == 134) {
            if (curr->value < 255) curr->value++;
            else curr->value = 0;
        }
        else if (currChar == 145 && nextChar == 135) {
            if (curr->value > 0) curr->value--;
            else curr->value = 255;
        }
        else if (currChar == 165 && nextChar == 186) {
            // putchar(curr->value);
            printf("%c", curr->value);
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

    // new line
    putchar('\n');


    return 0;
}

// tests
// >>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++. 
// 👉👉👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆🥺
