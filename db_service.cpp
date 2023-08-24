#include "db_service.hpp"

#include <iostream>

using namespace std;

DBService::DBService()
{
    int rc = sqlite3_open(DB_NAME.c_str(), &db);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return;
    } else {
        cout << "Opened database successfully" << endl;
    }
}


DBService::~DBService()
{
    sqlite3_close(db);
}

std::string DBService::getDbName() {
    return DB_NAME;
}

DBService& DBService::GetInstance() {
    static DBService instance;

    return instance;
}

sqlite3* DBService::getDb() {
    return db;
}

void DBService::exec(string sql) {
    cout << "sql: " << sql << endl;

    char* err_msg;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err_msg);
    if ( rc != SQLITE_OK ){
        cout << "err: " << sqlite3_errmsg(db) << endl;
        sqlite3_free(err_msg);
        //exit(0);
    }
}
