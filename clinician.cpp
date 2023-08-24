/**
 * @file clinician.cpp
 * @brief Allows creation of a clinician user to allow for transfer of clinician objects between classes
 * 
 * This defines all the function prototypes for a clinician
 * It inherits from a User, and each user has an ID, name, type, and password, and getter and setter methods for all of these
 * A clinician object initializes the id, name, and type of a clinician
 * 
 * @author Michael Mendes
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/

#include "clinician.hpp"

using namespace std;


Clinician::Clinician(string name, int id, string type)
{
    setName(name);
    setId(id);
    setType(type);
}


