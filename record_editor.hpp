/**
 * @file record_editor.cpp
 * @brief Functions to edit the medicalrecord table in the database
 *
 * This file contains multiple functions that are used in conjunction with the family_physician_server and the clinician_server.
 * The manage record function takes in a string and values, and runs the appropriate function based on the given command
 * 
 * @author Rhea Mangat
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/
#ifndef RECORDEDITOR_HPP
#define RECORDEDITOR_HPP

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

class RecordEditor{
    private:
        sqlite3 *db;
        int patientId;
        int rc;
        

        void editor(std::string column,std::string value, int patient);
        /**
         * @brief used with the addToMedicalRecord funtion to add a row to a specific table
         * @param tableName the table we are adding a row to
         * @param value the value we are adding
         * @param date the date for the table
         * @param patient the patientid of the patient
         * @return void
         */
        void addRow(std::string tableName,std::string value, std::string date, int patientID);
        /**
         * @brief used with the removeFromMedicalRecord funtion to remove a row from a specific table
         * @param tableName the table we are removing a row from
         * @param value the value we are removing
         * @param date the date for the row
         * @param columnName the name of the column in the table that the value is associated with
         * @param patient the patientid of the patient
         * @return void
         */
        void removeRow(std::string tableName,std::string value, std::string date, std::string column, int patient);

    public:
  	/**
         * @brief constructor
         * @param database our database object
         * @param patient the patientid of the patient
         */
        RecordEditor(sqlite3 *database, int patient);
  	
        /**
         * @brief The main method that accepts values to send to the other functions in this file
         * @param command the string that contains what attribute of the table we are changing
         * @param value the value to change the attribute to
         * @param date the date for the table
         * @param patient the patientid of the patient
         * @return void
         */
        // void manageRecord(std::string command, std::string value, std::string date, int patient); 
        
        /**
         * @brief used to edit values in the row of the patientID in the medicalrecord table
         * @param command the string that contains what attribute of the table we are changing
         * @param newValue the value to change the attribute to
         * @param patient the patientid of the patient
         * @return void
         */
        void editMedicalRecord(std::string command, std::string newValue, int patient);
        /**
         * @brief Adds a row to a specific table based on the command parameter
         * @param command the string that contains the table we are changing and how
         * @param newValue the value to change the attribute to
         * @param date the date for the table
         * @param patient the patientid of the patient
         * @return void
         */
        void addToMedicalRecord(std::string command, std::string newValue, std::string date, int patient);
        /**
         * @brief removes a row from a specific table based on the command parameter
         * @param command the string that contains the table we are changing and how
         * @param value the value to change the attribute to
         * @param patient the patientid of the patient
         * @return void
         */
        void removeFromMedicalRecord(std::string command, std::string value, int patient);
  		/**
         * @brief used with the editMedicalRecord funtion to edit a row value
         * @param column the column we are changing the value for
         * @param value the value to change the attribute to
         * @param patient the patientid of the patient
         * @return void
         */
};
#endif // RECORDEDITOR_HPP
