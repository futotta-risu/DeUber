#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "database/sqlite3.h"
#include "database/dbManager.h"

static int callback(void* ola, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Devuelve 1 == login correcto, Devuelve 0 == login incorrecto
int iniciarSesion(const char *nombre, const char *pass) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("database.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create merged SQL statement */
    //sql = "SELECT from USUARIO where NOMBRE = '" + static_cast<std::string>(nombre) + "' and pass = '" + static_cast<std::string>(pass) + "'; ";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    } else {
        fprintf(stdout, "Operation done successfully\n");
        return 1;
    }
    
    sqlite3_close(db);
}


int registro(const char *nombre,const  char *pass) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("database.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create merged SQL statement */
    //sql = "INSERT INTO USUARIO (ID_USUARIO,NOMBRE,pass) VALUES ('"+ static_cast<std::string>(id) +"', '"+ static_cast<std::string>(nombre)+"', '" + static_cast<std::string>(nombre) + "');";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    
    sqlite3_close(db);

    return 0;
}

