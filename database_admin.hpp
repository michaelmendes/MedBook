/**
 * @file database_admin
 * @brief deal with the database table creation
 *
 * This file is used to create the databse tables and the database pointer. 
 * It also deletes the database table and returns the pointer and name.
 * 
 * @author Shruthi Sundararaman
 * @author Rhea Mangat
 * @bug No known bugs
*/


#ifndef DATABASEADMIN_HPP
#define DATABASEADMIN_HPP

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "patient.hpp"


class DatabaseAdmin {
    private:
      	sqlite3 *db;

    public:
  		/**
         * @brief constructor that resets the database table with information
         */
        DatabaseAdmin();
		 /**
         * @brief deconstructor
         */
        ~DatabaseAdmin();
  		/**
         * @brief creates the database tables required for the program
         * @return void
         */
        void createDatabaseTables();
  		/**
         * @brief fills the database with information to be used during the demo and testing
         * @return void
         */
        void setDatabaseRandom();
  		/**
         * @brief deletes the database tables
         * @return void
         */
        void deleteDatabaseTables();
    	 /**
         * @brief returns the pointer to the database object
         * @return sqlite3*
         */
        sqlite3* getDBobject();
  		/**
         * @brief returns the database name as a string
         * @return string
         */
        std::string getDBname();
};

#endif // DATABASEADMIN_HPP
