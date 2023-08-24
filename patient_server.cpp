/**
 * @file patient_server.cpp
 * @brief Patient server allows for executing all actions needed by a patient
 *  
 * This, as linked with the user interface, will enable the patients to view their details, their medical records  
 * and add entries to their diary. The server will get the patient ID to be sent to the table from the class Patient,  
 * which inherits the ID from the user class 
 * 
 * @author Amreen Anbar
 * @bug No known bugs
*/
#include<iostream>   
#include <vector> 
#include <string> 
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include "patient_server.hpp" 
#include "patient.hpp"  
#include "user.hpp"
//#include "record_editor.hpp"
#include "db_service.hpp"
using namespace std;
 
patientServer::patientServer(Patient* myself)
{ 
    patient = myself;
    patientID = patient->getId(); //get patient ID from Patient and thus from the user login information
    db = DBService::GetInstance().getDb(); // get an instance of the database
};

patientServer::~patientServer() 
{  
}

Patient* patientServer::viewPatientDetails() {
    //dbService.exec("SELECT patientID, name, dateOfBirth, sex FROM medicalRecord WHERE patientID = " + to_string(patientID));

    int rc;
    sqlite3_stmt* statement;

    //Patient currPatient;

    cout << "viewPatientDetails for patient: " << patientID << endl;

    string query = "SELECT patientID, name, dateOfBirth, sex FROM medicalRecord WHERE patientID = \"" + to_string(patientID) + "\";";

    // try grabbing each row from the database
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Values not retrieved for viewPatientDetails" << endl;
        cerr << sqlite3_errmsg(db) << endl;
        // exit(0);
    }

    Patient *currPatient;

    while(sqlite3_step(statement) != SQLITE_DONE) {
        int patientId = stoi((const char*)sqlite3_column_text(statement, 0)); 
        string patientName = (const char*)sqlite3_column_text(statement, 1);
        string patientBirthdate = (const char*)sqlite3_column_text(statement, 2);
        string patientSex = (const char*)sqlite3_column_text(statement, 3);

        currPatient = new Patient(patientName, patientId, patientBirthdate, patientSex);

        cout << "viewPatientDetails retrieved: patientId " << patientId << ", patientName " << patientName << endl;
    }

    sqlite3_finalize(statement);
    return currPatient;

}

vector<string> patientServer::viewMedicalRecordPatient(string tableName) 
 {
    int rc;
    sqlite3_stmt* statement;
    vector<string> fetchedMedicalRecord;

    // select record of a specific table for a particular patient with sql statement
    string sql_view = "SELECT * FROM " + tableName + " WHERE patientID = " + to_string(patientID) + ";";
    // execute the statement
    //get rows from the database
    rc = sqlite3_prepare_v2(db, sql_view.c_str(), -1, &statement, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Values not retrieved for select from " + tableName << endl;
        cerr << sqlite3_errmsg(db) << endl;
        exit(0);
    }
    //combine each value and their corresponding dates to return
    while(sqlite3_step(statement) != SQLITE_DONE) {
        string valueOfEntry = (const char*)sqlite3_column_text(statement, 1); 
        string date = (const char*)sqlite3_column_text(statement, 2);
        string combinedValue = date + "," + valueOfEntry;

        cout << combinedValue << endl;
        fetchedMedicalRecord.push_back(combinedValue);
    }
    for (string record : fetchedMedicalRecord)
    {
        cout << record << "\n" << endl;
    }

    return fetchedMedicalRecord;
} 

void patientServer::writeDiaryPatient(string newValue)
{
    DBService& dbService = DBService::GetInstance();
    string tn = "diary"; 
    //write entries to the diary with date 
    dbService.exec("INSERT INTO " + tn + " VALUES (\"" + to_string(patientID) + "\", \"" + newValue + "\");");
}

/**
 * For testing the code, run:
 * g++ patientServer.cpp patient.cpp db_service.cpp user_.cpp medical_record.cpp -o patientServerObj -lsqlite3
*/
// int main (int argc, char *argv[]) {
//     patientServer *myPatientServer = new patientServer(1);
//     Patient *myPatient = myPatientServer->viewPatientDetails();
//     cout << myPatient->getName() << endl;

//     vector<string> diagnoses = myPatientServer->viewMedicalRecordPatient("diagnosis");
//     for (int i = 0; i < diagnoses.size(); i++) {
//         cout << diagnoses[i] << endl;
//     }

// }
