#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the singly linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* create_node(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
   
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a node at the end of the list
struct Node* insert_at_end(struct Node* head, int data) {
    struct Node* new_node = create_node(data);

    if (head == NULL) {
        return new_node; // If the list is empty, the new node becomes the head
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Traverse to the last node
    }
    temp->next = new_node; // Link the new node to the last node
    return head;
}

// Function to convert the linked list into an array
int* convert_to_array(struct Node* head, int* size) {
    int* arr = (int*)malloc(sizeof(int) * 100); // Allocate memory for the array (assuming max size of 100)
    int index = 0;

    struct Node* temp = head;
    while (temp != NULL) {
        arr[index++] = temp->data; // Copy node data into the array
        temp = temp->next; // Move to the next node
    }
    
    *size = index; // Update the size of the array
    return arr; // Return the array
}

// Function to display an array
void display_array(int* arr, int size) {
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int data, n;

    // Input the number of elements
    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);

    // Create the linked list
    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        head = insert_at_end(head, data);
    }

    // Convert the linked list to an array
    int size;
    int* arr = convert_to_array(head, &size);

    // Display the resulting array
    printf("\nLinked List converted to Array:\n");
    display_array(arr, size);

    // Free the allocated memory for the array
    free(arr);

    return 0;
}
