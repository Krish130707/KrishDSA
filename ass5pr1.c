#include <stdio.h>
#include <stdlib.h>

// Node structure for circular linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// History structure for undo/redo (Doubly Circular Linked List)
typedef struct History {
    Node* head;
    struct History* prev;
    struct History* next;
} History;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = new_node->prev = new_node;  // Circular link
    return new_node;
}

// Global history pointers for undo/redo
History* history_head = NULL;
History* current_state = NULL;

// Function to save history for undo/redo
void save_state(Node* head) {
    History* new_history = (History*)malloc(sizeof(History));
    new_history->head = head;
    new_history->next = NULL;

    if (history_head == NULL) {
        new_history->prev = new_history;
        new_history->next = new_history;
        history_head = new_history;
    } else {
        new_history->prev = current_state;
        new_history->next = current_state->next;
        current_state->next->prev = new_history;
        current_state->next = new_history;
    }

    current_state = new_history;
}

// Function to insert at the end (Used for initial setup)
void insert_at_end(Node** head, int data) {
    Node* new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* tail = (*head)->prev;
        new_node->next = *head;
        new_node->prev = tail;
        tail->next = new_node;
        (*head)->prev = new_node;
    }
}

// Function to take initial list input
void create_initial_list(Node** head) {
    int n, data;
    printf("Enter the size of the list: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("List must have at least one element!\n");
        return;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insert_at_end(head, data);
    }

    save_state(*head);
}

// Function to insert at the beginning
void insert_at_beginning(Node** head, int data) {
    Node* new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* tail = (*head)->prev;
        new_node->next = *head;
        new_node->prev = tail;
        tail->next = new_node;
        (*head)->prev = new_node;
        *head = new_node;
    }

    save_state(*head);
}

// Function to insert at a specific index
void insert_at_index(Node** head, int data, int index) {
    if (index == 0) {
        insert_at_beginning(head, data);
        return;
    }

    Node* new_node = create_node(data);
    Node* temp = *head;
    int i = 0;

    while (temp->next != *head && i < index - 1) {
        temp = temp->next;
        i++;
    }

    new_node->next = temp->next;
    new_node->prev = temp;
    temp->next->prev = new_node;
    temp->next = new_node;

    save_state(*head);
}

// Function to delete from a specific index
void delete_at_index(Node** head, int index) {
    if (*head == NULL) return;

    Node* temp = *head;
    if (index == 0) {
        *head = temp->next;
        (*head)->prev = temp->prev;
        temp->prev->next = *head;
        free(temp);
        save_state(*head);
        return;
    }

    int i = 0;
    while (temp->next != *head && i < index) {
        temp = temp->next;
        i++;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);

    save_state(*head);
}

// Function to delete from the beginning
void delete_at_beginning(Node** head) {
    if (*head == NULL) return;
    delete_at_index(head, 0);
}

// Function to delete from the last position
void delete_at_end(Node** head) {
    if (*head == NULL) return;

    Node* tail = (*head)->prev;
    tail->prev->next = *head;
    (*head)->prev = tail->prev;

    free(tail);
    save_state(*head);
}

// Undo function
void undo(Node** head) {
    if (current_state->prev != history_head) {
        current_state = current_state->prev;
        *head = current_state->head;
        printf("Undo successful!\n");
    } else {
        printf("No more undo available!\n");
    }
}

// Redo function
void redo(Node** head) {
    if (current_state->next != history_head) {
        current_state = current_state->next;
        *head = current_state->head;
        printf("Redo successful!\n");
    } else {
        printf("No more redo available!\n");
    }
}

// Function to print the list
void print_list(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(Circular)\n");
}

// Main function
int main() {
    Node* head = NULL;
    int choice, data, index;

    // Create initial list
    create_initial_list(&head);

    while (1) {
        printf("\n1. Insert at Beginning\n2. Insert at Index\n3. Insert at End\n");
        printf("4. Delete at Beginning\n5. Delete at Index\n6. Delete at End\n");
        printf("7. Undo\n8. Redo\n9. Print List\n10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_at_beginning(&head, data);
                break;
            case 2:
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter data: ");
                scanf("%d", &data);
                insert_at_index(&head, data, index);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_at_end(&head, data);
                break;
            case 4:
                delete_at_beginning(&head);
                break;
            case 5:
                printf("Enter index: ");
                scanf("%d", &index);
                delete_at_index(&head, index);
                break;
            case 6:
                delete_at_end(&head);
                break;
            case 7:
                undo(&head);
                break;
            case 8:
                redo(&head);
                break;
            case 9:
                print_list(head);
                break;
            case 10:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
