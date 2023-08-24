/**
 * @file family_physician.hpp
 * @brief Function prototypes for a Family Physician user to allow for transfer of Family Physician objects between classes
 * 
 * This defines all the function prototypes for a Family Physician
 * It inherits from a User, and each user has an ID, name, type, and password, and getter and setter methods for all of these
 * A Family Physician object initializes the id, name, and type of a clinician
 * 
 * @author Michael Mendes
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/

#ifndef FAMILYPHYSICIAN_HPP
#define FAMILYPHYSICIAN_HPP

#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "clinician.hpp"

class FamilyPhysician : public Clinician
{
public:
	/**
     * @brief Constructor for creating a Family physician object and initializing with a name, id, and type
     * @param name The name of the clinician
     * @param id The ID of the clinician
    */
    FamilyPhysician(std::string name="", int id=-1);
    
    /**
     * @brief will set the family physician object with a list of its current requests
     * @param requestList a vector of strings containing all the requests relevant to their patient
    */
    void setRequests(std::vector<std::string> requestList);
    
    /**
     *@brief will return a list of all the requests for the current family physician
     *@return a vector of strings with all requests for the current family physician
    */
    std::vector<std::string> getRequests();

private:
	/**
     *@brief will return a list of all the requests specific to transfer
     *@return a list of all the requests specific to transfer
    */
    std::vector<std::string> transferRequests;

};

#endif // FAMILYPHYSICIAN_HPP
