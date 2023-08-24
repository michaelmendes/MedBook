#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "record_editor.hpp"

using namespace std;

RecordEditor::RecordEditor(sqlite3 *database, int patient){
    db = database;
    patientId = patient;
}


// void RecordEditor::manageRecord(string command, string value, string date, int patient){
//     string firstWord = command.substr(0, command.find(" "));
//     if (firstWord == "add"){
//         addToMedicalRecord(command,value,date,patient);
//     }
//     else if (firstWord == "edit"){
//         editMedicalRecord(command, value, patient);
//     }
//     else if (firstWord == "remove"){
//         removeFromMedicalRecord(command,value,patient);
//     }
// }

void RecordEditor::editMedicalRecord(string command,string newValue, int patient) {
    // if wanting to edit demographic data
  	if (command == "edit demographic data") {
            editor("Demographic",newValue,patient);
    }
  	// if wanting to edit family physician
    else if (command == "edit family physician" ){
        editor("familyPhysicianID",newValue,patient);
    }
  	// if wanting to edit identification number
    else if (command == "edit identification number"){
        editor("patientID",newValue, patient);
    }
  	// if wanting to edit sex
  	else if (command == "edit sex"){
   		editor("sex",newValue, patient);
    }
  	// if wanting to edit date of birth
    else if (command == "edit date of birth"){
    	editor("dateOfBirth", newValue,patient);
    }
  	// if wanting to edit password
    else if (command == "edit password"){
    	editor("password", newValue,patient);
    }
  	// if wanting to edit name
    else if (command == "edit name"){
    	editor("name", newValue,patient);
    }
}


void RecordEditor::addToMedicalRecord(string command, string newValue, string date, int patient) {
  	// if wanting to add a diagnosis
    if (command == "add a Diagnosis"){
        addRow("diagnosis",newValue,date, patient);
    }
  	// if wanting to add a Surgery
    else if (command == "add a Surgery"){
        addRow("surgery",newValue, date, patient);
    }
  	// if wanting to add a Prescription
    else if (command == "add a Prescription"){
        addRow("prescription",newValue, date, patient);
    }
  	// if wanting to add a Vaccination
    else if (command == "add a Vaccination"){
        addRow("vaccination",newValue, date, patient);
    }
  	// if wanting to add a Allergy
    else if (command == "add a Allergy"){
        addRow("allergy",newValue, date, patient);
        cout << "New Allergy added to patient: " + to_string(patient);
    }
  	// if wanting to add a Diary Entry
    else if (command == "add a Diary Entry"){
        addRow("diary",newValue, date, patient);
    }
}

/*
will be used alongside removeRow function
*/
void RecordEditor::removeFromMedicalRecord(string command, string value, int patient) {
    string date = value;
    size_t position;
    position = date.find(",");
    value = date.substr(0, position);
    date.erase(0, position+1);
  	// to remove a Diagnosis
    if (command == "remove a Diagnosis"){
        removeRow("diagnosis",value,date,"diagnosis", patient);
    }
  	// to remove a Surgery
    else if (command == "remove a Surgery"){
        removeRow("surgery",value,date,"surgery", patient);
    }
  	// to remove a Prescription
    else if (command == "remove a Prescription"){
        removeRow("prescription",value,date,"prescription", patient);
    }
  	// to remove a Vaccination
    else if (command == "remove a Vaccination"){
        removeRow("vaccination",value,date,"vaccination", patient);
    }
  	// to remove a Allergy
    else if (command == "remove a Allergy"){
        removeRow("allergy",value,date,"allergy", patient);
    }
  	// to remove a Diary Entry
    else if (command == "remove a Diary Entry"){
        removeRow("diary",value,date,"diaryEntry", patient);
    }
}



void RecordEditor::editor(string column,string value, int patient){
    char *zErrMsg = 0;
    // create sql statement
    string sql_update = "UPDATE medicalRecords SET " + column + " = " + value + " WHERE patientID = " + to_string(patient);
    // update the db
    rc = sqlite3_exec(db, sql_update.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){
    	
    }
}



// Add a row to a table that is NOT medicalRecords; only for multivalued attributes

void RecordEditor::addRow(string tableName,string value, string date, int patientID){
    char *zErrMsg = 0;
    string sql_statement = "INSERT INTO " + tableName + " VALUES (\"" + to_string(patientID) + "\", \"" + value + "\", \"" + date +"\");";
    rc = sqlite3_exec(db, sql_statement.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        cout << "Error when inserting into " + tableName << endl;
    }
}


//Remove a row from a table that is NOT medicalRecords

void RecordEditor::removeRow(string tableName,string value, string date, string columnName, int patient){
    char *zErrMsg = 0;
    string sql_statement = "DELETE FROM " + tableName + " WHERE patientID = \"" + to_string(patient) + "\" AND date = \"" + date + "\" AND "+ columnName + " = \"" + value + "\";";
    rc = sqlite3_exec(db, sql_statement.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        //dbError("Error when removing row from " + tableName,zErrMsg);
        cout << "Error when deleting from " + tableName << endl;
        cout << sqlite3_errmsg(db) << endl;
    }
}


/** 
 * Testing purposes; run: g++ record_editor.cpp -o recordEditObj -lsqlite3
*/
/*
int main (int argc, char *argv[]) {

    sqlite3 *mydb;
    string database = "../medbook.db";
    int rc = sqlite3_open(database.c_str(), &mydb);
    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(mydb) << endl;
        exit(0);
    }

    RecordEditor *myRecordEditor = new RecordEditor(mydb, 1);

    time_t result = time(nullptr);
    string timeStamp = asctime(localtime(&result));
    timeStamp.erase(timeStamp.end() - 1);

    //timeStamp = "tempDate2";

    // test add value
    string uniqueNum = " 4"; // just to add more entries, have a unique id added to each entry
    myRecordEditor->manageRecord("add a diagnosis", "my test diagnosis" + uniqueNum, timeStamp, 1);
    myRecordEditor->manageRecord("add a surgery", "my test surgery" + uniqueNum, timeStamp, 1);
    myRecordEditor->manageRecord("add a prescription", "my test prescription" + uniqueNum, timeStamp, 1);
    myRecordEditor->manageRecord("add a vaccination", "my test vaccination" + uniqueNum, timeStamp, 1);
    myRecordEditor->manageRecord("add an allergy", "my test allergy" + uniqueNum, timeStamp, 1);
    myRecordEditor->manageRecord("add a diary entry", "my test diary entry" + uniqueNum, timeStamp, 1);


    // test remove value

    myRecordEditor->manageRecord("remove a diagnosis", "my test diagnosis", timeStamp, 1);
    myRecordEditor->manageRecord("remove a surgery", "my test surgery", timeStamp, 1);
    myRecordEditor->manageRecord("remove a prescription", "my test prescription", timeStamp, 1);
    myRecordEditor->manageRecord("remove a vaccination", "my test vaccination", timeStamp, 1);
    myRecordEditor->manageRecord("remove an allergy", "my test allergy", timeStamp, 1);
    myRecordEditor->manageRecord("remove a diary entry", "my test diary entry", timeStamp, 1);


    // test edit value

    sqlite3_close(mydb);

}
*/

