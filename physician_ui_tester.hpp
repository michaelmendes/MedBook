/**
 * @file physician_ui_tester.hpp
 * @brief used to test the physician UI
 *
 * tests the family physician UI by editing the record, setting the family physician ui and getting patients
 * 
 * @author Michael Mendes
 * @bug No known bugs
*/

#ifndef PHYSICIANUITESTER_HPP
#define PHYSICIANUITESTER_HPP

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "patient.hpp"
#include "family_physician.hpp"

class PhysicianUiTester
{
public:
/**
 * @brief constructor
 * @param FamilyPhysician* the family physician object
*/
    PhysicianUiTester(FamilyPhysician *famPhysician);
/**
 * @brief returns the patients
 * @return vector<Patient> a vector of patient objects
*/
    std::vector<Patient> getPatients();
/**
 * @brief xxx
 * @param currPatient the current patient object
 * @param editCommand the string that contains which edit to make
 * @param editorParams the edit parameters 
 * @return void
*/
    void editRecord(Patient currPatient, std::string editCommand, std::string editorParams);
/**
 * @brief xxx
 * @param currPhysician the current patient object
 * @return void
*/
    void setFamilyPhysician(FamilyPhysician* currPhysician=nullptr);

private:
    FamilyPhysician *physician;
    std::vector<Patient> patientList;

};

#endif // PHYSICIANUITESTER_HPP
