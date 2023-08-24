/**
 * @file patient_server.hpp
 * @brief Methods in patient server allows for executing all actions needed by a patient
 * 
 * This defines all the methods for a patient server. 
 * This, as linked with the user interface, will enable the patients to view their details, their medical records  
 * and add entries to their diary. The server will get the patient ID to be sent to the table from the class Patient,  
 * which inherits the ID from the user class.
 * 
 * @author Amreen Anbar
 * @bug No known bugs
*/ 

#ifndef PATIENT_SERVER_H
#define PATIENT_SERVER_H  
#include <vector> 
#include <string>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include "patient.hpp"
#include "record_editor.hpp"
#include "db_service.hpp" 
#include "user.hpp"

using namespace std; 
class patientServer
{   private:  
        
        // int patientID;
        // sqlite3* dBPtr; 
        Patient* patient;

   public:  
        //public variables
        sqlite3 *db;
        int patientID;  
        /**
         * @brief Constructor for the class
        */
        patientServer(Patient* myself);
        
        /**
         * @brief Deconstructor for the class
        */
        ~patientServer();    
         /**
         * @brief Allows a patient to get own medical record from the database
         * 
         * @param tableName The category of medical record the patient wishes to view 
        */
        vector<string> viewMedicalRecordPatient(string tableName);  
         /**
         * @brief Allows a patient to add antries to diary that can be viewed by the patient and the physician 
         * 
         * @param newValue The diary entry entered
        */
        void writeDiaryPatient(string newValue); 
        /**
         * @brief A pointer to patient object, views patient details
        */
        Patient* viewPatientDetails(); 

}; 

#endif // PATIENT_SERVER_H
