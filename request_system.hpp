/**
 * @file request_system.cpp
 * @brief Functions to work with the request system in the database
 *
 * This file contains multiple functions that are used in conjunction with the family_physician_server and the clinician_server.
 * This file allows the functionality of adding to the request system, accepting a request, and uploading a request
 * 
 * @author Rhea Mangat
 * @bug No known bugs
*/

#ifndef REQUESTS_HPP
#define REQUESTS_HPP

#include <string>
#include <sqlite3.h>
#include <iostream>
#include <string.h>
#include <vector>

#include "db_service.hpp"

class RequestSystem{
    private:
        sqlite3 *db;
        int rc;

    public:
  	/**
         * @brief constructor
         * @param database our database object
         */
        RequestSystem(sqlite3 *database);

  	/**
         * @brief Adds a request to the request table database
         * @param receiverDoctorId the ID of the doctor that recieves the request
         * @param senderDoctorId the ID of the doctor that sends the request
         * @param patientID the ID of the patient who is being requested
         * @param command the prompt stating what to do with the request
         * @return void
         */
        void createRequest(int receiverDoctorID, int senderDoctorID, int patientID, std::string command);
        
  	/**
         * @brief Uploads the request table database. Used with the createRequest function
         * @param receiverDoctorId the ID of the doctor that recieves the request
         * @param senderDoctorId the ID of the doctor that sends the request
         * @param patientID the ID of the patient who is being requested
         * @param type the type of request
         * @return void
         */
        void uploadRequest(int receiverDoctorID, int senderDoctorID, int patientID, std::string type);
  	
        /**
         * @brief returns the current rows in the request table relating to the given doctor
         * @param doctorID the ID of the doctor we want to find current requests for
         * @return vector<string> that represents each row in the table
         */
        std::vector<std::string> getRequests(int doctorID);
  	
        /**
         * @brief accepts the request in the database table and updates the value in the appropriate table (depending on type) and removes from request table
         * @param receiverDoctorId the ID of the doctor that recieves the request
         * @param senderDoctorId the ID of the doctor that sends the request
         * @param patientID the ID of the patient who is being requested
         * @param type the type of request
         * @return void
         */
        void acceptRequest(int receiverDoctorID, int senderDoctorID, int patientID, std::string type);

};

#endif // REQUESTS_HPP
