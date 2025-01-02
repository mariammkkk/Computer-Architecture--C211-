#include <stdio.h>


// DEFINE NODE
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// CREATE NODE
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// INSERT NODE
void insert(Node** head, int data) {
    Node* newNode = createNode(data);

    // IS IT EMPTY?
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // TRAVERSE TO END OF LIST
    Node* ptr = *head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    // CHECK FOR DUPLICATES
    if (ptr->next != NULL && ptr->next->data == data) {
        free(newNode);
        return;
    }

    // INSERT NEW NODE
    ptr->next = newNode;

}
// DELETE NODE
void delete(Node** head, int target) {
    
    // IS IT EMPTY?
    if (*head == NULL) {
        return;
    }

    Node* ptr = *head;
    Node* prev = NULL;

    // IS THE TARGET THE FIRST NODE?
    if (ptr != NULL && ptr->data == target) {
        *head = ptr->next;
        free(ptr);
        return;
    }

    // FIND TARGET AND DELETE
    while (ptr != NULL && ptr->data == target) {
        prev = ptr;
        ptr = ptr->next;
    }

    // NOT FOUND?
    if (ptr == NULL) {
        return;
    }

    // FREE ? DOUBLE CHECK WHY THIS IS NEEDED.
    prev->next = ptr->next;
    free(ptr);
}

// PRINT

void printList(Node* head) {
    Node* ptr = head;

    // Count number of nodes 
    int count = 0;
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    printf("%d :", count);

    ptr = head;
    while (ptr != NULL) {
        printf("% d", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main () {
    Node* head = NULL;
    char instruction;
    int num;

    while (scanf(" %c %d", &instruction, &num) != EOF) {
        if (instruction == 'i') {
            insert(&head, num);
        } else if (instruction == 'd') {
            delete(&head, num);
        }
        printList(head);
    }

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}