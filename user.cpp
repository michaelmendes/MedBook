/**
 * @file user.cpp
 * @brief Allows creation of a User object; to allow for transfer of User objects between classes
 * 
 * Each user has an ID, name, type, and password
 * This has getter and setter methods for all attributes
 * 
 * @author Jessica Liu
 * @bug No known bugs
*/

#include <string>
#include "user.hpp"

using namespace std;

User::User(){
}

int User::getId(){
    return userId;
}

void User::setId(int s){
    userId = s;
}

string User::getName(){
    return name;
}

void User::setName(string s){
    name = s;
}

string User::getPassword(){
    return password;
}

void User::setPassword(string s){
    password = s;
}

string User::getType(){
    return userType;
}

void User::setType(string s){
    userType = s;
}
