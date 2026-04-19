#include <stdio.h>
#include <string.h>

// هيكل التاريخ
typedef struct {
    int day, month, year;
} Date;


typedef struct {
    int id;
    char name[30];
    char firstName[30];
    Date dob;
    char address[50];
    char tel[15];
} Client;

typedef struct {
    int clientId;
    char type; // P, M, C
    int balance;
    int blocked; // boolea
} Account;

void createAccount() {
    Account newAcc;
    int birthYear;

    printf("\n--- Create New Account ---\n");
    printf("Enter Account Type (P: Individual, M: Minor, C: Commercial): ");
    scanf(" %c", &newAcc.type);

    if (newAcc.type == 'P') {
        printf("Enter birth year: ");
        scanf("%d", &birthYear);
        // شرط السلسلة 1: الفردي يجب أن يكون 18+
        if (2026 - birthYear < 18) {
            printf("Error: Individual must be at least 18 years old.\n");
            return;
        }
    } else if (newAcc.type == 'M') {
        printf("Does the guardian have an account? (1: Yes, 0: No): ");
        int hasGuardian;
        scanf("%d", &hasGuardian);
        if (!hasGuardian) {
            printf("Error: Guardian must have an account.\n");
            return;
        }
    }

    newAcc.balance = 0;
    newAcc.blocked = 0;
    printf("Account created successfully for type %c!\n", newAcc.type);
}
int main() {
    int choice;
    do {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create New Account\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch(choice) {
           case 1:
                createAccount();
                break;
            case 0: 
                printf("Exiting system.\n");
                break;
            default: 
                printf("Invalid choice!\n");
        }
    } while(choice != 0);
    return 0;
}