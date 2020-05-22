#ifndef DEUBER_DBMANAGER_H
#define DEUBER_DBMANAGER_H

#include "database/sqlite3.h"

#include <stdexcept>
#include <utility>

namespace DBManager {
    typedef struct {
        sqlite3 *db;
        sqlite3_stmt *stmt;
        char *zErrMsg;
    } db_comp;

    class database_open_error: public std::runtime_error {
    public:
        database_open_error(const char* message, const char* db_name):
                runtime_error(""), msg_(message), db_name_(db_name){}

        database_open_error(std::string message, std::string db_name) :
                runtime_error(""), msg_(std::move(message)), db_name_(std::move(db_name)){}

        ~database_open_error() noexcept override = default;

        const char* what() const noexcept{
            return (msg_ + ". \n Database Name: " + db_name_).c_str();
        }

    protected:
        std::string msg_,db_name_;
    };

    extern bool is_user_registered(const char *username);
    extern bool login_user(const char *username, const char *password);
    extern void sing_up_user(const char *username, const char *password);
    extern void print_users();
}
#endif //DEUBER_DBMANAGER_H
