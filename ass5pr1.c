#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct History {
    Node* state;
    struct History* prev;
    struct History* next;
} History;

Node* head = NULL;
History* currentHistory = NULL;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(1);
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* copyList(Node* head) {
    if (!head) return NULL;
    Node* copyHead = NULL;
    Node* copyTail = NULL;
    Node* temp = head;
    do {
        Node* newNode = createNode(temp->data);
        if (!copyHead) {
            copyHead = newNode;
            copyTail = copyHead;
        } else {
            copyTail->next = newNode;
            copyTail = newNode;
        }
        temp = temp->next;
    } while (temp != head);
    copyTail->next = copyHead;
    return copyHead;
}

void saveState() {
    History* newHistory = (History*)malloc(sizeof(History));
    if (!newHistory) exit(1);
    newHistory->state = copyList(head);
    newHistory->prev = currentHistory;
    newHistory->next = NULL;
    if (currentHistory) currentHistory->next = newHistory;
    currentHistory = newHistory;
}

void restoreState(Node* state) {
    if (head) {
        Node* temp = head;
        do {
            Node* next = temp->next;
            free(temp);
            temp = next;
        } while (temp != head);
    }
    head = copyList(state);
}

void undo() {
    if (currentHistory && currentHistory->prev) {
        currentHistory = currentHistory->prev;
        restoreState(currentHistory->state);
    } else {
        printf("No more actions to undo.\n");
    }
}

void redo() {
    if (currentHistory && currentHistory->next) {
        currentHistory = currentHistory->next;
        restoreState(currentHistory->state);
    } else {
        printf("No more actions to redo.\n");
    }
}

void insertAtIndex(int data, int index) {
    saveState();
    Node* newNode = createNode(data);
    if (!head) {
        head = newNode;
        head->next = head;
        return;
    }
    Node* temp = head;
    if (index == 0) {
        newNode->next = head;
        while (temp->next != head) temp = temp->next;
        temp->next = newNode;
        head = newNode;
        return;
    }
    for (int i = 0; temp->next != head && i < index - 1; i++) temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
}

void insertAtBeginning(int data) {
    insertAtIndex(data, 0);
}

void insertAtEnd(int data) {
    saveState();
    Node* newNode = createNode(data);
    if (!head) {
        head = newNode;
        head->next = head;
        return;
    }
    Node* temp = head;
    while (temp->next != head) temp = temp->next;
    temp->next = newNode;
    newNode->next = head;
}

void deleteAtIndex(int index) {
    if (!head) return;
    saveState();
    Node* temp = head;
    Node* prev = NULL;
    if (index == 0) {
        if (head->next == head) {
            free(head);
            head = NULL;
            return;
        }
        while (temp->next != head) temp = temp->next;
        temp->next = head->next;
        free(head);
        head = temp->next;
        return;
    }
    for (int i = 0; temp->next != head && i < index; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (prev) {
        prev->next = temp->next;
        free(temp);
    }
}

void deleteAtBeginning() {
    deleteAtIndex(0);
}

void deleteAtEnd() {
    if (!head) return;
    saveState();
    Node* temp = head;
    Node* prev = NULL;
    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }
    if (prev) prev->next = head;
    else head = NULL;
    free(temp);
}

void displayList() {
    if (!head) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(back to head)\n");
}

void createListFromUserInput() {
    int n, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        insertAtEnd(data);
    }
    saveState();
}

int main() {
    int choice, data, index;
    createListFromUserInput();
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at specific index\n");
        printf("2. Insert at beginning\n");
        printf("3. Insert at end\n");
        printf("4. Delete at specific index\n");
        printf("5. Delete at beginning\n");
        printf("6. Delete at end\n");
        printf("7. Undo\n");
        printf("8. Redo\n");
        printf("9. Display list\n");
        printf("10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter index and value: ");
                scanf("%d %d", &index, &data);
                insertAtIndex(data, index);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
            case 3:
                printf("Enter value: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 4:
                printf("Enter index: ");
                scanf("%d", &index);
                deleteAtIndex(index);
                break;
            case 5:
                deleteAtBeginning();
                break;
            case 6:
                deleteAtEnd();
                break;
            case 7:
                undo();
                break;
            case 8:
                redo();
                break;
            case 9:
                displayList();
                break;
            case 10:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
