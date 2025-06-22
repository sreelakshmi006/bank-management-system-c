#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[100];
    float balance;
};

void createAccount();
void viewAccount();
void deposit();
void withdraw();
void updateAccount();

int main() {
    int choice;

    while (1) {
        printf("\n===== Bank Management System =====\n");
        printf("1. Create New Account\n");
        printf("2. View Account Details\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Update Account Info\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: updateAccount(); break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank_data.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);
    printf("Account Created Successfully!\n");
}

void viewAccount() {
    struct Account acc;
    FILE *fp = fopen("bank_data.txt", "r");
    int accNo;

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accountNumber == accNo) {
            printf("\nAccount Number: %d\nName: %s\nBalance: %.2f\n",
                   acc.accountNumber, acc.name, acc.balance);
            fclose(fp);
            return;
        }
    }

    printf("Account Not Found!\n");
    fclose(fp);
}

void deposit() {
    struct Account acc;
    FILE *fp = fopen("bank_data.txt", "r+");
    int accNo;
    float amount;

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);
    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accountNumber == accNo) {
            acc.balance += amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);
            printf("Deposit Successful! New Balance: %.2f\n", acc.balance);
            fclose(fp);
            return;
        }
    }

    printf("Account Not Found!\n");
    fclose(fp);
}

void withdraw() {
    struct Account acc;
    FILE *fp = fopen("bank_data.txt", "r+");
    int accNo;
    float amount;

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);
    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accountNumber == accNo) {
            if (acc.balance >= amount) {
                acc.balance -= amount;

                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("Withdrawal Successful! New Balance: %.2f\n", acc.balance);
            } else {
                printf("Insufficient Balance!\n");
            }
            fclose(fp);
            return;
        }
    }

    printf("Account Not Found!\n");
    fclose(fp);
}

void updateAccount() {
    struct Account acc;
    FILE *fp = fopen("bank_data.txt", "r+");
    int accNo;

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number to Update: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accountNumber == accNo) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", acc.name);
            
            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);
            printf("Account Updated Successfully!\n");
            fclose(fp);
            return;
        }
    }

    printf("Account Not Found!\n");
    fclose(fp);
}

