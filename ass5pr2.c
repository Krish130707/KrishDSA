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

Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent == poly2->exponent) {
            int sumCoeff = poly1->coefficient + poly2->coefficient;
            if (sumCoeff != 0) {
                appendNode(&result, sumCoeff, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exponent > poly2->exponent) {
            appendNode(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else {
            appendNode(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        appendNode(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        appendNode(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
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
            } else if (!isFirstTerm && poly->coefficient < 0) {
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

    Node* sum = addPolynomials(poly1, poly2);

    printf("First Polynomial: ");
    printPolynomial(poly1);
    printf("Second Polynomial: ");
    printPolynomial(poly2);
    printf("Sum: ");
    printPolynomial(sum);

    return 0;
}
