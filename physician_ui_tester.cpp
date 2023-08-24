#include "physician_ui_tester.hpp"
#include "patient.hpp"

using namespace std;

PhysicianUiTester::PhysicianUiTester(FamilyPhysician* famPhysician)
{
    physician = famPhysician;
    Patient patient1("Mark", 1234);
    Patient patient2("James", 6243);
    Patient patient3("Taylor", 9087);
    Patient patient4("Sarah", 5555);
    patientList.push_back(patient1);
    patientList.push_back(patient2);
    patientList.push_back(patient3);
    patientList.push_back(patient4);
}

vector<Patient> PhysicianUiTester::getPatients()
{
    return patientList;
}

void PhysicianUiTester::setFamilyPhysician(FamilyPhysician* currPhysician) {
    physician = currPhysician;
}

void PhysicianUiTester::editRecord(Patient patient, string editCommand, string editorParams) {
    cout << "Command: " << editCommand << ", with parameters: " << editorParams << ", performed for Patient: " << patient.getId() << endl;

    if (editCommand == "delete patient")
    {
        vector<Patient> newList;
        for (Patient currPatient : patientList)
        {
            if (currPatient.getId() != patient.getId())
            {
                newList.push_back(currPatient);
            }
        }
        patientList = newList;
    }

    else if (editCommand == "add patient")
    {
        patientList.push_back(patient);
    }

    else if (editCommand == "request transfer")
    {
        string request = to_string(patient.getId()) + "," + patient.getName() + "," + editorParams;
        cout << "The request string sent to record editor is: " << request << endl;
        //physician->addRequest(request);
    }
    else if (editCommand == "transfer patient")
    {
        // patient should be removed from current physician's patientList and added to the requesting physician's
        vector<Patient> newList;
        for (Patient currPatient : patientList)
        {
            if (currPatient.getId() != patient.getId())
            {
                newList.push_back(currPatient);
            }
        }
        patientList = newList;
    }

}
