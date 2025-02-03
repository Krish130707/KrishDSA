#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure
struct BankMgmt {
    char AccType[10];
    int AccNumber;
    char CustName[50];
    float AvlBalance;
};

// Function to withdraw money
void withdraw(struct BankMgmt *account) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > account->AvlBalance) {
        printf("Insufficient balance! Cannot withdraw.\n");
    } else {
        account->AvlBalance -= amount;
        printf("Withdrawal successful.\nNew Balance: %.2f\n", account->AvlBalance);
    }
}

// Function to deposit money
void deposit(struct BankMgmt *account) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    account->AvlBalance += amount;
    printf("Deposit successful. New Balance: %.2f\n", account->AvlBalance);
}

// Function to display account details
void display(struct BankMgmt *account) {
    printf("\n--- Account Details ---\n");
    printf("Account Type: %s\n", account->AccType);
    printf("Account Number: %d\n", account->AccNumber);
    printf("Customer Name: %s\n", account->CustName);
    printf("Available Balance: %.2f\n", account->AvlBalance);
    printf("-----------------------\n");
}

int main() {
    struct BankMgmt account;

    // Initialize account details
    printf("Enter Account Type: ");
    scanf("%s", account.AccType);

    printf("Enter Account Number: ");
    scanf("%d", &account.AccNumber);

    printf("Enter Customer Name: ");
    scanf("%s", account.CustName);

    printf("Enter Available Balance: ");
    scanf("%f", &account.AvlBalance);

    int choice;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Withdrawal\n");
        printf("2. Deposit\n");
        printf("3. Display Balance\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                withdraw(&account);
                break;
            case 2:
                deposit(&account);
                break;
            case 3:
                display(&account);
                break;
            case 4:
                printf("Exiting application. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
