/**
 * Account manager
*/
#include "account_manager.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void write_to_file(Account *list) {

    FILE *fp = fopen("../assets/account.txt", "w");

    if (fp) {
        Account *acc = list;
        while (acc) {
            fprintf(fp, "%s %s %d\n", acc->username, acc->password, acc->status);
            acc = acc->next;
        }

        fclose(fp);
    } else {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }
}

/**
 * read data from txt file
 * Create a linked-list to store account
 * Return a pointer from first account
*/
Account* read_account_list() {

    FILE *fp = fopen("../assets/account.txt", "r");

    Account *list = NULL;
    Account *prev_acc, *acc;

    char username[USERNAME_SIZE + 1];
    char password[PASSWORD_SIZE + 1];
    int status;

    if (fp) {
        while (!feof(fp)) {
            // read data
            fscanf(fp, "%s", username);
            fscanf(fp, "%s", password);
            fscanf(fp, "%d", &status);

            // check empty line
            if (strlen(username) == 0) {
                continue;
            }

            // store value into memory
            acc = (Account *) malloc(sizeof(Account));
            strcpy(acc->username, username);
            strcpy(acc->password, password);
            acc->status = status;
            acc->consecutive_failed_sign_in = 0;
            acc->is_signed_in = 0;

            // add to list
            if (list == NULL) {
                list = acc;
                prev_acc = acc;
            } else {
                prev_acc->next = acc;
                prev_acc = acc;
            }

            // reset value
            strcpy(username, "");
            strcpy(password, "");
        }

        fclose(fp);
    } else {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }

    return list;
}


/**
 * Search account
 * - Found: return account
 * - Not found: return NULL
*/
Account* find_account(Account *list, char *username) {

    Account *acc = list;

    while (acc) {
        if (strcmp(acc->username, username) == 0) {
            return acc;
        }
        acc = acc->next;
    }

    return NULL;
}

/**
 * Check active users
 * - Active: return 1
 * - Lock: return 0
*/
int is_active_account(Account *list, char *username) {
    Account *acc = find_account(list, username);
    if (acc) {
        return acc->status;
    }
    return 1;
}
