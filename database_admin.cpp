#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "database_admin.hpp"
#include "db_service.hpp"

using namespace std;

DatabaseAdmin::DatabaseAdmin() {
    cout << "Database Admin called..." << endl;

    deleteDatabaseTables(); // Run to clear all tables
    createDatabaseTables(); // create all tables for medical record
    setDatabaseRandom();
};

void DatabaseAdmin::createDatabaseTables(){

    DBService& dbService = DBService::GetInstance();

    // make sure clinician table exists
    dbService.exec("CREATE TABLE IF NOT EXISTS clinician (clinicianID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, clinicianType VARCHAR(50), "
          "name VARCHAR(50), password VARCHAR(50));");

    // make sure medicalRecords table exists
    dbService.exec("CREATE TABLE IF NOT EXISTS medicalRecord (patientID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name VARCHAR(50), "
          "dateOfBirth varchar(10), sex varchar(10), familyPhysicianID INTEGER NOT NULL, "
          "password VARCHAR(50), FOREIGN KEY(familyPhysicianID) REFERENCES clinician(clinicianID));");

    // create diagnosis table
    dbService.exec("CREATE TABLE IF NOT EXISTS diagnosis (patientID INTEGER NOT NULL, diagnosis VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));");

    // create surgery table
    dbService.exec("CREATE TABLE IF NOT EXISTS surgery (patientID INTEGER NOT NULL, surgery VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));");

    // create prescription table
    dbService.exec("CREATE TABLE IF NOT EXISTS prescription (patientID INTEGER NOT NULL, prescription VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));");

    // create vaccination table
    dbService.exec("CREATE TABLE IF NOT EXISTS vaccination (patientID INTEGER NOT NULL, vaccination VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));");

    // create allergy table
    dbService.exec("CREATE TABLE IF NOT EXISTS allergy (patientID INTEGER NOT NULL, allergy VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));");

    // create diary table
    dbService.exec("CREATE TABLE IF NOT EXISTS diaryEntry (patientID INTEGER NOT NULL, diaryEntry VARCHAR(1000), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));");

    // create treats table for patient clinician relationship
   dbService.exec("CREATE TABLE IF NOT EXISTS treats (patientID INTEGER NOT NULL, clinicianID INTEGER NOT NULL, PRIMARY KEY (patientID, clinicianID), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID), FOREIGN KEY(clinicianID) REFERENCES clinician(clinicianID));");

   // create request table
    dbService.exec("CREATE TABLE IF NOT EXISTS request (sender_doctorID INTEGER, reciever_doctorID INTEGER,type VARCHAR(50), patientID INTEGER, PRIMARY KEY (patientID, sender_doctorID), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID), FOREIGN KEY(sender_doctorID) REFERENCES clinician(clinicianID), FOREIGN KEY(reciever_doctorID) REFERENCES clinician(clinicianID));");
};


DatabaseAdmin::~DatabaseAdmin() {
};

/*
Function initializes the medBook database with 4 clinicians and 4 medical records
*/
void DatabaseAdmin::setDatabaseRandom() {

    DBService& dbService = DBService::GetInstance();

    //INSERT RANDOM INTO CLINICIANS TABLE
    dbService.exec("INSERT INTO clinician VALUES (1, \"Family Physician\", \"David Baugh\", \"abc\")");
    dbService.exec("INSERT INTO clinician VALUES (2, \"Family Physician\", \"Sylvia Tennyson\", \"abc\")");
    dbService.exec("INSERT INTO clinician VALUES (3, \"Pharmacist\", \"Rita Luke\", \"abc\")");
    dbService.exec("INSERT INTO clinician VALUES (4, \"Surgeon\", \"Kristan Krueger\", \"abc\")");
    dbService.exec("INSERT INTO clinician VALUES (5, \"Pharmacist\", \"Bob Li\", \"abc\")");

    dbService.exec("INSERT INTO medicalRecord VALUES (1, \"Shruthi S.\", \"2001/02/15\", \"F\", 1, \"abc\");");
    dbService.exec("INSERT INTO medicalRecord VALUES (2, \"Amreen A.\", \"2005/02/18\", \"F\", 1, \"abc\");");
    dbService.exec("INSERT INTO medicalRecord VALUES (3, \"Michael M.\", \"2003/03/15\", \"F\", 2, \"abc\");");
    dbService.exec("INSERT INTO medicalRecord VALUES (4, \"Rhea M.\", \"2005/08/22\", \"F\", 2, \"abc\");");
    dbService.exec("INSERT INTO medicalRecord VALUES (5, \"Jessica L.\", \"2002/02/15\", \"F\", 2, \"abc\");");
    dbService.exec("INSERT INTO medicalRecord VALUES (6, \"Adam S.\", \"2010/02/02\", \"F\", 2, \"abc\");");

    dbService.exec("INSERT INTO request VALUES (2, 1, \"Transfer\", 4);");

// "CREATE TABLE IF NOT EXISTS diagnosis (patientID VARCHAR(50) NOT NULL, diagnosis VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));"
// "CREATE TABLE IF NOT EXISTS surgery (patientID VARCHAR(50) NOT NULL, surgery VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));"
// "CREATE TABLE IF NOT EXISTS prescription (patientID VARCHAR(50) NOT NULL, prescription VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));"
// "CREATE TABLE IF NOT EXISTS vaccination (patientID VARCHAR(50) NOT NULL, vaccination VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));"
// "CREATE TABLE IF NOT EXISTS allergy (patientID VARCHAR(50) NOT NULL, allergy VARCHAR(50), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));"
// "CREATE TABLE IF NOT EXISTS diaryEntry (patientID VARCHAR(50) NOT NULL, diaryEntry VARCHAR(1000), date VARCHAR(50), PRIMARY KEY (patientID, date), FOREIGN KEY(patientID) REFERENCES medicalRecord(patientID));"

    dbService.exec("INSERT INTO diagnosis VALUES (1,\"diagnosis 1\", \"11/22/3333\");");
    dbService.exec("INSERT INTO diagnosis VALUES (1,\"diagnosis 2\", \"22/33/4444\");");
    dbService.exec("INSERT INTO diagnosis VALUES (2,\"diagnosis 3\", \"33/44/5555\");");
    dbService.exec("INSERT INTO diagnosis VALUES (3,\"diagnosis 4\", \"66/77/8888\");");
    dbService.exec("INSERT INTO diagnosis VALUES (4,\"diagnosis 5\", \"99/11/2222\");");

    dbService.exec("INSERT INTO surgery VALUES (1,\"surgery 1\", \"11/22/3333\");");
    dbService.exec("INSERT INTO surgery VALUES (1,\"surgery 2\", \"22/33/4444\");");
    dbService.exec("INSERT INTO surgery VALUES (5,\"surgery 3\", \"33/44/5555\");");
    dbService.exec("INSERT INTO surgery VALUES (6,\"surgery 4\", \"66/77/8888\");");
    dbService.exec("INSERT INTO surgery VALUES (2,\"surgery 5\", \"99/11/2222\");");

    dbService.exec("INSERT INTO prescription VALUES (1,\"prescription 1\", \"11/22/3333\");");
    dbService.exec("INSERT INTO prescription VALUES (1,\"prescription 2\", \"22/33/4444\");");
    dbService.exec("INSERT INTO prescription VALUES (3,\"prescription 3\", \"33/44/5555\");");
    dbService.exec("INSERT INTO prescription VALUES (4,\"prescription 4\", \"66/77/8888\");");
    dbService.exec("INSERT INTO prescription VALUES (5,\"prescription 5\", \"99/11/2222\");");

    dbService.exec("INSERT INTO vaccination VALUES (1,\"vaccination 1\", \"11/22/3333\");");
    dbService.exec("INSERT INTO vaccination VALUES (1,\"vaccination 2\", \"22/33/4444\");");
    dbService.exec("INSERT INTO vaccination VALUES (6,\"vaccination 3\", \"33/44/5555\");");
    dbService.exec("INSERT INTO vaccination VALUES (2,\"vaccination 4\", \"66/77/8888\");");
    dbService.exec("INSERT INTO vaccination VALUES (3,\"vaccination 5\", \"99/11/2222\");");

    dbService.exec("INSERT INTO allergy VALUES (1,\"allergy 1\", \"11/22/3333\");");
    dbService.exec("INSERT INTO allergy VALUES (1,\"allergy 2\", \"22/33/4444\");");
    dbService.exec("INSERT INTO allergy VALUES (4,\"allergy 3\", \"33/44/5555\");");
    dbService.exec("INSERT INTO allergy VALUES (5,\"allergy 4\", \"66/77/8888\");");
    dbService.exec("INSERT INTO allergy VALUES (6,\"allergy 5\", \"99/11/2222\");");

    dbService.exec("INSERT INTO diaryEntry VALUES (1,\"diary 1\", \"11/22/3333\");");
    dbService.exec("INSERT INTO diaryEntry VALUES (1,\"diary 2\", \"22/33/4444\");");
    dbService.exec("INSERT INTO diaryEntry VALUES (2,\"diary 3\", \"33/44/5555\");");
    dbService.exec("INSERT INTO diaryEntry VALUES (3,\"diary 4\", \"66/77/8888\");");
    dbService.exec("INSERT INTO diaryEntry VALUES (4,\"diary 5\", \"99/11/2222\");");

    dbService.exec("INSERT INTO treats VALUES (1, 5);");
    dbService.exec("INSERT INTO treats VALUES (2, 5);");
    dbService.exec("INSERT INTO treats VALUES (3, 5);");
    dbService.exec("INSERT INTO treats VALUES (4, 5);");
    dbService.exec("INSERT INTO treats VALUES (5, 5);");
    dbService.exec("INSERT INTO treats VALUES (6, 5);");


};

/*
Function to delete the clinician and medical records tables
Haven't figured out how to delete tables yet
It is giving the following error: bad parameter or other API misuse
*/
void DatabaseAdmin::deleteDatabaseTables(){
    cout << "Deleting database tables ..." << endl;

    DBService& dbService = DBService::GetInstance();

    // delete medicalRecords table first (since it has the foreign key for clinician)
    dbService.exec("DROP TABLE IF EXISTS medicalRecord;");

    // delete the clinician table
    dbService.exec("DROP TABLE IF EXISTS clinician;");

    // delete the allergy table
    dbService.exec("DROP TABLE IF EXISTS allergy;");

    // delete the diagnosis table
    dbService.exec("DROP TABLE IF EXISTS diagnosis;");

    // delete the diary table
    dbService.exec("DROP TABLE IF EXISTS diaryEntry;");

    // delete the prescription table
    dbService.exec("DROP TABLE IF EXISTS prescription;");

    // delete the surgery table
    dbService.exec("DROP TABLE IF EXISTS surgery;");

    // delete the vaccination table
    dbService.exec("DROP TABLE IF EXISTS vaccination;");

    // delete the request table
    dbService.exec("DROP TABLE IF EXISTS request;");

};

/*
Getter method to return db
*/
sqlite3* DatabaseAdmin::getDBobject(){
    return db;
}

/*
Getter method to return database name
*/
string DatabaseAdmin::getDBname(){
    return DBService::GetInstance().getDbName();
}

/*
Getter method to return physicianId
*/
// string DatabaseAdmin::getPhysicianID(){
//     return physicianId;
// }

/*
Getter method to return database pointer
*/
// sqlite3* DatabaseAdmin::getDBpointer(){
//     return db;
// }

/**
 * Main function for testing
 * To run, uncomment main, and do: g++ database_admin.cpp db_error_handler.cpp db_service.cpp -o "adminObj" -lsqlite3
 */
/*
int main(int argc, char *argv[]) {
    DatabaseAdmin* myAdmin = new DatabaseAdmin();
}
*/
