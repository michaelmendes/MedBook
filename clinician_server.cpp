#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "clinician_server.hpp"
#include "db_service.hpp"
#include "record_editor.hpp"

using namespace std;

ClinicianServer::ClinicianServer(Clinician* c)
{
    clinician = c; // initializes the clinician object of the server with the one provided in the parameter

    db = DBService::GetInstance().getDb(); // gets the database that we are using 
    myRequestSystem = new RequestSystem(db); // creates a requests system object for handling requests

}

ClinicianServer::~ClinicianServer(){
}

void ClinicianServer::setClinician(Clinician* c) {
    clinician = c;
}

vector<Patient> ClinicianServer::getPatients() {
    int clinicianId = clinician->getId();

    int rc;
    sqlite3_stmt* statement;

    vector<Patient> patientList;
    vector<string> patientIdList;
    string s;
    int patientId;
    string patientName;
    string patientBirthdate;
    string patientSex;

    cout << "getPatients for clinicianId: " << clinicianId << endl;

    string query = "SELECT patientID FROM treats WHERE clinicianID = \"" + to_string(clinicianId) + "\";";

    // try grabbing each row from the database
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Values not retrieved for getPatients" << endl;
        cerr << sqlite3_errmsg(db) << endl;
        // exit(0);
    }

    while(sqlite3_step(statement) != SQLITE_DONE) { // for each row of the query result
        s = (const char*)sqlite3_column_text(statement, 0);
        patientIdList.push_back(s);

        cout << "getPatients from treats retrieved: patientId " << s << endl;
    }

    sqlite3_finalize(statement);

    if (patientIdList.empty()){
        return patientList;
    }

    s = "";
    for (string patientId : patientIdList){
        if (s != ""){
            s += "," + patientId;
        } else {
            s = patientId;
        }
    }

    query = "SELECT patientID, name, dateOfBirth, sex FROM medicalRecord WHERE patientID in (" + s + ")";

    // try grabbing each row from the database
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Values not retrieved for getPatients" << endl;
        cerr << sqlite3_errmsg(db) << endl;
        // exit(0);
    }
    cout << "after prepare" << endl;

    while(sqlite3_step(statement) != SQLITE_DONE) { // for each row of the query result
        cout << "within while loop" << endl;
        patientId = stoi((const char*)sqlite3_column_text(statement, 0));
        patientName = (const char*)sqlite3_column_text(statement, 1);
        patientBirthdate = (const char*)sqlite3_column_text(statement, 2);
        patientSex = (const char*)sqlite3_column_text(statement, 3);

        cout << "After getting all columns" << endl;

        Patient newPatient(patientName, patientId, patientBirthdate, patientSex);
        patientList.push_back(newPatient);

        cout << "getPatients retrieved: patientId: " << patientId << ", patientName: " << patientName << ", patientBirthday: " << patientBirthdate << ", patientSex: " << patientSex << endl;
    }

    sqlite3_finalize(statement);
    return patientList;
}


vector<string> ClinicianServer::viewTable(string tableName, int patient) {
    cout << "Clinician Requested to view table" << endl;
    int rc;
    sqlite3_stmt* statement;
    vector<string> tableRows; // vector to contain strings of format "value,date" for return

    // create sql statement
    string sql_view = "SELECT * FROM " + tableName + " WHERE patientID = \"" + to_string(patient) + "\";";
    
    // execute the statement
    rc = sqlite3_prepare_v2(db, sql_view.c_str(), -1, &statement, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Values not retrieved for select from " + tableName << endl;
        cerr << sqlite3_errmsg(db) << endl;
        exit(0);
    }

    while(sqlite3_step(statement) != SQLITE_DONE) { // for each row of the query result
        string valueOfEntry = (const char*)sqlite3_column_text(statement, 1); 
        string date = (const char*)sqlite3_column_text(statement, 2);
        string combinedValue = valueOfEntry + "," + date; // in order to return a string of format "value,date"

        cout << combinedValue << endl;
        tableRows.push_back(combinedValue); // add the entry to the vector to be returned
    }
    return tableRows;
}

void ClinicianServer::sendRequest(string command, Patient *patient, int currentPhysicianID) {
    myRequestSystem->createRequest(clinician->getId(), currentPhysicianID, patient->getId(), command);
}

/**
 * For testing clinician server: g++ clinician_server.cpp patient.cpp clinician.cpp user_.cpp db_service.cpp medical_record.cpp -o clinicianServerObj -lsqlite3
*/
/*
int main (int argc, char *argv[]) {

    Clinician *myClinician = new Clinician("David", 1, "Family Physician");
    ClinicianServer *myClinicianServer = new ClinicianServer(myClinician);
    myClinicianServer->getPatients();
}
*/


