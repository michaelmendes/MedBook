#include "medicalRecord.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <list>  
#include <sqlite3.h> 

using namespace std;
 
medicalRecord::medicalRecord()
{
}   
 
void medicalRecord::set_Record(int a,
                             string b,
                             list<string> c,
                             list<string> d,
                             list<string> e,
                             list<string> f,
                             list<string> g,
                             list<string> h,
                             list<string> i)
{

    identificationNumber = a;
    demographicData = b;
    contactInformation = c;
    diagnosesHistory = d;
    surgicalHistory = e;
    prescriptionRecords = f;
    vaccinationRecords = g;
    allergies = h;
    diary = i;
}
 

medicalRecord::~medicalRecord()
{
} 
 
void medicalRecord::get_record()  

{   cout<<"ID "<<identificationNumber<<endl; 
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
   
}
 
