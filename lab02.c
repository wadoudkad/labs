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
void deposit() {
    int id, amount;
    printf("\n--- Deposit Money ---");
    printf("\nEnter Account ID: "); scanf("%d", &id);
    int idx = findIndex(id);

    if (idx != -1) {
        if (accounts[idx].isBlocked) {
            printf("[!] Error: This account is blocked!\n");
            return;
        }
        printf("Enter amount to deposit: "); scanf("%d", &amount);
        if (amount > 0) {
            accounts[idx].balance += amount;
            printf("[+] Success! New Balance: %d\n", accounts[idx].balance);
        } else printf("[!] Invalid amount.\n");
    } else printf("[!] Account not found.\n");
}
void withdraw() {
    int id, amount;
    printf("\n--- Withdraw Money ---");
    printf("\nEnter Account ID: "); scanf("%d", &id);
    int idx = findIndex(id);

    if (idx != -1) {
        if (accounts[idx].isBlocked) {
            printf("[!] Error: Account is blocked!\n");
            return;
        }
        printf("Enter amount to withdraw: "); scanf("%d", &amount);
        if (amount > 0 && amount <= accounts[idx].balance) {
            accounts[idx].balance -= amount;
            printf("[+] Success! New Balance: %d\n", accounts[idx].balance);
        } else printf("[!] Insufficient balance or invalid amount.\n");
    } else printf("[!] Account not found.\n");
}
void transferMoney() {
    int fromId, toId, amount;
    printf("\n--- Transfer Money ---");
    printf("\nEnter your Account ID (Sender): "); scanf("%d", &fromId);
    printf("Enter Receiver Account ID: "); scanf("%d", &toId);

    int fromIdx = findIndex(fromId);
    int toIdx = findIndex(toId);

    if (fromIdx != -1 && toIdx != -1) {
        // التحقق من حالة الحسابات (لا يمكن التحويل من أو إلى حساب مجمد)
        if (accounts[fromIdx].isBlocked || accounts[toIdx].isBlocked) {
            printf("[!] Transfer Failed: One of the accounts is blocked!\n");
            return;
        }

        printf("Enter amount to transfer: "); scanf("%d", &amount);
        
        // التحقق من توفر الرصيد
        if (amount > 0 && amount <= accounts[fromIdx].balance) {
            accounts[fromIdx].balance -= amount; // خصم من المرسل
            accounts[toIdx].balance += amount;   // إضافة للمستقبل
            printf("[+] Success! %d transferred from ID %d to ID %d.\n", amount, fromId, toId);
        } else {
            printf("[!] Transfer Failed: Insufficient balance or invalid amount.\n");
        }
    } else {
        printf("[!] Error: One or both IDs were not found.\n");
    }
}
void updateAccount() {
    int id, choice;
    printf("\n--- Update Account Details ---");
    printf("\nEnter Account ID to modify: "); scanf("%d", &id);
    int idx = findIndex(id);

    if (idx != -1) {
        printf("\nWhat do you want to update?");
        printf("\n1. Customer Name\n2. Account Type (P/M/C)\n3. Block/Unblock Account\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter New Name: "); scanf("%s", accounts[idx].name);
        } else if (choice == 2) {
            printf("Enter New Type: "); scanf(" %c", &accounts[idx].type);
            accounts[idx].type = toupper(accounts[idx].type);
        } else if (choice == 3) {
            accounts[idx].isBlocked = !accounts[idx].isBlocked; // تعكس الحالة الحالية
            printf("Status updated to: %s\n", accounts[idx].isBlocked ? "Blocked" : "Active");
        }
        printf("[+] Update completed successfully!\n");
    } else {
        printf("[!] Error: ID not found.\n");
    }
}
void accountInquiry() {
    int id;
    printf("\n--- Account Inquiry ---");
    printf("\nEnter Account ID: "); scanf("%d", &id);
    int idx = findIndex(id); // نستخدم نفس دالة البحث التي كتبناها سابقاً

    if (idx != -1) {
        printf("\n>>>> Account Details <<<<");
        printf("\nID: %d", accounts[idx].id);
        printf("\nName: %s", accounts[idx].name);
        printf("\nType: %c", accounts[idx].type);
        printf("\nBalance: %d", accounts[idx].balance);
        printf("\nStatus: %s\n", accounts[idx].isBlocked ? "Blocked" : "Active");
    } else {
        printf("[!] Error: ID not found.\n");
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
            case 6: deposit(); break;
            case 7: withdraw(); break;
            case 8: updateAccount(); break;
            case 9: transferMoney(); break;
            case 10: accountInquiry(); break;
            case 0: 
                printf("Exiting system. Goodbye!\n");
                exit(0);
                default: printf("[!] Invalid choice. Try again.\n");
        }
    } while (choice != 0);
    return 0;
}