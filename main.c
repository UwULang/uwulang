/* 
* UwULang (MIT)
*/ 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

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
    while ((currInputChar = getchar()) != EOF && currInputChar != '\n') {
        *inputCounter = currInputChar;
        inputCounter++;
    }

    // hash map for pre-complied [] blocks

    int *pc = code;
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
        if (currChar == 145 && nextChar == 134) curr->value++;
        else if (currChar == 145 && nextChar == 135) curr->value--;
        else if (currChar == 165 && nextChar == 186) putchar(curr->value);
        else if (currChar == 152 && nextChar == 179) curr->value = getchar();
        else if (currChar == 145 && nextChar == 137) curr = next(curr);
        else if (currChar == 145 && nextChar == 136) {
            // if parent exists return parent, otherwise return current
            curr = curr->parent ? curr->parent : curr;
        } else if (currChar == 165 && nextChar == 180) {
            // if parent exists return parent, otherwise return current
            curr->value = rand() % 128;
        } else if (currChar == 152 && nextChar == 146) {
            // if parent exists return parent, otherwise return current
            if (curr->value == 0) {
                // go to ']'
                while (*pc != ']') {
                    // stop from going over
                    if (*pc == EOF && *pc == '\0') {
                        pc--;
                        break;
                    }
                    pc++;
                }
            } else {
                stackCount++;
            }
        } else if (currChar == 152 && nextChar == 161) {
            // if parent exists return parent, otherwise return current
            if (curr->value == 0) {
                // go to ']'
                while (*pc != '[') {
                    // stop from going over
                    if (*pc == EOF && *pc == '\0') {
                        pc--;
                        break;
                    }
                    pc--;
                }
            } else {
                if (stackCount <= 0) {
                    // stack error
                    return 1;
                } else {
                    stackCount--;
                }
            }
        }

        pc++;
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
