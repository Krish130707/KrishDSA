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

// Function to insert a new node at the end of the list
struct Node* insert_at_end(struct Node* head, int data) {
    struct Node* new_node = create_node(data);

    if (head == NULL) {
        return new_node; // If the list is empty, the new node becomes the head
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Traverse to the end of the list
    }
    temp->next = new_node; // Link the new node to the last node
    return head;
}

// Function to insert a new node at the beginning of the list
struct Node* insert_at_beginning(struct Node* head, int data) {
    struct Node* new_node = create_node(data); // Create a new node
    new_node->next = head;                    // Link the new node to the current head
    head = new_node;                          // Update head to the new node
    return head;
}

// Function to display the linked list
void display_list(struct Node* head) {
    struct Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main() {
    struct Node* head = NULL;
    int n, data, i;

    // Input the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Create the list by adding nodes at the end
    printf("Enter the elements to create the initial list in order:\n");
    for (i = 0; i < n; i++) {
        printf("Enter the data for node %d: ", i + 1);
        scanf("%d", &data);
        head = insert_at_end(head, data);
    }

    printf("\nInitial Linked List:\n");
    display_list(head);

    // Insert a new node at the beginning
    printf("\nEnter data for the new node to insert at the beginning: ");
    scanf("%d", &data);
    head = insert_at_beginning(head, data);

    printf("\nUpdated Linked List:\n");
    display_list(head);

    return 0;
}
