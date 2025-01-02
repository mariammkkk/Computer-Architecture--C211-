#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int sz = 0; 
int gtsz = 0;

typedef struct{
    char name[20];
    int val;
    char type[20];
} Node; 

typedef struct{
    char op[20];
    char left[20];
    char right[20];
    char output[20];
    Node* selector; 
    Node* inputs;
    int sel;
} Gate;

int power(int n){
    return 1 << n; // 2^n
}

int** mallocArray(int rows, int cols) {
    int **mx = (int**)malloc(rows * sizeof(int*));
    if (!mx) return NULL;

    for (int i = 0; i < rows; i++) {
        mx[i] = (int*)malloc(cols * sizeof(int));
        if (!mx[i]) { 
            for (int j = 0; j < i; j++) {
                free(mx[j]); 
            }
            free(mx);
            return NULL;
        }
    }
    return mx;
}

void freeArray(int** array, int rows) {
    if (array) {
        for (int i = 0; i < rows; i++) {
            free(array[i]); 
        }
        free(array);
    }
}

void insert_node_into_dictionary(Node* array, char* in){
    strcpy(array[sz].name, in);
    strcpy(array[sz].type, "TEMP");
    sz = sz + 1; 
}

int find_node_by_name(Node *array, char *x){
    for(int k = 0; k < sz; k++){
        int result = strcmp(array[k].name, x);
        if (result == 0){
            return k;
        }
    }
    return -1;
}

void and(Node* dictionary, char* left, char* right, char* outputt){
    int left_index = find_node_by_name(dictionary, left);
    if(left_index == -1) {
        insert_node_into_dictionary(dictionary, left);
        dictionary[sz - 1].val = atoi(left);
        left_index = sz - 1;
    }

    int right_index = find_node_by_name(dictionary, right);
    if(right_index == -1) {
        insert_node_into_dictionary(dictionary, right);
        dictionary[sz - 1].val = atoi(right);
        right_index = sz - 1;
    }

    int output_index = find_node_by_name(dictionary, outputt);
    if(output_index == -1) {
        insert_node_into_dictionary(dictionary, outputt);
        output_index = sz - 1;
    }

    if(dictionary[left_index].val == 1 && dictionary[right_index].val == 1){
        dictionary[output_index].val = 1;
    } else {
        dictionary[output_index].val = 0;
    }
}

void or(Node* dictionary, char* left, char* right, char* outputt){
    int left_index = find_node_by_name(dictionary, left);
    if(left_index == -1) {
        insert_node_into_dictionary(dictionary, left);
        dictionary[sz - 1].val = atoi(left);
        left_index = sz - 1;
    }
    int right_index = find_node_by_name(dictionary, right);
    if(right_index == -1) {
        insert_node_into_dictionary(dictionary, right);
        dictionary[sz - 1].val = atoi(right);
        right_index = sz - 1;
    }
    int output_index = find_node_by_name(dictionary, outputt);
    if(output_index == -1) {
        insert_node_into_dictionary(dictionary, outputt);
        output_index = sz - 1;
    }
    
    if(dictionary[left_index].val == 1 || dictionary[right_index].val == 1) {
        dictionary[output_index].val = 1;
    }
    else {
        dictionary[output_index].val = 0;
    }
}

void xor(Node* dictionary, char* left, char* right, char* outputt){
    int left_index = find_node_by_name(dictionary, left);

    if(left_index == -1) {
        insert_node_into_dictionary(dictionary, left);
        dictionary[sz - 1].val = atoi(left);
        left_index = sz - 1;
    }

    int right_index = find_node_by_name(dictionary, right);

    if (right_index == -1) {
        insert_node_into_dictionary(dictionary, right);
        dictionary[sz - 1].val = atoi(right);
        right_index = sz - 1;
    }

    int output_index = find_node_by_name(dictionary, outputt);
    if(output_index == -1) {
        insert_node_into_dictionary(dictionary, outputt);
        output_index = sz - 1;
    }

    if(dictionary[left_index].val == 1 && dictionary[right_index].val == 1) {
        dictionary[output_index].val = 0;
    } else if (dictionary[left_index].val == 1 || dictionary[right_index].val == 1) {
        dictionary[output_index].val = 1;
    } else {
        dictionary[output_index].val = 0;
    }
}

void nand(Node* dictionary, char* left, char* right, char* outputt){
    int left_index = find_node_by_name(dictionary, left);
    if(left_index == -1) {
        insert_node_into_dictionary(dictionary, left);
        dictionary[sz - 1].val = atoi(left);
        left_index = sz - 1;
    }
    int right_index = find_node_by_name(dictionary, right);
    if(right_index == -1) {
        insert_node_into_dictionary(dictionary, right);
        dictionary[sz - 1].val = atoi(right);
        right_index = sz - 1;
    }
    int output_index = find_node_by_name(dictionary, outputt);
    if(output_index == -1) {
        insert_node_into_dictionary(dictionary, outputt);
        output_index = sz - 1;
    }

    if(dictionary[left_index].val == 1 && dictionary[right_index].val == 1){
        dictionary[output_index].val = 0;
    }
    else{
        dictionary[output_index].val = 1;
    }
}

void not(Node* dictionary, char* left, char* outputt){
    int left_index = find_node_by_name(dictionary, left);
    if(left_index == -1){
        insert_node_into_dictionary(dictionary, left);
        dictionary[sz - 1].val = atoi(left);
        left_index = sz - 1;
    }
    int output_index = find_node_by_name(dictionary, outputt);
    if(output_index == -1) {
        insert_node_into_dictionary(dictionary, outputt);
        output_index = sz - 1;
    }

    if(dictionary[left_index].val == 1){
        dictionary[output_index].val = 0;
    }
    else{
        dictionary[output_index].val = 1;
    }
}

void create_truth_table(int** table, int rows, int cols) {
    int x = rows;
    int y = 1;
    int j = 0;
    for (int a = 0; a < cols; a++) {
        x /= 2;  
        for (int m = 0; m < y; m++) {
            for (int n = 0; n < x; n++) {
                table[j][a] = 0;
                j++;
            }
            for (int n = 0; n < x; n++) {
                table[j][a] = 1;
                j++;
            }
        }
        j = 0;  
        y *= 2;
    }
}

int andOp(int x, int y) {
    return x && y;
}

int orOp(int x, int y) {
    return x || y;  
}

int notOp(int x) {
    return !x;
}

int MULTIPLEXER(Node* dictionary, Node* D, Node* S, int** array, int rows, int cols) {
    create_truth_table(array, rows, cols);

    int last = 0; 
    for (int i = 0; i < rows; i++) {
        int curr = (strcmp(D[i].name, "0") == 0 || strcmp(D[i].name, "1") == 0) 
                            ? atoi(D[i].name)  
                            : dictionary[find_node_by_name(dictionary, D[i].name)].val; 
        for (int j = 0; j < cols; j++) {
            int selector = dictionary[find_node_by_name(dictionary, S[j].name)].val;
            if (array[i][j] == 0) {
                selector = notOp(selector);  
            }
            curr = andOp(curr, selector); 
        }
        
        last = (i == 0) ? curr : orOp(last, curr);
    }
    return last;
}

void decoder(Node* dictionary, Node* inp, Node* outp, int** array, int rows, int cols) {
    create_truth_table(array, rows, cols);

    int currentOutput;

    for (int i = 0; i < rows; i++) {
        currentOutput = 1;

        for (int j = 0; j < cols; j++) {
            int index = find_node_by_name(dictionary, inp[j].name);
            int inputValue = dictionary[index].val;

            if (array[i][j] == 0) {
                inputValue = notOp(inputValue);
            }

            currentOutput = (j == 0) ? inputValue : andOp(currentOutput, inputValue);
        }

        int outputIndex = find_node_by_name(dictionary, outp[i].name);
        if (outputIndex == -1) {
            insert_node_into_dictionary(dictionary, outp[i].name);
            outputIndex = sz - 1;
        }
        dictionary[outputIndex].val = currentOutput;
    }
}

int main(int argc, char** argv) {
    Node* dictionary = (Node*)malloc(50 * sizeof(Node));

    Gate* gate = (Gate*)malloc(50 * sizeof(Gate));  
    // MEMORY ALLOCATION
    for (int i = 0; i < 50; i++) {
        gate[i].inputs = (Node*)malloc(50 * sizeof(Node));   
        gate[i].selector = (Node*)malloc(50 * sizeof(Node));  
    }

    // OPEN
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) exit(EXIT_FAILURE);

    // INPUT
    char str[16];
    fscanf(file, "%s", str);
    int numOfIn; 
    fscanf(file, "%d", &numOfIn);
    char in[16];
    for (int i = 0; i < numOfIn; i++) {
        fscanf(file, "%s", in);
        strcpy(dictionary[i].name, in);
        strcpy(dictionary[i].type, "INPUT");
        sz++;
    }

    // OUTPUT
    fscanf(file, "%s", str);
    int output_count; 
    fscanf(file, "%d", &output_count);
    char outputt[16];
    int s = sz;
    for (int i = s; i < output_count + s; i++) {
        fscanf(file, "%s", outputt);
        strcpy(dictionary[i].name, outputt);
        strcpy(dictionary[i].type, "OUTPUT");
        sz++;
    }

    // GATES
    while (fscanf(file, "%s", str) != EOF) {
        if (strcmp(str, "AND") == 0 || strcmp(str, "NAND") == 0 || strcmp(str, "OR") == 0 || strcmp(str, "XOR") == 0 || strcmp(str, "NOR") == 0) {
            strcpy(gate[gtsz].op, str);
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].left, str);
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].right, str);
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].output, str);
            gtsz++;
        }
        if (strcmp(str, "NOT") == 0 || strcmp(str, "PASS") == 0) {
            strcpy(gate[gtsz].op, str);
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].left, str);
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].output, str);
            gtsz++;
        }
        if (strcmp(str, "MULTIPLEXER") == 0) {
            strcpy(gate[gtsz].left, "null");
            strcpy(gate[gtsz].right, "null");
            strcpy(gate[gtsz].op, str);
            int selector_count = 0; 
            fscanf(file, "%d", &selector_count);
            gate[gtsz].sel = selector_count;
            int y = power(selector_count);
            char word[20];
            for (int i = 0; i < y; i++) {
                fscanf(file, "%s", word);
                strcpy(gate[gtsz].inputs[i].name, word);
            }
            for (int i = 0; i < selector_count; i++) {
                fscanf(file, "%s", word);
                strcpy(gate[gtsz].selector[i].name, word);
            }
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].output, str);
            gtsz++;
        }
        if (strcmp(str, "DECODER") == 0) {
            strcpy(gate[gtsz].left, "null");
            strcpy(gate[gtsz].right, "null");
            strcpy(gate[gtsz].output, "null");
            strcpy(gate[gtsz].op, str);
            int selector_count = 0; 
            fscanf(file, "%d", &selector_count);
            gate[gtsz].sel = selector_count;
            char word[20];
            for (int i = 0; i < selector_count; i++) {
                fscanf(file, "%s", word);
                strcpy(gate[gtsz].inputs[i].name, word);
            }
            int y = power(selector_count);
            for (int i = 0; i < y; i++) {
                fscanf(file, "%s", word);
                strcpy(gate[gtsz].selector[i].name, word);
            }
            gtsz++;
        }
        if (strcmp(str, "PASS") == 0) {
            strcpy(gate[gtsz].op, str);
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].left, str);
            fscanf(file, "%s", str);
            strcpy(gate[gtsz].output, str);
        }
    }

    int rows = power(numOfIn);
    int cols = numOfIn; 
    int** table = mallocArray(rows, cols);
    create_truth_table(table, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dictionary[j].val = table[i][j];
            printf("%d ", table[i][j]);
        }
        printf("|");
        for (int j = 0; j < gtsz; j++) {
            if (strcmp(gate[j].op, "AND") == 0) {
                and(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if (strcmp(gate[j].op, "NAND") == 0) {
                nand(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if (strcmp(gate[j].op, "OR") == 0) {
                or(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if (strcmp(gate[j].op, "XOR") == 0) {
                xor(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if (strcmp(gate[j].op, "NOT") == 0) {
                not(dictionary, gate[j].left, gate[j].output);
            }
            if (strcmp(gate[j].op, "NOR") == 0) {
                or(dictionary, gate[j].left, gate[j].right, gate[j].output);
                not(dictionary, gate[j].left, gate[j].output);
            }
            if (strcmp(gate[j].op, "MULTIPLEXER") == 0) {
                int c = gate[j].sel;
                int r = power(c);
                int** arr = mallocArray(r, c);
                int i = MULTIPLEXER(dictionary, gate[j].inputs, gate[j].selector, arr, r, c);
                int DICT = find_node_by_name(dictionary, gate[j].output);
                if (DICT == -1) {
                    insert_node_into_dictionary(dictionary, gate[j].output);
                    DICT = sz - 1;
                }
                dictionary[DICT].val = i;
                freeArray(arr, r);
            }
            if (strcmp(gate[j].op, "DECODER") == 0) {
                int c = gate[j].sel;
                int r = power(c);
                int** arr = mallocArray(r, c);
                decoder(dictionary, gate[j].inputs, gate[j].selector, arr, r, c);
                freeArray(arr, r);
            }
            if (strcmp(gate[j].op, "PASS") == 0) {
                int xIn = find_node_by_name(dictionary, gate[j].left);
                if (xIn == -1) {
                    insert_node_into_dictionary(dictionary, gate[j].left);
                    xIn = sz - 1;
                }
                int xOut = find_node_by_name(dictionary, gate[j].output);
                if (xOut == -1) {
                    insert_node_into_dictionary(dictionary, gate[j].output);
                    xOut = sz - 1;
                }
                dictionary[xOut].val = dictionary[xIn].val;
            }
        }

        for (int i = 0; i < sz; i++) {
            if (strcmp(dictionary[i].type, "OUTPUT") == 0) {
                printf(" %d", dictionary[i].val);
            }
        }

        printf("\n");
    }

    freeArray(table, rows);

    // FREE

    for (int i = 0; i < 50; i++) {
        free(gate[i].inputs);
        free(gate[i].selector);
    }
    free(gate);

    free(dictionary);
    fclose(file); // CLOSE
}