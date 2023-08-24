/**
 * @file patient_ui_two.hpp
 * @brief Methods in this file takes the patient to the page that shows record or the page that lets the patient add entry to diary 
 * 
 * @author Jessica Liu 
 * @bug No known bugs
*/ 
#ifndef LOGIN_SERVER_HPP
#define LOGIN_SERVER_HPP

#include "user.hpp"

class LoginServer
{
private:
    const std::string USER_TABLE = "user";

public:
    LoginServer();
    /**
    * @brief UserService::getUserById
    * @param userId
    * @param userType
    * @return The user retrieved from user table, or nullptr if the user does not exist, or something is wrong.
    */
    User* getUserById(std::string userId, std::string userType); 
    /**
    * @brief UserService::getUserByName
    * @param userName
    * @return The user retrieved from user table, or nullptr if the user does not exist, or something is wrong.
    */
    User* getUserByName(std::string userName); 
    /**
    * @brief UserService::login
    * @param user
    * @return when login successful, return user retrieved from user table, otherwise nullptr
    */
    User* login(User* user); 
    /**
    * @brief UserService::registerUser
    * @param user
    * @return true when successful, otherwise false
    */
    bool registerUser(User* user);

};

#endif // LOGIN_SERVER_HPP
