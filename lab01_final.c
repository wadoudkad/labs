#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// --- Data Structures ---
typedef struct {
    int id;
    char name[30];
    char type; // P: Personal, M: Minor, C: Commercial
    int balance;
    bool isBlocked;
} Account;

Account accounts[100];
int accountCount = 0;

// Helper function to find account index by ID
int findIndex(int id) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].id == id) return i;
    }
    return -1;
}

// 1. Create (Add Account)
void addAccount() {
    if (accountCount >= 100) {
        printf("\n[!] Error: Database is full!\n");
        return;
    }
    Account a;
    printf("\n--- Create New Account ---\n");
    printf("Enter Account ID: "); 
    scanf("%d", &a.id);
    printf("Enter Customer Name: "); 
    scanf("%s", a.name);
    printf("Enter Type (P: Personal, M: Minor, C: Commercial): "); 
    scanf(" %c", &a.type);
    
    // Convert to uppercase for case-insensitivity
    a.type = toupper(a.type);
    
    a.balance = 0;
    a.isBlocked = false;
    
    accounts[accountCount++] = a;
    printf("[+] Account created successfully!\n");
}

// 2. Search (Case-insensitive search by Name)
void searchAccount() {
    char searchName[30];
    printf("\nEnter Name to search: "); 
    scanf("%s", searchName);
    bool found = false;

    for (int i = 0; i < accountCount; i++) {
        // strcasecmp ignores upper/lower case differences
        if (strcasecmp(accounts[i].name, searchName) == 0) {
            printf("\nAccount Found:\n");
            printf("ID: %d | Name: %s | Type: %c | Balance: %d | Status: %s\n", 
                    accounts[i].id, accounts[i].name, accounts[i].type, 
                    accounts[i].balance, accounts[i].isBlocked ? "Blocked" : "Active");
            found = true;
        }
    }
    if (!found) printf("[!] Customer not found.\n");
}

// 3. Update (Modify Name)
void updateAccount() {
    int id;
    printf("\nEnter Account ID to update: "); 
    scanf("%d", &id);
    int idx = findIndex(id);
    if (idx != -1) {
        printf("Current Name: %s. Enter New Name: ", accounts[idx].name);
        scanf("%s", accounts[idx].name);
        printf("[+] Update successful!\n");
    } else {
        printf("[!] Account ID not found.\n");
    }
}

// 4. Delete (Remove and Shift)
void deleteAccount() {
    int id;
    printf("\nEnter Account ID to delete: "); 
    scanf("%d", &id);
    int idx = findIndex(id);
    if (idx != -1) {
        // Shifting logic to maintain array continuity
        for (int i = idx; i < accountCount - 1; i++) {
            accounts[i] = accounts[i+1];
        }
        accountCount--;
        printf("[-] Account deleted and database optimized.\n");
    } else {
        printf("[!] Account ID not found.\n");
    }
}

// 5. Display (List all accounts)
void displayAll() {
    if (accountCount == 0) {
        printf("\nDatabase is empty.\n");
        return;
    }
    printf("\n--- All Registered Accounts ---\n");
    for (int i = 0; i < accountCount; i++) {
        printf("%d. ID: %d | Name: %s | Type: %c | Balance: %d | Status: %s\n", 
                i+1, accounts[i].id, accounts[i].name, accounts[i].type, 
                accounts[i].balance, accounts[i].isBlocked ? "Blocked" : "Active");
    }
}

int main() {
    int choice;
    do {
        printf("\n========== BANK MANAGEMENT SYSTEM (LAB 01) ==========\n");
        printf("1. Add Account\n");
        printf("2. Search by Name (Case-Insensitive)\n");
        printf("3. Update Customer Name\n");
        printf("4. Delete Account\n");
        printf("5. Display All Accounts\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addAccount(); break;
            case 2: searchAccount(); break;
            case 3: updateAccount(); break;
            case 4: deleteAccount(); break;
            case 5: displayAll(); break;
            case 0: 
                printf("Exiting system. Goodbye!\n");
                exit(0);
                default: printf("[!] Invalid choice. Try again.\n");
        }
    } while (choice != 0);
    return 0;
}