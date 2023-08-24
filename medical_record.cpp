/**
 * @file medicalRecord.cpp
 * @brief A medical record with getter and setter functions
 * 
 * This will allow for the creation of a medical record.
 * A medical record has many attributes, including ID, demographics,
 * contact information, diagnoses history, surgical history, prescriptions,
 * vaccinations, allergy information, and diary entries.
 * All these attributes can be set, retrieved, and added to.
 * 
 * @author Shruthi Sundararaman
 * @author Amreen Anbar
 * @bug No known bugs
*/

#include "medical_record.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <list>  
#include <sqlite3.h> 

using namespace std;
 
MedicalRecord::MedicalRecord()
{
    int id = 0;
    string demographics = "";
    vector<string> defaultVector;

    identificationNumber = id;
    demographicData = demographics;
    contactInformation = defaultVector;
    diagnosesHistory = defaultVector;
    surgicalHistory = defaultVector;
    prescriptionRecords = defaultVector;
    vaccinationRecords = defaultVector;
    allergies = defaultVector;
    diary = defaultVector;
}  
 
 
void MedicalRecord::set_Record(int id, string demographics, vector<string> contactInfo, vector<string> diagnosesHist, vector<string> surgicalHist, vector<string> prescriptions, vector<string> vaccinations, vector<string> allergyInfo, vector<string> diaryEntries)
{
    identificationNumber = id;
    demographicData = demographics;
    contactInformation = contactInfo;
    diagnosesHistory = diagnosesHist;
    surgicalHistory = surgicalHist;
    prescriptionRecords = prescriptions;
    vaccinationRecords = vaccinations;
    allergies = allergyInfo;
    diary = diaryEntries;
}
 
void MedicalRecord::setID(int id) {
    identificationNumber = id;
}
void MedicalRecord::setDemographics(string demographics){
    demographicData = demographics;
}
void MedicalRecord::setContactInfo(vector<string> contactInfo){
    contactInformation = contactInfo;
}
void MedicalRecord::setDiagnosesHistory(vector<string> diagnosesHist){
    diagnosesHistory = diagnosesHist;
}
void MedicalRecord::setSurgicalHistory(vector<string> surgicalHist){
    surgicalHistory = surgicalHist;
}
void MedicalRecord::setPrescriptions(vector<string> prescriptions){
    prescriptionRecords = prescriptions;
}
void MedicalRecord::setVaccinations(vector<string> vaccinations){
    vaccinationRecords = vaccinations;
}
void MedicalRecord::setAllergyInfo(vector<string> allergyInfo){
    allergies = allergyInfo;
}
void MedicalRecord::setDiaryEntries(vector<string> diaryEntries){
    diary = diaryEntries;
}

void MedicalRecord::addDiagnosis(string currDiagnosis){
    diagnosesHistory.push_back(currDiagnosis);
}
void MedicalRecord::addSurgery(string currSurgery){
    surgicalHistory.push_back(currSurgery);
}
void MedicalRecord::addPrescription(string currPrescription){
    prescriptionRecords.push_back(currPrescription);
}
void MedicalRecord::addVaccination(string currVaccination){
    vaccinationRecords.push_back(currVaccination);
}
void MedicalRecord::addAllergy(string allergy){
    allergies.push_back(allergy);
}
void MedicalRecord::addDiaryEntry(string diaryEntry){
    diary.push_back(diaryEntry);
}   
            
    
int MedicalRecord::getID() {
    return identificationNumber;
}
string MedicalRecord::getDemographics(){
    return demographicData;
}
vector<string> MedicalRecord::getContactInfo(){
    return contactInformation;
}
vector<string> MedicalRecord::getDiagnosisHistory(){
    return diagnosesHistory;
}
vector<string> MedicalRecord::getSurgicalHistory(){
    return surgicalHistory;
}
vector<string> MedicalRecord::getPrescriptions(){
    return prescriptionRecords;
}
vector<string> MedicalRecord::getVaccinations(){
    return vaccinationRecords;
}
vector<string> MedicalRecord::getAllergyInfo(){
    return allergies;
}
vector<string> MedicalRecord::getDiaryEntries(){
    return diary;
}

MedicalRecord::~MedicalRecord()
{
} 
 
void MedicalRecord::get_record()

{   /*

    cout<<"ID "<<identificationNumber<<endl; 
    cout<<"Demographic Data "<<demographicData<<endl;  
    cout<<"Contact Information"<<endl;
    for (string i : contactInformation)  
    {
    cout<<i<<endl;
    }    
    cout<<"Diagnosis History"<<endl;
    for (string i : diagnosesHistory)  
    {
    cout<<i<<endl;
    }  
    cout<<"Surgical History"<<endl; 
    for (string i : surgicalHistory)  
    {
    cout<<i<<endl;
    } 
    cout<<"Prescription Records"<<endl;
    for (string i : prescriptionRecords)  
    {
    cout<<i<<endl;
    }   
    cout<<"Vaccination Record"<<endl;
    for (string i : vaccinationRecords)  
    {
    cout<<i<<endl;
    }  
    cout<<"Allergy History"<<endl; 
    for (string i : allergies)  
    {
    cout<<i<<endl;
    }   
    cout<<"Diary"<<endl;
    for (string i : diary)  
    {
    cout<<i<<endl;
    }  
    */
   
}
 
