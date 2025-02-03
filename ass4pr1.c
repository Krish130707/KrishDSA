#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a node at a given index (0-based)
void insert_at_index(struct Node** head, int value, int index) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (index == 0) { // Insert at head
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    for (int i = 0; temp != NULL && i < index - 1; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid index! Cannot insert.\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Function to delete a node at a given index (0-based)
void delete_at_index(struct Node** head, int index) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    struct Node* temp = *head;

    if (index == 0) { // Delete first node
        *head = temp->next;
        free(temp);
        return;
    }

    struct Node* prev = NULL;
    for (int i = 0; temp != NULL && i < index; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid index! Cannot delete.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Function to display the linked list
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d   ", temp->data);
        temp = temp->next;
    }
}

// Main function
int main() {
    struct Node* head = NULL;
    int n, value, index, choice;

    // Step 1: Take length of list
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);

    // Step 2: Insert elements at the end (index 0 to n-1)
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        insert_at_index(&head, value, i);
    }

    // Step 3: While loop menu for operations
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at Any Index\n");
        printf("2. Delete at Any Index\n");
        printf("3. Display List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Enter index : ");
                scanf("%d", &index);
                insert_at_index(&head, value, index);
                break;
            case 2:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                delete_at_index(&head, index);
                break;
            case 3:
                display(head);
                break;
            case 4:
                printf("program ends\n");
                return 1;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    }

    return 0;
}
