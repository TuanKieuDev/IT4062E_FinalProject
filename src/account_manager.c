/**
 * Account manager
 */
#include "account_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "config.h"
#include "error.h"

#include "db.h"

/**
 * Find an account with given username
 * Returns pointer to dynamically allocated memory
 */
Account *account_find(char *username)
{
    Account *acc = NULL;
    struct sqlite3 *db = db_get_instance();
    const char *query = "SELECT username, password, is_signed_in FROM account "
                        "WHERE username = ?";
    struct sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, strlen(username), NULL);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        acc = malloc(sizeof(Account));
        strcpy(acc->username, (char *)sqlite3_column_text(stmt, 0));
        strcpy(acc->password, (char *)sqlite3_column_text(stmt, 1));
        acc->is_signed_in = sqlite3_column_int(stmt, 2);
    }

out:
    sqlite3_finalize(stmt);
    return acc;
}

void account_login(const char *username)
{
    struct sqlite3 *db = db_get_instance();
    const char *query = "UPDATE account SET is_signed_in = 1 WHERE username = ?";
    struct sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, strlen(username), NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void account_logout(const char *username)
{
    struct sqlite3 *db = db_get_instance();
    const char *query = "UPDATE account SET is_signed_in = 0 WHERE username = ?";
    struct sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, strlen(username), NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
