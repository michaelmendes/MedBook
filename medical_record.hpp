/**
 * @file medicalRecord.hpp
 * @brief Function prototypes for a medical record with getter and setter functions
 * 
 * This contains prototypes for a medical record.
 * A medical record has many attributes, including ID, demographics,
 * contact information, diagnoses history, surgical history, prescriptions,
 * vaccinations, allergy information, and diary entries.
 * All these attributes can be set, retrieved, and added to.
 * 
 * @author Shruthi Sundararaman
 * @author Amreen Anbar
 * @bug No known bugs
*/

#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H
#include <string> 
#include <vector>
#include <iostream>  
#include <list>  

class MedicalRecord
{  
    private:
        int identificationNumber; 
        std::string demographicData; 
        std::vector<std::string>contactInformation;  
        std::vector<std::string>diagnosesHistory;  
        std::vector<std::string>surgicalHistory;  
        std::vector<std::string>prescriptionRecords;  
        std::vector<std::string>vaccinationRecords;  
        std::vector<std::string>allergies;  
        std::vector<std::string>diary; 

    public:
        /**
         * @brief Generates a medical record object with all input attributes
         * This constructor will initialize a medical record object and set all of its attribuets with the values inputed when creating the object
         * 
         * @param id the identification number for the medical record
         * @param demographics the string containing demographic data
         * @param contactInfo the patient's contact information, such as phone number, email, address etc.
         * @param diagnosesHist the list of the patient's previous diagnoses
         * @param surgicalHist the list of the patient's previous surgeries
         * @param prescriptions the plist of the patient's current prescriptions
         * @param vaccinations the list of vaccinations the patient has received
         * @param allergyInfo the list of the patient's allergies
         * @param diaryEntries the list of the patient's manually inputted diary entries
         */           
         MedicalRecord();

        /**
         * @brief sets all the values of the medical record with the inputted values
         * 
         * This function allows the user to change all the values of the medical record at once
         * @param id the identification number for the medical record
         * @param demographics the string containing demographic data
         * @param contactInfo the patient's contact information, such as phone number, email, address etc.
         * @param diagnosesHist the list of the patient's previous diagnoses
         * @param surgicalHist the list of the patient's previous surgeries
         * @param prescriptions the plist of the patient's current prescriptions
         * @param vaccinations the list of vaccinations the patient has received
         * @param allergyInfo the list of the patient's allergies
         * @param diaryEntries the list of the patient's manually inputted diary entries
         * @return void
        */
        void set_Record(int id, std::string demographics, std::vector<std::string> contactInfo, std::vector<std::string> diagnosesHist, std::vector<std::string> surgicalHist, std::vector<std::string> prescriptions, std::vector<std::string> vaccinations, std::vector<std::string> allergyInfo, std::vector<std::string> diaryEntries); 

        /**
         * @brief returns each attribute of the medical record object as strings
         * @return void
        */
        void get_record();  

        /**
         * @brief allows the ID of the current medical record to be set
         * @param id the identification number for the medical record
         * @return void
        */
        void setID(int id);
        
        /**
         * @brief allows the demographics of the current medical record to be set
         * @param demographics the string containing demographic data
         * @return void
        */
        void setDemographics(std::string demographics);

        /**
         * @brief allows the contact info of the current medical record to be set
         * @param contactInfo the list containing the contact information strings
         * @return void
        */
        void setContactInfo(std::vector<std::string> contactInfo);

        /**
         * @brief allows the diagnoses history of the current medical record to be set
         * @param diagnosesHist the list containing diagnosis history strings
         * @return void
        */
        void setDiagnosesHistory(std::vector<std::string> diagnosesHist);

        /**
         * @brief allows the surgical history of the current medical record to be set
         * @param surgicalHist the list containing previous surgical strings
         * @return void
        */
        void setSurgicalHistory(std::vector<std::string> surgicalHist);

        /**
         * @brief allows the prescriptions of the current medical record to be set
         * @param prescriptions the list containing prescription strings
         * @return void
        */
        void setPrescriptions(std::vector<std::string> prescriptions);

        /**
         * @brief allows the vaccinations of the current medical record to be set
         * @param vaccinations the list containing vaccination strings
         * @return void
        */
        void setVaccinations(std::vector<std::string> vaccinations);

        /**
         * @brief allows the allergy inforamtion of the current medical record to be set
         * @param allergyInfo the list containing allergy information as strings
         * @return void
        */
        void setAllergyInfo(std::vector<std::string> allergyInfo);

        /**
         * @brief allows the diary entries of the current medical record to be set
         * @param diaryEntries the list containing diary entry strings
         * @return void
        */
        void setDiaryEntries(std::vector<std::string> diaryEntries);

        /**
         * @brief adds a diagnosis to the diagnosesHist attribute
         * @param currDiagnosis the string containing the diagnosis to be added
         * @return void
        */
        void addDiagnosis(std::string currDiagnosis);

        /**
         * @brief adds a surgery to the surgicalHist attribute
         * @param currSurgery the string containing the surgery to be added
         * @return void
        */
        void addSurgery(std::string currSurgery);

        /**
         * @brief adds a prescription to the prescriptions attribute
         * @param currPrescription the string containing the prescription to be added
         * @return void
        */
        void addPrescription(std::string currPrescription);

        /**
         * @brief adds a vaccination to the vaccinations attribute
         * @param currVaccination the string containing the vaccination to be added
         * @return void
        */
        void addVaccination(std::string currVaccination);

        /**
         * @brief adds an allergy to the allergyInfo attribute
         * @param allergy the string containing the allergy to be added
         * @return void
        */
        void addAllergy(std::string allergy);

        /**
         * @brief adds a diary entry to the diaryEntries attribute
         * @param diaryEntry the string containing the diary entry to be added
         * @return void
        */
        void addDiaryEntry(std::string diaryEntry);                     
          
        /**
         * @brief returns the ID of the medical record
         * @return the ID
        */
        int getID();

        /**
         * @brief returns the demographics of the medical record
         * @return the demographics as a string
        */
        std::string getDemographics();

        /**
         * @brief returns the contact inforamtion for the medical record
         * @return the contact information as a vector
        */
        std::vector<std::string> getContactInfo();

        /**
         * @brief returns the diagnosis history of the medical record
         * @return the diagnosis history
        */
        std::vector<std::string> getDiagnosisHistory();

        /**
         * @brief returns the surgical history of the medical record
         * @return the surgical history
        */
        std::vector<std::string> getSurgicalHistory();

        /**
         * @brief returns the prescriptions of the medical record
         * @return the prescriptions
        */
        std::vector<std::string> getPrescriptions();

        /**
         * @brief returns the vaccinations of the medical record
         * @return the vaccinations
        */
        std::vector<std::string> getVaccinations();

        /**
         * @brief returns the allergy information of the medical record
         * @return the allergy information
        */
        std::vector<std::string> getAllergyInfo();

        /**
         * @brief returns the diary entries of the medical record
         * @return the diary entries
        */
        std::vector<std::string> getDiaryEntries();

        /**
         * @brief deconstructor for the class
        */
        ~MedicalRecord();
};          
 
#endif  

