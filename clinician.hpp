/**
 * @file clinician.hpp
 * @brief Function prototypes for a clinician user to allow for transfer of clinician objects between classes
 * 
 * This defines all the function prototypes for a clinician
 * It inherits from a User, and each user has an ID, name, type, and password, and getter and setter methods for all of these
 * A clinician object initializes the id, name, and type of a clinician
 * 
 * @author Michael Mendes
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/

#ifndef CLINICIAN_HPP
#define CLINICIAN_HPP

#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "user.hpp"

class Clinician : public User
{
public:
	/**
     * @brief Constructor for creating a clinician object and initializing with a name, id, and type
     * @param name The name of the clinician
     * @param id The ID of the clinician
     * @param type The type of the clinician
    */
    Clinician(std::string name="", int id=-1, std::string type="");

};

#endif // CLINICIAN_HPP
