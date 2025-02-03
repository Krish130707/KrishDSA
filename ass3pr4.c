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

// Function to insert a node at the end of the linked list
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

// Function to display the linked list
void display_list(struct Node* head) {
    struct Node* temp = head;

    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next; // Move to the next node
    }
    
}

int main() {
    int n; // Number of elements in the array
    printf("Enter the size of array : ");
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(n*sizeof(int)));
    struct Node* head = NULL;
    for (int i = 0; i < n; i++) {
    	printf("Ener element number %d : ",i+1);
        scanf("%d", &arr[i]);
    }

    // Copy elements of the array to the linked list
    for (int i = 0; i < n; i++) {
        head = insert_at_end(head, arr[i]);
    }

    // Display the linked list
    printf("Array copied to Linked List:\n");
    display_list(head);

    return 0;
}
