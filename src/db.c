#include "db.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"

#define MAX_SQL_SIZE 3072

sqlite3 *Create_room_sqlite(Package *pkg)
{
    sqlite3 *database;
    char name[23];
    sprintf(name, "%d.db", pkg->group_id);
    int ret = sqlite3_open(name, &database);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(database));
        exit(0);
    }
    return database;
}

void save_chat(Package *pkg)
{
    sqlite3 *database = Create_room_sqlite(pkg);

    char *errmsg = NULL;
    char buf[MAX_SQL_SIZE] = "create table if not exists chat(time TEXT, sender TEXT, message TEXT)";
    int ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("Open table failed\n");
        return;
    }

    time_t t;
    t = time(&t);
    char time[100];
    strcpy(time, ctime(&t));
    int len = strlen(time);
    time[len - 1] = '\0';
    sprintf(buf, "insert into chat values('%s','%s','%s')", time, pkg->sender, pkg->msg);
    ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("Failed to insert data\n");
        return;
    }
    sqlite3_close(database);
}

void drop_table(int group_id)
{
    sqlite3 *database;
    char name[23];
    sprintf(name, "%d.db", group_id);
    int ret = sqlite3_open(name, &database);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(database));
        exit(0);
    }

    char *errmsg = NULL;

    ret = sqlite3_exec(database, "drop table IF EXISTS chat", 0, 0, &errmsg);

    if (ret != SQLITE_OK)
    {

        printf("Error in SQL statement: %s\n", errmsg);

        sqlite3_free(errmsg);
        sqlite3_close(database);
        return;
    }
    printf("Chat table dropped successfully\n");
    sqlite3_close(database);
}

static struct sqlite3 *db = NULL;
static pthread_mutex_t lock;

struct sqlite3 *db_get_instance()
{
    pthread_mutex_lock(&lock);
    if (db)
        goto out;

    if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
        goto out;

    db = NULL;
out:
    pthread_mutex_unlock(&lock);
    return db;
}

void db_close()
{
    sqlite3_close(db);
}
