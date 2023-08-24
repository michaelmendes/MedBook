/**
 * @file family_physician_server.hpp
 * @brief Function prototypes for family physician server allows for executing all actions needed by a family physician
<<<<<<< HEAD
 *
 * This defines all the function prototypes for a family physician server.
 * This will inherit from clinician server, and so can view all patients that a family physician has,
 * view each patient's records, including diagnosis history, prescription, etc., and send requests to the requests system.
 * In addition, it also implements other methods unique to a family physician, including the ability to
 * add a new patient's medical record, edit a patient's medical record, view all requests, and send and accept requests
 *
=======
 * 
 * This defines all the function prototypes for a family physician server.
 * This will inherit from clinician server, and so can view all patients that a family physician has,
 * view each patient's records, including diagnosis history, prescription, etc., and send requests to the requests system.
 * In addition, it also implements other methods unique to a family physician, including the ability to 
 * add a new patient's medical record, edit a patient's medical record, view all requests, and send and accept requests
 * 
>>>>>>> aa738b47d7bfe6d8e18214fb7953e0c56ed82988
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/

#ifndef FAMILYPHYSICIANSERVER_HPP
#define FAMILYPHYSICIANSERVER_HPP

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "clinician_server.hpp"
#include "family_physician.hpp"
#include "patient.hpp"

class FamilyPhysicianServer : public ClinicianServer {
    private:
        FamilyPhysician* physician; 

    public:
        /**
         * @brief Generates family physician server and initializes it with a family physician object
         * This constructor allows the creation of a family physician server, and initializes it with the current family physician object
         * 
         * @param currPhysician This is the family physician object that the server will be initialized with. All operations will be performed in relation to this family physician. 
        */
        FamilyPhysicianServer(FamilyPhysician* currPhysician=nullptr);

        /**
         * @brief Deconstructor for the class
        */
        ~FamilyPhysicianServer();

        /**
         * @brief Allows to set a new family physician object to the family physician server
         * This method allows the server to have change its corresponding family physician.
         * So a different family physician would be accessing it, and viewing the information and sending requests
         * 
         * @param currPhysician This is the new family physician object that the server will be set to use
        */
        void setFamilyPhysician(FamilyPhysician* currPhysician=nullptr);

        /**
         * @brief Returns all patients that the current family physician has
         * This method returns a vector of patient objects corresponding to
         * all patients that the family physician has
         * 
         * @return a vector of patient objects
        */
        std::vector<Patient> getPatients();

        /**
         * @brief Enables a family physician to edit specific components of a patient's medical record
         * This method uses the requests_system object to edit a patient's record
         * It allows for the editing of a patient's diagnosis, prescription, surgery, vaccination, allergy
         * 
         * @param patient the patient object for which we will be editing their record for in the database
         * @param editCommand the command to be executed; add or remove, and for which table
         * Commands have a beginning and an ending
         * Possible command beginnings: "add a", "remove a"
         * Possible command endings: "Diagnosis", "Surgery", "Prescription", "Vaccination", "Allergy", "Diary Entry"
         * @param value the value to be added, or the value to be removed; represented as "string,date"
         * 
        */
        void editRecord(Patient patient, std::string editCommand, std::string value);

        /**
         * @brief allows a new patient to be added to the medical record database
         * @param patient the patient object to be added to the medical record database
        */
        void addMedicalRecord(Patient patient);
  		/**
         * @brief allows the removal of a patient from the medical record database
         * @param patient the patient object to be added to the medical record database
        */
  		void removeMedicalRecord(Patient patient);
        /**
         * @brief allows the viewing of all requests for the current family physician
        */
        void viewRequests();
        /**
         * @brief Allows a new request to be sent to the request system
         * 
         * This method enables the family physician to send a new request to Transfer a patient to their own list of patients
         * 
         * @param command The type of request; can be "Transfer" for a family physician
         * @param patient A pointer to a patient object, the patient that we are requesting to view or transfer
         * @param currentPhysicianID The ID of the family physician currently responsible for that patient; who we are sending the request to
        */
        void sendRequest(std::string command, Patient *patient, int currentPhysicianID);
        /**
         * @brief Allows a family physician to accept an incoming request
         * 
         * This method allows a family physician to approve an incoming transfer or view request for their patient
         * 
         * @param command The type of request; can be "Transfer" or "View Record"
         * @param patient A pointer to a patient object, the patient that we are requesting to view or transfer
         * @param currentPhysicianID The ID of the clinician that was requesting the transfer
        */
        void acceptRequest(std::string command, Patient *patient, int currentPhysicianID);
};

#endif
