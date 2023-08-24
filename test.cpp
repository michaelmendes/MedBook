// this is a test file to test if I have connected to bit bucket

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "medicalRecordDatabase.h"
using namespace std;

int main (int argc, char *argv[]) {
    medicalRecordDatabase *myDatabase = new medicalRecordDatabase();
    cout << "initialized db" << endl;
    myDatabase->setDatabaseRandom();
    cout << "set random values in database tables" << endl;
}
