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
    char value;
    struct Block* next;
    struct Block* parent;
} UwU = {0, NULL, NULL};

struct Block* next(struct Block* curr) {
    if (curr->next != NULL) {
        return curr->next;
    } else {
        curr->next = malloc(sizeof (struct Block));
        curr->next->value = 0;
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

    // TODO: convert char to UTF-8 emojis

    // inital way
    char code[32768] = {0};

    int currInputChar;
    int *inputCounter = code;
    int counter = 0;
    while ((currInputChar = getchar()) != EOF && currInputChar != '\n') {
        *inputCounter = currInputChar;
        inputCounter++;
        counter++;
    }

    char jump_table[32768] = {0};
    int *preCounter = code;
    // hash map for pre-complied [] blocks
    for (int i = 0; i < counter / 4 + 1; i++) {
        if (*preCounter == 240 && *(preCounter+1) == 159 && *(preCounter+2) == 152 &&  *(preCounter+2) == 146) {
            STACK_PUSH(i);
        } else if (*preCounter == 240 && *(preCounter+1) == 159 && *(preCounter+2) == 152 &&  *(preCounter+2) == 161) {
            int start = STACK_POP();
            jump_table[start] = i;
            jump_table[i] = start;
        }
        // currChar == 152 && nextChar == 161
        preCounter+=4;
    }

    int *pc = code;
    int ptr = 0;
    int currChar, nextChar;
    int stackCount = 0;
    while (*pc != EOF && *pc != '\n' && *pc != '\0') {
        // if not emoji continue
        if (*pc != 240) {
            pc++;
            continue;
        }
        pc++;
        if (*pc != 159) {
            if (*pc == '\n') break;
            pc++;
            continue;
        }
        pc++;
        // printf("%d", *pc);
        currChar = *pc;
        nextChar = *(++pc);
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
            printf("%d ", curr->value);
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
            // [
            // get ptr to right place
            // for (int k = ptr; k < jump_table[ptr]; k++) {
            //     pc-=4;
            // }
            curr->value = jump_table[curr->value]; // get hashed value
        } else if (currChar == 152 && nextChar == 161 && curr->value != 0) {
            // 😡 ]
            // get ptr to right place
            // for (int k = ptr; k > jump_table[ptr]; k--) {
            //     pc-=4;
            // }
            curr->value = jump_table[curr->value]; // get hashed value
        }

        pc++;
        ptr++;
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
