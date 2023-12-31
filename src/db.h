#ifndef __DB_H__
#define __DB_H__

#include <sqlite3.h>

#include "network.h"

sqlite3 *Create_room_sqlite(Package *pkg);
void save_chat(Package *pkg);
void drop_table(int group_id);

struct sqlite3 *db_get_instance();
void db_close();

#endif
