/**
 * @file db_service
 * @brief 
 *
 * This class is a singleton class. Is used it to make sure only one db connection is used in all widgets.
 * 
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/

#ifndef DB_SERVICE_HPP
#define DB_SERVICE_HPP
#include <sqlite3.h>
#include <string>


class DBService
{
private:
    const std::string DB_NAME = "../medBook.db";
    sqlite3 *db;

    /**
     * @brief opens the database. 
    */
    DBService();

public:
    /**
     * @brief deconstructor 
    */
    ~DBService();

    /**
     * @brief constructor to ensure that there is only one instance 
    */
    DBService(const DBService &other) = delete;

    /**
     * @brief singletons should not be assignable
    */
    void operator=(const DBService &) = delete;

    /**
     * @brief returns the instance of dbservice
     * @return DBService&
    */
    static DBService& GetInstance();

    /**
     * @brief get the database object
     * @return sqlite3*
    */
    sqlite3 *getDb();
    /**
     * @brief get the database name
     * @return string
    */
    std::string getDbName();
    /**
     * @brief runs a sql statement into the database and error handling 
     * @param sql a string of the sql statement
     * @return string
    */
    void exec(std::string sql);

};

#endif // DB_SERVICE_HPP
