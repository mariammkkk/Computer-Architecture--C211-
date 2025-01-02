#include <stdio.h>
#include <string.h>

// use strcmp to compare strings
// print a new line after each sorting
// if no arguments are passed, exit
// selection sort: find lexicographically smallest string, swap it with first string of unsorted part

void sorta (int len, char arg[]) {

    // Exit if empty
    if (len == '\0') {
        return;
    }

    // find smallest string lexicographically
    for (int i = 0; i < len-1; i++) {
        int minimum_index = i;
        for (int j = 0; j < len; j++) {
            if (strcmp(arg[j], arg[minimum_index] < 0)) {
                minimum_index = j;
            }
        }
        // swap minimum with first element
        if (minimum_index != i) {
            char temp = arg[i];
            arg[i] = arg[minimum_index];
            arg[minimum_index] = temp;
        }
    }

    // finished sorting, now print
    for (int i = 0; i < arg; i++) {
        printf("%s\n", arg[i]);
    }

    return;
}
