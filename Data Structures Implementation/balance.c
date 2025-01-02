#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 1000

// Every time a {[( is identified, push it into the stack
// once a )]} is identified, pop the top element off of stack & check if it matches whats already in the stack
// if delimiters dont match, or stack is empty, print the index for the unexpected delimiter and the closing delimiter encountered
//If the stack is not empty when balance reaches the end of the input, it will print the message
// open followed by a list of closing delimiters in the order needed to balance the string

// stack requirements: pop, push, isEmpty

// DEFINE STACK
typedef struct Stack {
    int top_element_id;
    int arr[MAX_SIZE];
} Stack;

// INITALIZE STACK
void initialize(Stack *stack) {
    stack->top_element_id = -1; // EMPTY
}

// CHECK IF FULL
bool isFull(Stack *stack) {
    return stack->top_element_id == MAX_SIZE - 1;  
}

// PUSH
void push(struct Stack *stack, int item) {
    if (isFull(stack)) {
        return;
    }
    stack->arr[++stack->top_element_id] = item;
}

// CHECK IF STACK IS EMPTY
int isEmpty(struct Stack *stack) {
    return stack->top_element_id == -1;
}

// POP
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->arr[stack->top_element_id--];
}

// BALANCE
void balance (char input[]) {
    struct Stack* check;
    initialize(&check);

    for (int i = 0; i != "/0"; i++) {
        // FOUND OPEN BRACKET? PUSH INTO STACK.
        if (input[i] == "(" || input[i] == "{" || input[i] == "[") {
            push(&check, input[i]);

        // FOUND CLOSED BRACKET? CHECK STACK.
        } else if (input[i] == ")" || input[i] == "}" || input[i] == "]") { 
            if (isEmpty(check)) {
                printf("");
            } else {
                char top = pop(&check);
                if (input[i] == "(" && top == ")" ||
                    input[i] == "{" && top == "}" ||
                    input[i] == "[" && top == "]" ) {
                        printf(input[i]);
                        return;
                }
            }
        }

        if (!isEmpty(&check)) {
            printf("open: ");
            int i = 0;
            while (i < strlen(input)) {
                if (input[i] == "(") {
                    printf(")");
                } else if (input[i] == "{") {
                    printf("}");
                } else {
                    printf("]");
                }
                i++;
            }

        }
    }
}
