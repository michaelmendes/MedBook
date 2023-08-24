#include <string>
#include <iostream>
#include <vector>


#include "request_system.hpp"


using namespace std;

// constructor
RequestSystem::RequestSystem(sqlite3 *database){
    db = database;
    cout << "Created request system object" << endl;
}

void RequestSystem::createRequest(int reciever_doctorID, int sender_doctorID, int patientID, string command){
    // if the command says to transfer the patient
  	if (command.find("Transfer") != string::npos){
        uploadRequest(reciever_doctorID, sender_doctorID, patientID, "Transfer");
    }
  	// if the command says to view the patient's record
    else if (command.find("View Record") != string::npos){
        uploadRequest(reciever_doctorID, sender_doctorID, patientID, "View Record");
    }
}

void RequestSystem::uploadRequest(int reciever_doctorID, int sender_doctorID, int patientID, string type){
    DBService& dbService = DBService::GetInstance();
    // insert the request into the table
  	dbService.exec("INSERT INTO request VALUES (\"" + to_string(sender_doctorID) + "\", \"" + to_string(reciever_doctorID) + "\", \"" + type + "\"," + to_string(patientID) + ")");
}

vector<string> RequestSystem::getRequests(int doctorID){
    sqlite3_stmt *q;
    vector<string> requestList;
  	// create sql statement
    string sql_statement = "SELECT request.type, request.patientID, medicalRecord.name, request.reciever_doctorID, clinician.name FROM request, medicalRecord, clinician WHERE request.patientID = medicalRecord.patientID AND request.reciever_doctorID = clinician.clinicianID AND request.sender_doctorID = " + to_string(doctorID);
    int code;
    code = sqlite3_prepare_v2(db, (sql_statement).c_str(), -1, &q, NULL);
    if (code != SQLITE_OK)
    {
        cerr << "Values not retrieved" << endl;
    }
    code = sqlite3_step(q);
    while (code != SQLITE_DONE) {
        string type = string(reinterpret_cast<const char *>(sqlite3_column_text(q, 0)));
        string patientID = string(reinterpret_cast<const char *>(sqlite3_column_text(q, 1)));
        string patientName = string(reinterpret_cast<const char *>(sqlite3_column_text(q, 2)));
        string reciever_doctorID = string(reinterpret_cast<const char *>(sqlite3_column_text(q, 3)));
        string reciever_doctorName = string(reinterpret_cast<const char *>(sqlite3_column_text(q, 4)));
        string requestX = type + "," + patientID + "," + patientName + "," + reciever_doctorID + "," + reciever_doctorName;
        cout << requestX << endl;
        requestList.push_back(requestX);
        code = sqlite3_step(q);
    }
    sqlite3_finalize(q);
    return requestList;
}

// send all information for a request to ensure correct one is accepted
void RequestSystem::acceptRequest(int reciever_doctorID, int sender_doctorID, int patientID, string type){
    DBService& dbService = DBService::GetInstance();
    cout << reciever_doctorID << sender_doctorID << patientID << type << endl;

    // change family physician ID in medicalRecord database
    if (type.find("Transfer") != string::npos){
        dbService.exec("UPDATE medicalRecord SET familyPhysicianID = \"" + to_string(sender_doctorID) + "\" WHERE patientID = \"" + to_string(patientID) + "\";");
    }
    else {
    // insert patient clinicina relationship into the treats table
        dbService.exec("INSERT INTO treats (patientID,clinicianID) VALUES (\"" + to_string(patientID) + "\", \""+ to_string(sender_doctorID) +"\");");
    }

    // delete the request from the db
    dbService.exec("DELETE FROM request WHERE reciever_doctorID = \"" + to_string(reciever_doctorID) + "\" AND patientID = \"" + to_string(patientID) + "\" AND sender_doctorID = \"" + to_string(sender_doctorID) + "\" AND type = \"" + type + "\";");
}
