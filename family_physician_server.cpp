/**
 * @file family_physician_server.cpp
 * @brief Family physician server allows for executing all actions needed by a family physician
 * 
 * This will inherit from clinician server, and so can view all patients that a family physician has,
 * view each patient's records, including diagnosis history, prescription, etc., and send requests to the requests system.
 * In addition, it also implements other methods unique to a family physician, including the ability to 
 * add a new patient's medical record, edit a patient's medical record, view all requests, and send and accept requests
 * 
 * @author Shruthi Sundararaman
 * @bug No known bugs
*/

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <ctime>

#include "db_service.hpp"
#include "family_physician_server.hpp"
#include "record_editor.hpp"
#include "patient.hpp"
#include "request_system.hpp"

using namespace std;


FamilyPhysicianServer::FamilyPhysicianServer(FamilyPhysician* currPhysician) {
    physician = currPhysician; // initializes the server with the family physician object that was passed in

    db = DBService::GetInstance().getDb(); // get an instance of the database
    myRequestSystem = new RequestSystem(db); // set up the requests system
};


FamilyPhysicianServer::~FamilyPhysicianServer() {
};

void FamilyPhysicianServer::setFamilyPhysician(FamilyPhysician* currPhysician) {
    physician = currPhysician;
}

vector<Patient> FamilyPhysicianServer::getPatients() {
    int familyPhysicianId = physician->getId();

    int rc;
    sqlite3_stmt* statement;

    vector<Patient> patientList; // will store all patients of the current physician

    // all the attributes that are grabbed for a patient
    string patientName;
    int patientId;
    string patientBirthdate;
    string patientSex;

    cout << "getPatients for clinicianId: " << familyPhysicianId << endl;

    string query = "SELECT patientID, name, dateOfBirth, sex FROM medicalRecord WHERE familyPhysicianID = \"" + to_string(familyPhysicianId) + "\";";

    // try grabbing each row from the database
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Values not retrieved for getPatients" << endl;
        cerr << sqlite3_errmsg(db) << endl;
        // exit(0);
    }

    while(sqlite3_step(statement) != SQLITE_DONE) { // for each row in the query result
        // grab the appropriate attributes
        patientId = stoi((const char*)sqlite3_column_text(statement, 0)); 
        patientName = (const char*)sqlite3_column_text(statement, 1);
        patientBirthdate = (const char*)sqlite3_column_text(statement, 2);
        patientSex = (const char*)sqlite3_column_text(statement, 3);

        // create a new patient object with the appropriate attributes;
        Patient newPatient(patientName, patientId, patientBirthdate, patientSex);

        // add the patient object to the patients list
        patientList.push_back(newPatient);

        cout << "getPatients retrieved: patientId " << patientId << ", patientName " << patientName << endl;
    }

    sqlite3_finalize(statement);
    return patientList;
}


void FamilyPhysicianServer::addMedicalRecord(Patient patient){
    // statement to insert a new patient's information into the medical record table
    string sql = "INSERT INTO medicalRecord VALUES (" + to_string(patient.getId()) + ", \"" + patient.getName() + "\", \"" + patient.getBirth() + "\", \"" + patient.getSex() + "\", " + to_string(physician->getId()) + ", \"abc\");";
    DBService::GetInstance().exec(sql);
}

void FamilyPhysicianServer::removeMedicalRecord(Patient patient){
    // statement to delete a patient from the medical record table
    string sql = "DELETE FROM medicalRecord WHERE patientID = \"" + to_string(patient.getId()) + "\"";
    DBService::GetInstance().exec(sql);
}

void FamilyPhysicianServer::editRecord(Patient patient, string editCommand, string value) {
    RecordEditor editor(db, patient.getId());

    string firstWord = editCommand.substr(0, editCommand.find(" "));
    if (firstWord == "add"){
        // to get current date and time
        time_t result = time(nullptr);
        string timeStamp = asctime(localtime(&result));
        timeStamp.erase(timeStamp.end() - 1);

        editor.addToMedicalRecord(editCommand, value, timeStamp, patient.getId());
    }
    else if (firstWord == "edit"){
        editor.editMedicalRecord(editCommand, value, patient.getId());
    }
    else if (firstWord == "remove"){
        editor.removeFromMedicalRecord(editCommand, value, patient.getId());
    }
}

void FamilyPhysicianServer::viewRequests(){
    // Check output

    vector<string> requests = myRequestSystem->getRequests(physician->getId());
    /*
    for (string item : requests)
    {
        cout << "Get Requests Returned: " << item << endl;
    }
*/
    physician->setRequests(requests);
}

void FamilyPhysicianServer::sendRequest(string command, Patient *patient, int currentPhysicianID) {
    myRequestSystem->createRequest(physician->getId(), currentPhysicianID, patient->getId(), command);
}

void FamilyPhysicianServer::acceptRequest(string command, Patient *patient, int currentPhysicianID){
    myRequestSystem->acceptRequest(physician->getId(), currentPhysicianID, patient->getId(), command);
}


/**
 * For testing family physician server: g++ family_physician_server.cpp family_physician.cpp clinician_server.cpp clinician.cpp patient.cpp user_.cpp -o familyPhysServerObj db_service.cpp medical_record.cpp record_editor.cpp request_system.cpp -lsqlite3
 */

/*
int main (int argc, char *argv[]) {
    FamilyPhysician *myPhysician = new FamilyPhysician("Sylvia", 2);
    FamilyPhysicianServer *myFamilyPhysicianServer = new FamilyPhysicianServer(myPhysician);

    Patient *myPatient = new Patient("Shruthi S.", 1, "2001/02/15", "F");
    myFamilyPhysicianServer->getPatients();
    myFamilyPhysicianServer->sendRequest("Transfer", myPatient, 1);
    myFamilyPhysicianServer->getPatients();
    myFamilyPhysicianServer->acceptRequest("Transfer", myPatient, 1);
    myFamilyPhysicianServer->viewRequests();



    // vector<Patient> myPatients = myFamilyPhysicianServer->getPatients();
    // for (int i = 0; i < myPatients.size(); i++) {
    //     cout << myPatients[i].getName() << endl;
    // }
}
*/

