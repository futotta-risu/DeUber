#include <string>
#include <database/dbManager.h>
#include <util/strings/strings_cpp.h>

#include <iostream>

using namespace DBManager;

const char* callback_data = "Callback function called";

const std::string db_name               =   "../data/database.s3db";

const std::string insert_query          =   "INSERT INTO user (username,password) VALUES ('%un', '%pd');";
const std::string select_query          =   "SELECT username FROM user WHERE username='%un' AND password='%pd'";
const std::string get_all_users         =   "SELECT * FROM user";

const std::string get_user              =   "SELECT username FROM user WHERE username='%un'";

int callback(void* notUser, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void _print_sqlite_error(char *zErrMsg){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
}

int _sqlite3_exec_db(db_comp *db_struct, const char* query){
    return sqlite3_exec(db_struct->db, query, callback, (void*)callback_data, &db_struct->zErrMsg);
}

int _sqlite3_connect(db_comp *db){
    int rc = sqlite3_open(db_name.c_str(), &db->db);
    if(rc)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db->db));

    return rc;
}

std::string _replace_user_pass(std::string main_query, const std::string& username, const  std::string& password){
    replace(main_query,"%un",username);
    replace(main_query,"%pd",password);

    return main_query;
}

bool DBManager::login_user(const char *username, const char *password) {
    db_comp db_struct;
    bool correct_login = true;

    if(_sqlite3_connect(&db_struct) != SQLITE_OK )
        throw DBManager::database_open_error(
                "Could not open database on login.", db_name);

    std::string query_t = select_query;
    std::string query = _replace_user_pass(query_t, username, password);

    if(sqlite3_prepare( db_struct.db, query.c_str() , -1, &db_struct.stmt, nullptr ) != SQLITE_OK) {
        _print_sqlite_error(db_struct.zErrMsg);
        sqlite3_close(db_struct.db);
        return false;
    }

    if (sqlite3_step(db_struct.stmt) == SQLITE_DONE)
        correct_login = false;

    sqlite3_close(db_struct.db);
    return correct_login;
}



void DBManager::sing_up_user(const char *username,const  char *password){
    db_comp db_struct;

    if(_sqlite3_connect(&db_struct) != SQLITE_OK)
        throw DBManager::database_open_error(
                "Could not open database on sing up.", db_name);

    std::string query_t = insert_query;
    std::string query = _replace_user_pass(query_t, username, password);
    if( _sqlite3_exec_db(&db_struct, query.c_str()) != SQLITE_OK )
        _print_sqlite_error(db_struct.zErrMsg);

    sqlite3_close(db_struct.db);
}

bool DBManager::is_user_registered(const char *username){
    db_comp db_struct;

    if(_sqlite3_connect(&db_struct) != SQLITE_OK)
        throw DBManager::database_open_error(
                "Could not open database on sing up.", db_name);

    bool user_exists = true;

    std::string query_t = get_user;
    const char* query = _replace_user_pass(query_t, username, "").c_str();

    if(sqlite3_prepare( db_struct.db, query , -1, &db_struct.stmt, nullptr ) != SQLITE_OK) {
        _print_sqlite_error(db_struct.zErrMsg);
        sqlite3_close(db_struct.db);
        return false;
    }

    if (sqlite3_step(db_struct.stmt) == SQLITE_DONE)
        user_exists = false;

    sqlite3_close(db_struct.db);
    return user_exists;
}

void DBManager::print_users(){
    db_comp db_struct;

    if(_sqlite3_connect(&db_struct) != SQLITE_OK)
        throw DBManager::database_open_error(
                "Could not open database on sing up.", db_name);

    if( _sqlite3_exec_db(&db_struct, get_all_users.c_str()) != SQLITE_OK )
        _print_sqlite_error(db_struct.zErrMsg);

    sqlite3_close(db_struct.db);
}