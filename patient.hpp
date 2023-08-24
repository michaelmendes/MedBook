/**
 * @file patient.hpp
 * @brief Function prototypes for Patient to allow for transfer of Patient objects between classes
 * 
 * This defines all the function prototypes for a Patient, which inherits from User
 * Each User has an ID, name, type, and password, and getter and setter methods for all of these
 * A patient also has a birthdate and sex, and getter and setter for these
 * 
 * @author Michael Mendes
 * @bug No known bugs
*/

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "medical_record.hpp"
#include "user.hpp"

class Patient : public User
{
public:
    /**
     * @brief Constructor for creating a patient objects with name, id, birthday, and sex
     * @param name the patient's name
     * @param id the patient's ID
     * @param birthday the patient's birthday
     * @param sex the patient's sex
    */
    Patient(std::string name = "", int id = -1, std::string birthday = "", std::string sex = "");

    /**
     * @brief Returns the birthday of the patient
     * @return the birthday of the patient as a string
    */
    std::string getBirth();

    /**
     * @brief returns the sex of the patient
     * @return the sex of the patient as a string
    */
    std::string getSex();

    /**
     * @brief sets the birthday of the patient
     * @param newBirth the patient's birthday
    */
    void setBirth(std::string newBirth);

    /**
     * @brief sets the sex of the patient
     * @param newSex the patient's sex
    */
    void setSex(std::string newSex);

private:
    int patientID = -1;
    std::string birthday = "";
    std::string patientSex = "";

    MedicalRecord record;
};

#endif // PATIENT_HPP
