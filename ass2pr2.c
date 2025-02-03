#include <stdio.h>
#include <stdlib.h>

// Define a structure to hold two integer pointers
struct Arrays {
    int *arr1;
    int *arr2;
};

// Function to read the elements of the first array
void readArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter element at position %d: ", i + 1);
        scanf("%d", (arr + i));
    }
}

// Function to process the arrays
void processArrays(struct Arrays *arrays, int size) {
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            *(arrays->arr2 + i) = *(arrays->arr1 + i);  // Copy element from arr1
        } else {
            // Handle odd indices (except the last element)
            if (i == size - 1) {
                *(arrays->arr2 + i) = *(arrays->arr1 + i);  // Copy the last element
            } else {
                *(arrays->arr2 + i) = (*(arrays->arr1 + (i - 1))) * (*(arrays->arr1 + (i + 1)));  // Replace odd indices
            }
        }
    }
}

// Function to display an array
void displayArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int main() {
    int size;

    printf("Enter the size of the arrays: ");
    scanf("%d", &size);

    // Allocate memory for the structure and its members
    struct Arrays arrays;
    arrays.arr1 = (int *)malloc(size * sizeof(int));
    arrays.arr2 = (int *)malloc(size * sizeof(int));

    if (arrays.arr1 == NULL || arrays.arr2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Read elements of the first array
    printf("Enter elements of the first array:\n");
    readArray(arrays.arr1, size);

    // Process the arrays
    processArrays(&arrays, size);

    // Display the second array
    printf("Elements of the second array:\n");
    displayArray(arrays.arr2, size);

    // Free dynamically allocated memory
    free(arrays.arr1);
    free(arrays.arr2);

    return 0;
}
