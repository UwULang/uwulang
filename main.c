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

    int currChar;
    while ((currChar = getchar()) != EOF && currChar != '\n') {
        // printf("%d", curr.value);
        if (currChar == '+') curr->value++;
        else if (currChar == '-') curr->value--;
        else if (currChar == '.') putchar(curr->value);
        else if (currChar == ',') curr->value = getchar();
        else if (currChar == '>') curr = next(curr);
        else if (currChar == '<') {
            // if parent exists return parent, otherwise return current
            curr = curr->parent ? curr->parent : curr;
        } else if (currChar == '?') {
            // if parent exists return parent, otherwise return current
            curr->value = rand() % 128;
        }
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

// >>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++. 👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆👆🥺
