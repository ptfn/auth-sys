#ifndef _DBLIB_H_
#define _DBLIB_H_

/* Libraries */
#include <sqlite3.h>
#include <stdio.h>

/* Macros */
#define MAX_SQL_REQUEST 1024

/* Struct */
typedef struct {
    sqlite3_stmt *stmt;
    sqlite3 *db;
    char *err;
    int rc;
} sql_t;

typedef struct {
    char *name, *key, *login, *password;
} client_t;
    
typedef struct {
    int client_id, access;
    char *login, *password;
} user_t;

/* Prototype */
int open_db(sql_t *db);
int request_to_db(sql_t *db, char *request, char *text);
int add_client(sql_t *db, client_t *client, char *request);
int close_db(sql_t *db);

#endif

