#include <stdio.h>
#include <string.h>

void rot13 (char input[]) {

    // retrieve input
    // have input displayed as an array of characters
    // loop through each character in the input string
    // find the new letter (check case for lowercase and uppercase) and add to to result
    // display result

    // Create 'result' array with respective length
    int length = strlen(input);
    char result[length + 1];

    // loop through each character and replace it
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] >= 'a' && input[i] <= 'z') { // lowercase
            result[i] = (input[i] - 'a' + 13) % 26 + 'a';
        } else if (input[i] >= 'A' && input[i] <= 'Z') { //upercase
            result[i] = (input[i] - 'A' + 13) % 26 + 'A';
        } else { // non-alphabetic
            result[i] = input[i];
        }
    }

    result[length] = '\0'; // null terminator

    printf("%s\n", result);
}
