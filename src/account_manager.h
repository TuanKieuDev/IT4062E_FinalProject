#ifndef __ACCOUNT_MANAGER_H__
#define __ACCOUNT_MANAGER_H__

#define USERNAME_SIZE 256
#define PASSWORD_SIZE 256

typedef struct Account_
{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    int is_signed_in;
} Account;

Account *account_find(char *username);
void account_login(const char *username);
void account_logout(const char *username);

#endif
