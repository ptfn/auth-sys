#include <stdlib.h>

#include "db.h"

char *table = "CREATE TABLE Clients ( \
	client_id INTEGER PRIMARY KEY, \
	client_name TEXT,\
	client_key TEXT,\
	client_login TEXT,\
	client_password TEXT);";

int main(void)
{
    sql_t *db = (sql_t*)malloc(sizeof(sql_t));
    char *request = (char*)malloc(MAX_SQL_REQUEST * sizeof(char));
    open_db(db);
    request_to_db(db, table, "Table create");

    client_t *client = (client_t*)malloc(sizeof(client_t));
    client->name = "1";
    client->key = "1";
    client->login = "1";
    client->password = "1";

    add_client(db, client, request);
    close_db(db);

    free(db);
    free(client);
    free(request);
    return 0;
}
