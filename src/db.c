#include "db.h"

int open_db(sql_t *db)
{
    db->rc = sqlite3_open("auth.db", &db->db);
    if (db->rc != SQLITE_OK) {
        sqlite3_close(db->db);
        return 1;
    }
    return 0;
}

int request_to_db(sql_t *db, char *request, char *text)
{
    db->rc = sqlite3_exec(db->db, request, 0, 0, &db->err);
    if (db->rc != SQLITE_OK) {
        sqlite3_free(db->err);
        return 1;
    }
    return 0;
}

int close_db(sql_t *db)
{
    int res = sqlite3_close(db->db);
    if (res != SQLITE_OK)
        return 1;
    return 0;
}

int add_client(sql_t *db, client_t *client, char *request)
{
    sprintf(request, "INSERT INTO Clients \
                     (client_name, client_key, client_login, client_password) \
                     VALUES ('%s', '%s', '%s', '%s');",
            client->name, client->key, client-> login, client->password);
    return request_to_db(db, request, "Added client");
}

