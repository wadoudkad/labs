#include <stdio.h>
#include <string.h>

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
                // سنقوم ببرمجة دالة إنشاء الحساب هنا لاحقاً
                printf("Account creation module...\n");
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
