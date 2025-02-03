#include <stdio.h>
#include <stdlib.h>

// Function to read a matrix
void readMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter element at [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to multiply two matrices
void multiplyMatrices(int **mat1, int **mat2, int **result, int row1, int col1, int row2, int col2) {
    // Initialize the result matrix to 0
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            result[i][j] = 0;
        }
    }

    // Perform matrix multiplication
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            for (int k = 0; k < col1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// Function to display a matrix
void displayMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int row1, col1, row2, col2;

    // Input dimensions of matrices
    printf("Enter the number of rows and columns for FIRST MATRIX: ");
    scanf("%d %d", &row1, &col1);
    printf("Enter the number of rows and columns for SECOND MATRIX: ");
    scanf("%d %d", &row2, &col2);

    // Check if multiplication is possible
    if (col1 != row2) {
        printf("Column of the first matrix must equal the row of the second matrix for multiplication.\n");
        return 1;
    }

    // Dynamic memory allocation for the matrices
    int **mat1 = (int **)malloc(row1 * sizeof(int *));
    for (int i = 0; i < row1; i++) {
        mat1[i] = (int *)malloc(col1 * sizeof(int));
    }

    int **mat2 = (int **)malloc(row2 * sizeof(int *));
    for (int i = 0; i < row2; i++) {
        mat2[i] = (int *)malloc(col2 * sizeof(int));
    }

    int **product = (int **)malloc(row1 * sizeof(int *));
    for (int i = 0; i < row1; i++) {
        product[i] = (int *)malloc(col2 * sizeof(int));
    }

    // Read elements of matrices
    printf("ENTER ELEMENTS OF MATRIX A:\n");
    readMatrix(mat1, row1, col1);
    printf("ENTER ELEMENTS OF MATRIX B:\n");
    readMatrix(mat2, row2, col2);

    // Multiply matrices
    multiplyMatrices(mat1, mat2, product, row1, col1, row2, col2);

    // Display the result
    printf("PRODUCT OF MATRIX A AND MATRIX B:\n");
    displayMatrix(product, row1, col2);

    // Free allocated memory
    for (int i = 0; i < row1; i++) {
        free(mat1[i]);
    }
    free(mat1);

    for (int i = 0; i < row2; i++) {
        free(mat2[i]);
    }
    free(mat2);

    for (int i = 0; i < row1; i++) {
        free(product[i]);
    }
    free(product);

    return 0;
}
