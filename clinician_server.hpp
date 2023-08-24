/**
 * @file clinician_server.hpp
 * @brief Function prototypes for clinician server allows for executing all actions needed by a clinician
 * 
 * This defines all the function prototypes for a clinician server.
 * Enables a clinician to view all patients that they have access to, view each patient's
 * detailed records, including diagnosis history, prescription, etc., and send requests to view another patient's record
 * 
 * @author Jessica Liu
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/


#ifndef CLINICIANSERVER_HPP
#define CLINICIANSERVER_HPP

#include <sqlite3.h>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "clinician.hpp"
#include "patient.hpp"
#include "request_system.hpp"

class ClinicianServer
{
private:
    Clinician* clinician;


public:
    sqlite3 *db;
    RequestSystem* myRequestSystem;

    /**
     * @brief Generates clinician server and initializes it with a clinician object
     * This constructor allows the creation of a clinician server, and initializes it with the current clinician object
     * 
     * @param currPhysician This is the clinician object that the server will be initialized with. All operations will be performed in relation to this clinician. 
    */
    ClinicianServer(Clinician* c=nullptr);
    
    /**
     * @brief Deconstructor for the class
    */
    ~ClinicianServer();

    /**
     * REMOVED??
    */
    //void viewPatients();

    /**
     * @brief Allows for the viewing of a multi-valued attribute (e.g. diagnosis, prescription) of a patient's medical record
     * 
     * This method allows a clinician to view the specific details of a patient's medical record
     * This includes things like diagnosis, prescription, etc.
     * 
     * @param tableName the table that you wish to see; can be diagnosis, prescription, surgery, allergy, vaccination, or diary entry
     * @param patient the id of patient that you want to view the details of
     * @return a vector of strings, each one representing one entry of that table. Each string is a comma separated attribute, containing the value and the date of the entry as follows: "value,date"
    */
    std::vector<std::string> viewTable(std::string tableName, int patient);

    /**
     * @brief method to set the clinician object of the current server
     * @param c the clinician object to be used by the server
    */
    void setClinician(Clinician* c=nullptr);

    /**
     * @brief Returns all patients that the current clinician is allowed to view
     * @return a vector of patient objects containing the patients that the clinician is approved to see
    */
    std::vector<Patient> getPatients();

    /**
     * @brief Allows a clinician to send a request to view a new patient
     * @param command The type of request; can only be "View Record" for a clinician, but can be "Transfer" for a family physician
     * @param patient A pointer to a patient object with the patient that is being requested
     * @param currentPhysicianID The ID of the current family physician of the patient; the one the request is being sent to
    */
    void sendRequest(std::string command, Patient *patient, int currentPhysicianID);
};

#endif // CLINICIANSERVER_HPP
