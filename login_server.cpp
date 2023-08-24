/**
 * @file patient_ui_two.hpp
 * @brief Methods in this file takes the patient to the page that shows record or the page that lets the patient add entry to diary 
 * 
 * @author Jessica Liu 
 * @bug No known bugs
*/
#include "clinician.hpp"
#include "db_service.hpp"
#include "family_physician.hpp"
#include "login_server.hpp"
#include "patient.hpp"

#include <iostream>

using namespace std;


LoginServer::LoginServer()
{
}

/**
 * @brief UserService::getUserByName
 * @param userName
 * @return The user retrieved from user table, or nullptr if the user does not exist, or something is wrong.
 */
User* LoginServer::getUserByName(string userName)
{
    // TODO: add userType as parameter
    return nullptr;

    /*
    sqlite3_stmt* stmt;
    sqlite3* db = DBService::GetInstance().getDb();

    cout << "get User By Email ..." << endl;

    string sql = "SELECT user_id, user_name, first_name, last_nam, password, user_type FROM " + USER_TABLE + " WHERE user_name = \"" + userName + "\"";

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Failed to retrieve user by email: " << userName << " error: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        User* u = new User();
        u->setId((const char*)sqlite3_column_text(stmt, 0));
        u->setName((const char*)sqlite3_column_text(stmt, 1));
        u->setFirstName((const char*)sqlite3_column_text(stmt, 2));
        u->setLastName((const char*)sqlite3_column_text(stmt, 3));
        u->setPassword((const char*)sqlite3_column_text(stmt, 4));
        u->setType((const char*)sqlite3_column_text(stmt, 5));
        sqlite3_finalize(stmt);

        cout << "Retrieved user userId: " << u->getId() << " userName: " << u->getName() << " firstName: " << u->getFirstName() << " lastName: " << u->getLastName() << endl;
        return u;
    }

    cerr << "Failed to retrieve user by userName: " << userName << " error: not found ?" << endl;
    return nullptr;
    */
}


/**
 * @brief UserService::getUserById
 * @param userId
 * @param userType
 * @return The user retrieved from user table, or nullptr if the user does not exist, or something is wrong.
 */
User* LoginServer::getUserById(string userId, string userType)
{
    sqlite3_stmt* stmt;
    sqlite3* db = DBService::GetInstance().getDb();

    cout << "get User By userId: " << userId << "  userType: " << userType << endl;

    string sql;
    User* u;
    //get information from database depending on the user type 
    if (userType == "Patient") { 
        sql = "SELECT patientID, name, password FROM medicalRecord WHERE patientID = \"" + userId + "\";";
        u = new Patient();
    } else if (userType == "Family Physician") {
        cout << "in userType == Family Physician ... beginning ..." << endl;
        sql = "SELECT clinicianID, name, password, clinicianType FROM clinician WHERE clinicianID = \"" + userId + "\";";
        u = new FamilyPhysician();
    } else { // Clinician
        sql = "SELECT clinicianID, name, password, clinicianType FROM clinician WHERE clinicianID = \"" + userId + "\";";
        u = new Clinician();
    }

    cout << "sql: " << sql << endl; 
    //retrieve information 
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Failed to retrieve user by ID: " << userId << " error: " << sqlite3_errmsg(db) << endl;
        delete u;
        return nullptr;
    }

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        cout << "in while ..." << endl;

        u->setId(stoi((const char*)sqlite3_column_text(stmt, 0)));
        u->setName((const char*)sqlite3_column_text(stmt, 1));
        u->setPassword((const char*)sqlite3_column_text(stmt, 2));

        if (userType != "Patient") {
            u->setType((const char*)sqlite3_column_text(stmt, 3));
        }

        cout << "before sqlite3_finalize" << endl;
        sqlite3_finalize(stmt);

        cout << "Retrieved user userId: " << u->getId() << " name: " << u->getName() << " password: " << u->getPassword() << endl;
        return u;
    }

    cout << "before return nullptr" << endl;
    delete u;
    return nullptr;
}


/**
 * @brief UserService::login
 * @param user
 * @return when login successful, return user retrieved from user table, otherwise nullptr
 */
User* LoginServer::login(User* user)
{ 
    //verify user 
    User* existing = getUserById(to_string(user->getId()), user->getType());
    if (existing == nullptr) {
        cerr << "login: failed to retrieve the user !" << endl;
        return nullptr;
    }

    if (user->getPassword() != existing->getPassword()) {
        cerr << "login: password does not match !" << endl;
        return nullptr;
    }
    return existing;
}


/**
 * @brief UserService::registerUser
 * @param user
 * @return true when successful, otherwise false
 */
bool LoginServer::registerUser(User* user)
{
    // TODO: change to update clinician and medicalRecord table

    return false;

    /*
    char* err_msg;
    sqlite3* db = DBService::GetInstance().getDb();

    cout << "registering user " << user->getName() << endl;

    User* existing = getUserByName(user->getName());
    if (existing != nullptr) {
        return false;
    }

    // TODO: change password to hash code

    string sql = "INSERT INTO " + USER_TABLE + " (user_name, first_name, last_name, password, user_type) " +
                 "VALUES (\"" + user->getName() + "\", \"" + user->getFirstName() + "\", \"" + user->getLastName() + "\", \"" + user->getPassword() + "\", \"" + user->getType() + "\");";
    cout << "sql: " << sql << endl;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err_msg);

    if (rc != SQLITE_OK) {
        cerr << "Failed to register user: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    cout << "User " << user->getName() << " is registered successfully." << endl;
    return true;
    */
}
