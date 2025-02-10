#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

Node* createNode(int coefficient, int exponent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int coefficient, int exponent) {
    Node* newNode = createNode(coefficient, exponent);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    for (Node* ptr1 = poly1; ptr1 != NULL; ptr1 = ptr1->next) {
        for (Node* ptr2 = poly2; ptr2 != NULL; ptr2 = ptr2->next) {
            int coeff = ptr1->coefficient * ptr2->coefficient;
            int exp = ptr1->exponent + ptr2->exponent;

            Node* temp = result;
            Node* prev = NULL;
            while (temp != NULL && temp->exponent > exp) {
                prev = temp;
                temp = temp->next;
            }

            if (temp != NULL && temp->exponent == exp) {
                temp->coefficient += coeff;
            } else {
                Node* newNode = createNode(coeff, exp);
                if (prev == NULL) {
                    newNode->next = result;
                    result = newNode;
                } else {
                    newNode->next = temp;
                    prev->next = newNode;
                }
            }
        }
    }
    return result;
}

void printPolynomial(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    int isFirstTerm = 1;
    while (poly != NULL) {
        if (poly->coefficient != 0) {
            if (!isFirstTerm && poly->coefficient > 0) {
                printf(" + ");
            } else if (poly->coefficient < 0) {
                printf(" - ");
            }
            printf("%dx^%d", abs(poly->coefficient), poly->exponent);
            isFirstTerm = 0;
        }
        poly = poly->next;
    }
    printf("\n");
}

Node* inputPolynomial() {
    Node* poly = NULL;
    int coeff, exp;
    char choice;
    do {
        printf("Enter coefficient: ");
        scanf("%d", &coeff);
        printf("Enter exponent: ");
        scanf("%d", &exp);
        appendNode(&poly, coeff, exp);
        printf("Do you want to add another term? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
    return poly;
}

int main() {
    printf("Enter the first polynomial:\n");
    Node* poly1 = inputPolynomial();
    printf("Enter the second polynomial:\n");
    Node* poly2 = inputPolynomial();

    Node* product = multiplyPolynomials(poly1, poly2);

    printf("First Polynomial: ");
    printPolynomial(poly1);
    printf("Second Polynomial: ");
    printPolynomial(poly2);
    printf("Product: ");
    printPolynomial(product);

    return 0;
}
