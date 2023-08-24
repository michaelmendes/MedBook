/**
 * @file family_physician.cpp
 * @brief Allows creation of a Family Physician user to allow for transfer of Family Physician objects between classes
 * 
 * It inherits from a User, and each user has an ID, name, type, and password, and getter and setter methods for all of these
 * A Family Physician object initializes the id, name, and type of a clinician
 * 
 * @author Michael Mendes
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/
#include "family_physician.hpp"

using namespace std;

FamilyPhysician::FamilyPhysician(string name, int id)
{
    setName(name);
    setId(id);
    setType("Family Physician");
}

void FamilyPhysician::setRequests(std::vector<std::string> requestList)
{
    transferRequests = requestList;
}

vector<string> FamilyPhysician::getRequests()
{
    return transferRequests;
}
