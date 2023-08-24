/**
 * @file patient.cpp
 * @brief Allows creation of a patient object; to allow for transfer of patient objects between classes
 * 
 * Inherits from User, and each user has an ID, name, type, and password, with getter and setter methods for all attributes
 * A patient also has a birthdate and sex, and getter and setter for these
 * 
 * @author Michael Mendes
 * @bug No known bugs
*/

#include "patient.hpp"

using namespace std;

Patient::Patient(string name, int id, string birthday, string sex)
    : record()
{
    setName(name);
    setId(id);
    setType("Patient");
    setBirth(birthday);
    setSex(sex);
}


string Patient::getBirth() {
    return birthday;
}

string Patient::getSex() {
    return patientSex;
}

void Patient::setBirth(string newBirth) {
    birthday = newBirth;
}

void Patient::setSex(string newSex) {
    patientSex = newSex;
}
