#include <stdio.h>
#include <stdlib.h>

void read_matrix(const char *inputfile, double **matrix, int *rows, int *cols, double **target, int isTraining) {
    FILE *file = fopen(inputfile, "r");
    if (file == NULL || matrix == NULL) return;

    fscanf(file, "%*s"); 
    fscanf(file, "%d", cols);
    fscanf(file, "%d", rows);

    *matrix = malloc(*rows * (*cols + 1) * sizeof(double));
    if (isTraining) {
        *target = malloc(*rows * sizeof(double));
    }
    if (*matrix == NULL || (isTraining && *target == NULL)) {
        fclose(file);
        return;
    }

    for (int r = 0; r < *rows; r++) {
        (*matrix)[r * (*cols + 1)] = 1.0; // Bias term
        for (int c = 1; c <= *cols; c++) {
            fscanf(file, "%lf", &(*matrix)[r * (*cols + 1) + c]);
        }
        if (isTraining) { // Train: read and store price in target (Y)
            fscanf(file, "%lf", &(*target)[r]);
        }
    }
    fclose(file);
}

// Need this to transpose X 
void transposeMatrix(int rows, int cols, double *matrix, double *result) {
    if (matrix == NULL || result == NULL) return;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j * rows + i] = matrix[i * cols + j]; // flip
        }
    }
}

// Use this for: (X^T)(X) and (X^T)(Y)
// How to multiply matrices: Multiply each element in a row of the first matrix by the corresponding element in a column of the second matrix, then add the products together.
void multiplyMatrices(int r1, int c1, double *M1, int c2, double *M2, double *product) {
    if (M1 == NULL || M2 == NULL || product == NULL) return;

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            product[i * c2 + j] = 0;
            for (int k = 0; k < c1; k++) {
                product[i * c2 + j] += M1[i * c1 + k] * M2[k * c2 + j];
            }
        }
    }
}

// Find inverse of matrix using Gauss-Jordan Elimination
void findInverse(int n, double *matrix, double *result) {
    if (matrix == NULL || result == NULL) return; 
    
    // Identity Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                result[i * n + j] = 1.0;
            } else {
                result[i * n + j] = 0.0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        double diag = matrix[i * n + i];
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] /= diag;
            result[i * n + j] /= diag;
        }

        for (int j = 0; j < n; j++){
            if (i != j) {
                double factor = matrix[j * n + i];
                for (int k = 0; k < n; k++) {
                    matrix[j * n + k] -= factor * matrix[i * n + k];
                    result[j * n + k] -= factor * result[i * n + k];
                }
            }
        }
    }
}

// Calculating pseudo-inverse: W = (X^T)(X)^-1 * (X^T)(Y)  
void calculatingW(double *X, double *Y, double *W, int rows, int cols) {
    double *transposedX = malloc(cols * rows * sizeof(double));
    double *transposedX_mult_X = malloc(cols * cols * sizeof(double));
    double *transposedX_mult_Y = malloc(cols * sizeof(double));
    double *transposedX_mult_invertedX = malloc(cols * cols * sizeof(double));

    transposeMatrix(rows, cols, X, transposedX); // X^T
    multiplyMatrices(cols, rows, transposedX, cols, X, transposedX_mult_X); // (X^T) * X
    findInverse(cols, transposedX_mult_X, transposedX_mult_invertedX); // (X^T * X)^-1
    multiplyMatrices(cols, rows, transposedX, 1, Y, transposedX_mult_Y); // (X^T) * Y
    multiplyMatrices(cols, cols, transposedX_mult_invertedX, 1, transposedX_mult_Y, W); // (X^T * X)^-1 * (X^T * Y)

    // Free everything
    free(transposedX);
    free(transposedX_mult_X);
    free(transposedX_mult_Y);
    free(transposedX_mult_invertedX);
}

// Once W is calculated, use this with a new set of house attributes X^I to estimate prices for those prices 
// To do this, compute (X^I)(W) = Y^I 
// Estimate prices for new houses
void estimatePrices(int rows, int cols, double *newX, double *W) {
    for (int i = 0; i < rows; i++) {
        newX[i * cols] = 1.0; // Set bias term for each row

        double estimatedPrice = 0.0;
        for (int j = 0; j < cols; j++) {
            estimatedPrice += newX[i * cols + j] * W[j];
        }
        printf("%.0f\n", estimatedPrice); // Print prices
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) return 1; // check arg length

    int rows;
    int cols;
    double *X;
    double *Y;

    // Read "train" file
    read_matrix(argv[1], &X, &rows, &cols, &Y, 1); // Pass Y as target

    // Compute W
    double *W = malloc((cols + 1) * sizeof(double));
    if (W == NULL) {
        free(X);
        free(Y);
        return 1;
    }
    calculatingW(X, Y, W, rows, cols + 1);

    // Read "data" file
    int newRows;
    int newCols;
    double *newX;
    read_matrix(argv[2], &newX, &newRows, &newCols, NULL, 0); // No target needed for data file

    // Ensure newCols matches cols for consistent data
    if (newCols != cols) {
        free(X);
        free(Y);
        free(W);
        free(newX);
        return 1;
    }

    // Estimate prices for new houses
    estimatePrices(newRows, newCols + 1, newX, W);

    // Free everything
    free(X);
    free(Y);
    free(W);
    free(newX);

    return 0;
}
