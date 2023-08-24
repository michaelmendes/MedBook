/**
 * @file user.hpp
 * @brief Function prototypes for user to allow for transfer of user objects between classes
 * 
 * This defines all the function prototypes for a user
 * Each user has an ID, name, type, and password
 * This has getter and setter methods
 * 
 * @author Jessica Liu
 * @bug No known bugs
*/
#ifndef USER__H
#define USER__H

#include <string>

class User
{

    private:
        int userId;
        std::string name;
        std::string password;
        std::string userType;

    public:
        /**
         * @brief Constructor allows the creation of a user object
        */
        User();

        /**
         * @brief getter for the user ID
         * @return the user's ID as an integer
        */
        int getId();

        /**
         * @brief setter for the user ID
         * @param s the integer that is the ID of the user
        */
        void setId(int s);

        /**
         * @brief getter for the user name
         * @return the user's name as a string
        */
        std::string getName();

        /**
         * @brief setter for the user's name
         * @param s the user's name as a string
        */
        void setName(std::string s);

        /**
         * @brief getter for the user's password
         * @return the user's password as a string
        */
        std::string getPassword();

        /**
         * @brief setter for the user's password
         * @param s the user's password as a string
        */
        void setPassword(std::string s);

        /**
         * @brief getter for the type of user; whether its a Patient, Clinician, or Family Physician
         * @return the user's type as a string
        */
        std::string getType();

        /**
         * @brief setter for the type of user
         * @param s the type of user as a string; whether its a Patient, Clinician, or Family Physician
        */
        void setType(std::string s);
};

#endif
